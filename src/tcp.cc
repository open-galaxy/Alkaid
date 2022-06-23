#include "tcp.h"
#include "util.h"
#include "util-inl.h"

namespace alkaid {

namespace tcp {

void Open(const v8::FunctionCallbackInfo<v8::Value> &args) {
  v8::Isolate* isolate = args.GetIsolate();
  v8::HandleScope handle_scope(isolate);
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    isolate->ThrowException(v8::Exception::Error(FIXED_ONE_BYTE_STRING(isolate, "socket failed")));
    return;
  }
  args.GetReturnValue().Set(v8::Integer::New(isolate, fd));
}

void Listen(const v8::FunctionCallbackInfo<v8::Value> &args) {
  v8::Isolate* isolate = args.GetIsolate();
  
  int fd = v8::Local<v8::Integer>::Cast(args[0])->Value();

  args.GetReturnValue().Set(v8::Integer::New(isolate, listen(fd, SOMAXCONN)));
}

void Bind(const v8::FunctionCallbackInfo<v8::Value> &args) {
  v8::Isolate *isolate = args.GetIsolate();
  int fd = v8::Local<v8::Integer>::Cast(args[0])->Value();
  int port = v8::Local<v8::Integer>::Cast(args[1])->Value();

  const char* address = "0.0.0.0";
  int socktype = AF_INET;
  struct sockaddr_in server_addr;
  server_addr.sin_family = socktype;
  server_addr.sin_port = htons(port);
  inet_pton(socktype, address, &(server_addr.sin_addr.s_addr));
  int r = bind(fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

  args.GetReturnValue().Set(v8::Integer::New(isolate, r));
}

v8::Local<v8::ObjectTemplate> Initialize(v8::Isolate* isolate) {
  v8::Local<v8::ObjectTemplate> tcp = v8::ObjectTemplate::New(isolate);

  SET_METHOD(isolate, "open", tcp, Open);
  SET_METHOD(isolate, "listen", tcp, Listen);
  SET_METHOD(isolate, "bind", tcp, Bind);

  return tcp;
}

} // namespace tcp

} // namespace alkaid