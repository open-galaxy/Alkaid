#ifndef SRC_ALKAID_TCP_H_
#define SRC_ALKAID_TCP_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <v8.h>
#include <libplatform/libplatform.h>

namespace alkaid {

namespace tcp {

void Open(const v8::FunctionCallbackInfo<v8::Value> &args);
void Listen(const v8::FunctionCallbackInfo<v8::Value> &args);
void Bind(const v8::FunctionCallbackInfo<v8::Value> &args);

v8::Local<v8::ObjectTemplate> Initialize(v8::Isolate* isolate);

} // namespace tcp

} // namespace alkaid


#endif