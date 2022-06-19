#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

#include <v8.h>
#include <libplatform/libplatform.h>
#include <stdlib.h>
#include "util-inl.h"

namespace alkaid {

#ifdef __GNUC__
#define UNLIKELY(expr) __builtin_expect(!!(expr), 0)
#else
#define UNLIKELY(expr) expr
#endif

static const char* v8flags = "--stack-trace-limit=10 --use-strict --disallow-code-generation-from-strings";

#define CHECK(expr)                                                           \
  do {                                                                        \
    if (UNLIKELY(!(expr))) {                                                  \
      abort();                                                                \
    }                                                                         \
  } while (0)

#define CHECK_NOT_NULL(val) CHECK((val) != nullptr)

#define SET_MODULE(isolate, name_str, target, mod)                            \
  do {                                                                        \
    v8::Local<v8::String> name =                                              \
          v8::String::NewFromUtf8(                                            \
            isolate, name_str, v8::NewStringType::kNormal                     \
          ).ToLocalChecked();                                                 \
    target->Set(name, mod);                                                   \
  } while (0)

#define SET_METHOD(isolate, name_str, target, callback)                       \
  do {                                                                        \
    v8::Local<v8::String> name =                                              \
          v8::String::NewFromUtf8(                                            \
            isolate, name_str, v8::NewStringType::kNormal                     \
          ).ToLocalChecked();                                                 \
    target->Set(name, v8::FunctionTemplate::New(isolate, callback));          \
  } while (0)

#define SET_VALUE(isolate, name_str, target, value)                           \
  do {                                                                        \
    v8::Local<v8::String> name =                                              \
          v8::String::NewFromUtf8(                                            \
            isolate, name_str, v8::NewStringType::kNormal                     \
          ).ToLocalChecked();                                                 \
    target->Set(name, value);                                                 \
  } while (0)

template <std::size_t N>
inline v8::Local<v8::String> FIXED_ONE_BYTE_STRING(v8::Isolate* isolate, const std::array<char, N>& arr) {
  return OneByteString(isolate, arr.data(), N - 1);
}

template <int N>
inline v8::Local<v8::String> FIXED_ONE_BYTE_STRING(v8::Isolate* isolate, const char(&data)[N]) {
  return OneByteString(isolate, data, N - 1);
}

}

#endif