#include "process.h"
#include "util.h"
#include <iostream>

namespace alkaid {

namespace process {

Local<Array> ParseArgs(Isolate* isolate, Local<Context> context, int argc, char** argv) {
  Local<Array> arguments = Array::New(isolate, argc);

  for (int i = 0; i < argc; i++) {
    arguments->Set(context, i, String::NewFromUtf8(isolate, argv[i], 
      NewStringType::kNormal, strlen(argv[i])).ToLocalChecked()).Check();
  }

  return arguments;
}

const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

void Print(const FunctionCallbackInfo<Value>& args) {
  bool first = true;
  for (int i = 0; i < args.Length(); i++) {
    v8::HandleScope handle_scope(args.GetIsolate());
    if (first) {
      first = false;
    } else {
      printf(" ");
    }
    v8::String::Utf8Value str(args.GetIsolate(), args[i]);
    const char* cstr = ToCString(str);
    printf("%s", cstr);
  }
  printf("\n");
  fflush(stdout);
}

void PrintError(const FunctionCallbackInfo<Value> &args) {
  bool first = true;
  printf("Error: ");
  for (int i = 0; i < args.Length(); i++) {
    v8::HandleScope handle_scope(args.GetIsolate());
    if (first) {
      first = false;
    } else {
      printf(" ");
    }
    v8::String::Utf8Value str(args.GetIsolate(), args[i]);
    const char* cstr = ToCString(str);
    printf("%s", cstr);
  }
  printf("\n");
  fflush(stdout);
}

void Initialize(Isolate* isolate, Local<Context> context, int argc, char** argv) {
  Local<Object> process = Object::New(isolate);

  SetMethod(isolate, process, "stdout", Print);
  SetMethod(isolate, process, "stderr", PrintError);
  SetValue(isolate, process, "argv", ParseArgs(isolate, context, argc, argv));

  context->Global()
         ->Set(context, FIXED_ONE_BYTE_STRING(isolate, "process"), process)
         .Check();
  
  context->Global()
         ->Set(context, FIXED_ONE_BYTE_STRING(isolate, "globalThis"), context->Global())
         .Check();
  
} // namespace processs

} // namespace alkaid

}