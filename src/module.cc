#include "module.h"
#include "internal.h"

namespace alkaid {

Module::Module(Isolate* isolate) {
  isolate_ = isolate;
}

Module::~Module() {
  isolate_ = nullptr;
}

void Module::Load(Local<ObjectTemplate> global) {
  SetMethod(global, "addEventListener", Internal::addEventListener);
}

void Module::SetMethod(Local<ObjectTemplate> target, const char* name, FunctionCallback callback) {
  target->Set(
    String::NewFromUtf8(isolate_, name, NewStringType::kNormal).ToLocalChecked(),
    FunctionTemplate::New(isolate_, callback)
  );
}

}