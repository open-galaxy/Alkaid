#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <v8.h>
#include <libplatform/libplatform.h>
#include "env.h"

using v8::Isolate;
using v8::HandleScope;
using v8::ArrayBuffer;
using v8::Local;
using v8::Context;
using v8::String;
using v8::Value;
using v8::Script;
using v8::NewStringType;

using namespace alkaid;

int main(int argc, char** argv) {
  Env env(argc, argv);

  if (argc > 1) {
    Isolate* isolate = env.NewIsolate();

    int exit_code = env.Run(isolate, argv[1]);

    env.ExitEnv(isolate);
    return exit_code;
  }

  return 0;
}