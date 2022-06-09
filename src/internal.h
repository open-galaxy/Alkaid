#ifndef SRC_ALKAID_INTERNAL_H_
#define SRC_ALKAID_INTERNAL_H_

#include <stdlib.h>
#include <stdio.h>
#include <v8.h>
#include <libplatform/libplatform.h>


namespace alkaid {

using v8::FunctionCallbackInfo;
using v8::Value;
using v8::Isolate;
using v8::FunctionTemplate;
using v8::Local;
using v8::ObjectTemplate;
using v8::Object;
using v8::String;
using v8::NewStringType;
using v8::Function;
using v8::Context;
using v8::MaybeLocal;
using namespace std;

class Internal {
  public:
    static void print(const FunctionCallbackInfo<Value> &args);
};

}


#endif