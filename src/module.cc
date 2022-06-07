#include "module.h"

namespace alkaid {

Module::Module(Isolate* isolate) {
  isolate_ = isolate;
}

Module::~Module() {
  isolate_ = nullptr;
}

void LoadBuiltin(Local<ObjectTemplate> global) {
  global_ = global;
}

void SetMethod(const char* name, FunctionCallback callback)) {

}

}