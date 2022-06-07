#ifndef SRC_ALKAID_MODULE_H_
#define SRC_ALKAID_MODULE_H_

#include <v8.h>
#include <libplatform/libplatform.h>


namespace alkaid {

using v8::Isolate;
using v8::ObjectTemplate;
using v8::Local;
using v8::FunctionCallback;

class Module {
  private:
    Isolate* isolate_;
    Local<ObjectTemplate> global_;
    void SetMethod(const char* name, FunctionCallback callback));
  
  public:
    Module::Module(Isolate* isolate);
    Module::~Module();

    void LoadBuiltin(Local<ObjectTemplate> global);

};

}


#endif