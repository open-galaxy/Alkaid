#ifndef SRC_ALKAID_PROCESS_H_
#define SRC_ALKAID_PROCESS_H_

#include <stdlib.h>
#include <v8.h>
#include <libplatform/libplatform.h>


namespace alkaid {

namespace process {

using v8::Local;
using v8::ObjectTemplate;
using v8::Value;
using v8::Isolate;
using v8::Array;
using v8::NewStringType;
using v8::String;
using v8::Context;
using v8::Object;

Local<Array> ParseArgs(Isolate* isolate, Local<Context> context, int argc, char** argv);
void Initialize(Isolate* isolate, Local<Context> context, int argc, char** argv);

}  // namespace process

}; // namespace alkaid


#endif