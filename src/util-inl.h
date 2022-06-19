#ifndef SRC_ALKAID_UTIL_INL_H_
#define SRC_ALKAID_UTIL_INL_H_

#include <stdlib.h>
#include <v8.h>
#include <libplatform/libplatform.h>

namespace alkaid {

inline v8::Local<v8::String> OneByteString(v8::Isolate* isolate, const char* data, int length) {
  return v8::String::NewFromOneByte(isolate,
                                    reinterpret_cast<const uint8_t*>(data),
                                    v8::NewStringType::kNormal,
                                    length).ToLocalChecked();
}

inline v8::Local<v8::FunctionTemplate> NewFunctionTemplate(v8::Isolate* isolate,
                                     v8::FunctionCallback callback,
                                     v8::Local<v8::Signature> signature,
                                     v8::ConstructorBehavior behavior,
                                     v8::SideEffectType side_effect_type) {
  v8::Local<v8::Object> external = v8::Object::New(isolate);
  return v8::FunctionTemplate::New(isolate, callback, external,
                                   signature, 0, behavior, side_effect_type);
}

inline void SetMethod(v8::Isolate* isolate, v8::Local<v8::Object> that,
                                   const char* name,
                                   v8::FunctionCallback callback) {
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  v8::Local<v8::Function> function =
      NewFunctionTemplate(isolate, callback, v8::Local<v8::Signature>(),
                          v8::ConstructorBehavior::kThrow,
                          v8::SideEffectType::kHasSideEffect)
          ->GetFunction(context)
          .ToLocalChecked();
  // kInternalized strings are created in the old space.
  const v8::NewStringType type = v8::NewStringType::kInternalized;
  v8::Local<v8::String> name_string =
      v8::String::NewFromUtf8(isolate, name, type).ToLocalChecked();
  that->Set(context, name_string, function).Check();
  function->SetName(name_string);  // NODE_SET_METHOD() compatibility.
}

inline void SetValue(v8::Isolate* isolate,  v8::Local<v8::Object> that,
                    const char* name, v8::Local<v8::Value> value) {
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  const v8::NewStringType type = v8::NewStringType::kInternalized;
  v8::Local<v8::String> name_string =
      v8::String::NewFromUtf8(isolate, name, type).ToLocalChecked();
  that->Set(context, name_string, value).Check();
}

}

#endif