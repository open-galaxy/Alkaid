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

}

#endif