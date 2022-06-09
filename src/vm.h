#ifndef SRC_ALKAID_VM_H_
#define SRC_ALKAID_VM_H_

#include <v8.h>
#include <libplatform/libplatform.h>

namespace alkaid {

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

namespace vm {

void RunScript(const FunctionCallbackInfo<Value> &args);
Local<ObjectTemplate> Initialize(Isolate* isolate);

}

}

#endif