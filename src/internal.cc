#include "internal.h"

namespace alkaid {

void Internal::addEventListener(const FunctionCallbackInfo<Value> &args) {
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  if (args[0].IsEmpty()) return;
  if (args[0]->IsFunction() == false) return;

  Local<Function> callback = Local<Function>::Cast(args[0]);
  const unsigned argc = 1;
  Local<Object> event = Object::New(isolate);
  event->Set(
    context,
    String::NewFromUtf8Literal(isolate, "respondWith", NewStringType::kNormal),
    FunctionTemplate::New(isolate, respondWithByEvent)->GetFunction(context).ToLocalChecked()
  ).Check();

  Local<Value> argv[argc] = { event };

  MaybeLocal<Value> result = callback->Call(context, context->Global(), argc, argv);
}

void Internal::respondWithByEvent(const FunctionCallbackInfo<Value> &args) {

}

}