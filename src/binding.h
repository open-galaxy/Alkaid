#ifndef SRC_ALKAID_BINDING_H_
#define SRC_ALKAID_BINDING_H_

#include <v8.h>
#include <libplatform/libplatform.h>


namespace alkaid {

namespace binding {

using v8::Isolate;
using v8::ObjectTemplate;
using v8::Local;
using v8::FunctionCallback;
using v8::String;
using v8::NewStringType;
using v8::FunctionTemplate;

void RegisterBuiltinModules(Isolate* isolate, Local<ObjectTemplate> global);

}  // namespace binding

}; // namespace alkaid


#endif