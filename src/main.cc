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

int main(int argc, char** argv) {
  alkaid::Env env(argv);
  Isolate* isolate = env.NewIsolate();

  int exit_code = env.Run(isolate);

  env.ExitEnv(isolate);
  return exit_code;
}