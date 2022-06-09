#include "env.h"
#include "binding.h"
#include "fs.h"
#include "util.h"
#include "process.h"

namespace alkaid {

using v8::Isolate;
using v8::V8;
using v8::ArrayBuffer;
using v8::Locker;
using v8::HandleScope;
using v8::Context;
using v8::Local;
using v8::String;
using v8::Value;
using v8::Script;
using v8::NewStringType;
using v8::Message;
using v8::StackTrace;
using v8::StackFrame;

Env::Env(int argc, char** argv) {
  platform_ = v8::platform::NewDefaultPlatform();
  V8::InitializePlatform(platform_.get());
  V8::Initialize();
  V8::SetFlagsFromString(v8flags);

  args_ = { argc, argv };
}

Isolate* Env::NewIsolate() {
  Isolate* isolate = Isolate::Allocate();
  CHECK_NOT_NULL(isolate);

  Isolate::CreateParams params;
  params.array_buffer_allocator = ArrayBuffer::Allocator::NewDefaultAllocator();
  Isolate::Initialize(isolate, params);

  return isolate;
}

int Env::Run(Isolate* isolate, const char* filepath_str) {
  Isolate::Scope isolate_scope(isolate);
  HandleScope handle_scope(isolate);

  // 创建全局对象
  Local<ObjectTemplate> global = ObjectTemplate::New(isolate);

  // 注册内部模块
  binding::RegisterBuiltinModules(isolate, global);

  // 创建执行上下文环境
  Local<Context> context = Context::New(isolate, NULL, global);
  Context::Scope context_scope(context);
  
  // 注册 process
  process::Initialize(isolate, context, args_.argc, args_.argv);

  // 执行入口文件
  return ExecuteBootstrapper("lib/bootstrap.js", isolate, context);
}

int Env::ExecuteBootstrapper(const char* filepath_str, Isolate* isolate, Local<Context> context) {
  Local<String> filepath = String::NewFromUtf8(isolate, filepath_str, NewStringType::kNormal).ToLocalChecked();

  TryCatch try_catch(isolate);
  const char* entry_source_str = fs::ReadFile(filepath_str, NULL);
  Local<String> entry_source = String::NewFromUtf8(isolate, entry_source_str, NewStringType::kNormal).ToLocalChecked();

  Local<Script> entry_script;
  v8::ScriptOrigin entry_script_origin(isolate, filepath);
  if (!Script::Compile(context, entry_source, &entry_script_origin).ToLocal(&entry_script)) {
    PrintStackTrace(isolate, try_catch);
    return -1;
  }

  Local<Value> result;
  if (!entry_script->Run(context).ToLocal(&result)) {
    PrintStackTrace(isolate, try_catch);
    return -2;
  }

  return 0;
}

void Env::PrintStackTrace(Isolate* isolate, const TryCatch& try_catch) {
  HandleScope handleScope(isolate);

  Local<Value> exception = try_catch.Exception();
  Local<Message> message = try_catch.Message();
  Local<StackTrace> stack = message->GetStackTrace();
  String::Utf8Value ex(isolate, exception);
  Local<Value> scriptName = message->GetScriptResourceName();
  String::Utf8Value scriptname(isolate, scriptName);
  Local<Context> context = isolate->GetCurrentContext();

  int linenum = message->GetLineNumber(context).FromJust();
  fprintf(stderr, "%s in %s on line %i\n", *ex, *scriptname, linenum);
  if (stack.IsEmpty()) return;

  for (int i = 0; i < stack->GetFrameCount(); i++) {
    Local<StackFrame> stack_frame = stack->GetFrame(isolate, i);
    Local<String> functionName = stack_frame->GetFunctionName();
    Local<String> scriptName = stack_frame->GetScriptName();
    String::Utf8Value fn_name_s(isolate, functionName);
    String::Utf8Value script_name(isolate, scriptName);

    const int line_number = stack_frame->GetLineNumber();
    const int column = stack_frame->GetColumn();
    if (stack_frame->IsEval()) {
      if (stack_frame->GetScriptId() == Message::kNoScriptIdInfo) {
        fprintf(stderr, "    at [eval]:%i:%i\n", line_number, column);
      } else {
        fprintf(stderr, "    at [eval] (%s:%i:%i)\n", *script_name,
          line_number, column);
      }
      break;
    }

    if (fn_name_s.length() == 0) {
      fprintf(stderr, "    at %s:%i:%i\n", *script_name, line_number, column);
    } else {
      fprintf(stderr, "    at %s (%s:%i:%i)\n", *fn_name_s, *script_name,
        line_number, column);
    }
  }

  fflush(stderr);
}

void Env::ExitEnv(Isolate* isolate) {
  // TODO
  isolate->Dispose();
  v8::V8::Dispose();
  v8::V8::ShutdownPlatform();
  platform_.reset();
}

Env::~Env() {}
}