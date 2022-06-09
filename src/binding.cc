#include "binding.h"
#include "internal.h"
#include "vm.h"
#include "fs.h"
#include "process.h"
#include "util.h"

namespace alkaid {

namespace binding {

void RegisterBuiltinModules(Isolate* isolate, Local<ObjectTemplate> global) {
  SET_METHOD(isolate, "print", global, Internal::print);
  SET_MODULE(isolate, "fs", global, fs::Initialize(isolate));
  SET_MODULE(isolate, "vm", global, vm::Initialize(isolate));
}

} // namespace binding

} // namespace alkaid