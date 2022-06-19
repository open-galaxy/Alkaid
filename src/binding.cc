#include "binding.h"
#include "vm.h"
#include "fs.h"
#include "process.h"
#include "util.h"

namespace alkaid {

namespace binding {

void RegisterBuiltinModules(Isolate* isolate, Local<ObjectTemplate> global) {
  SET_MODULE(isolate, "fs", global, fs::Initialize(isolate));
  SET_MODULE(isolate, "vm", global, vm::Initialize(isolate));
}

void GetInternalBinding(const FunctionCallbackInfo<Value>& args) {
  CHECK(args[0]->IsString());

  Isolate* isolate = args.GetIsolate();
  Local<String> module = args[0].As<String>();
  Local<Object> exports;

  // TODO(Ricky) Implementation of native modules

  args.GetReturnValue().Set(exports);
}

} // namespace binding

} // namespace alkaid