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

class Env {
  public:
    Env(char** argv);
    ~Env();

    Isolate* NewIsolate();
    int Run(Isolate* isolate);
    // TODO
    void ExitEnv(Isolate* isolate);
  private:
    std::unique_ptr<Platform> platform_;

};

}

#endif