#include "env.h"

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

Env::Env(char** argv) {
  platform_ = v8::platform::NewDefaultPlatform();
  V8::InitializePlatform(platform_.get());
  V8::Initialize();
}

Isolate* Env::NewIsolate() {
  Isolate* isolate = Isolate::Allocate();
  CHECK_NOT_NULL(isolate);

  Isolate::CreateParams params;
  params.array_buffer_allocator = ArrayBuffer::Allocator::NewDefaultAllocator();
  Isolate::Initialize(isolate, params);

  return isolate;
}

int Env::Run(Isolate* isolate) {
  Locker locker(isolate);
  Isolate::Scope isolate_scope(isolate);
  HandleScope handle_scope(isolate);

  Local<Context> context = Context::New(isolate);
  Context::Scope context_scope(context);
  {
    Local<String> source = String::NewFromUtf8(isolate, "'Hello' + ', World'", NewStringType::kNormal).ToLocalChecked();
    Local<Script> script = Script::Compile(context, source).ToLocalChecked();
    Local<Value> result = script->Run(context).ToLocalChecked();
    String::Utf8Value utf8(isolate, result);
    printf("%s\n", *utf8);
  }

  return 0;
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