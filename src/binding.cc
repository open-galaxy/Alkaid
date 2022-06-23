#include "binding.h"
#include "vm.h"
#include "fs.h"
#include "process.h"
#include "util.h"
#include "tcp.h"

namespace alkaid {

namespace binding {

void RegisterBuiltinModules(Isolate* isolate, Local<ObjectTemplate> global) {
  SET_MODULE(isolate, "fs", global, fs::Initialize(isolate));
  SET_MODULE(isolate, "vm", global, vm::Initialize(isolate));
  SET_MODULE(isolate, "tcp", global, tcp::Initialize(isolate));
}

void GetInternalBinding(const FunctionCallbackInfo<Value>& args) {
  CHECK(args[0]->IsString());

  Isolate* isolate = args.GetIsolate();
  Local<String> module = args[0].As<String>();
  Local<Object> exports;

  args.GetReturnValue().Set(exports);
}

} // namespace binding

} // namespace alkaid