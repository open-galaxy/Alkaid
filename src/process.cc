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

void Initialize(Isolate* isolate, Local<Context> context, int argc, char** argv) {
  Local<Object> process = Object::New(isolate);

  process->Set(context, FIXED_ONE_BYTE_STRING(isolate, "argv"), ParseArgs(isolate, context, argc, argv))
          .Check();

  context->Global()
         ->Set(context, FIXED_ONE_BYTE_STRING(isolate, "process"), process)
         .Check();
  
  context->Global()
         ->Set(context, FIXED_ONE_BYTE_STRING(isolate, "globalThis"), context->Global())
         .Check();
  
} // namespace processs

} // namespace alkaid

}