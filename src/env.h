#ifndef SRC_ALKAID_ENV_H_
#define SRC_ALKAID_ENV_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <v8.h>
#include <libplatform/libplatform.h>
#include "util.h"

namespace alkaid {

using v8::Isolate;
using v8::Platform;
using v8::Local;
using v8::ObjectTemplate;
using v8::Context;
using v8::Script;
using v8::TryCatch;

class Env {
  public:
    Env(char** argv);
    ~Env();

    Isolate* NewIsolate();
    int Run(Isolate* isolate, const char* filepath);
    // TODO
    void ExitEnv(Isolate* isolate);
  private:
    std::unique_ptr<Platform> platform_;
    int Compile(const char* filepath, Isolate* isolate, Local<Context> context);
    void PrintStackTrace(Isolate* isolate, const TryCatch& try_catch);
};

}

#endif