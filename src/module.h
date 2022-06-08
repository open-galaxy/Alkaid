#ifndef SRC_ALKAID_MODULE_H_
#define SRC_ALKAID_MODULE_H_

#include <v8.h>
#include <libplatform/libplatform.h>


namespace alkaid {

using v8::Isolate;
using v8::ObjectTemplate;
using v8::Local;
using v8::FunctionCallback;
using v8::String;
using v8::NewStringType;
using v8::FunctionTemplate;

class Module {
  private:
    Isolate* isolate_;
    void SetMethod(Local<ObjectTemplate> target, const char* name, FunctionCallback callback);
  
  public:
    Module(Isolate* isolate);
    ~Module();

    void Load(Local<ObjectTemplate> global);

};

}


#endif