#ifndef SRC_ALKAID_FS_H_
#define SRC_ALKAID_FS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <v8.h>
#include <libplatform/libplatform.h>


namespace alkaid {

namespace fs {

using namespace std;
using v8::Value;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Context;
using v8::String;
using v8::TryCatch;
using v8::ScriptOrigin;
using v8::ScriptCompiler;
using v8::MaybeLocal;
using v8::Script;
using v8::Object;
using v8::ObjectTemplate;
using v8::NewStringType;

char* ReadFile(const char* filepath, unsigned int* file_len_out);
void ReadFileV8(const FunctionCallbackInfo<Value> &args);
Local<ObjectTemplate> Initialize(Isolate* isolate);

} // namespace fs

} // namespace alkaid


#endif