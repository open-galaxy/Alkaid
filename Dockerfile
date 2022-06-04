FROM debian:buster-slim

WORKDIR /build
ENV V8_RELEASE 0.1.8
ENV V8_H_RELEASE 0.1.7

COPY CMakeLists.txt .
COPY src ./src

RUN apt update && apt upgrade -y && apt install -y git curl python lsb-release sudo cmake build-essential

RUN curl -L -o v8headers-$V8_H_RELEASE.tar.gz https://raw.githubusercontent.com/just-js/v8headers/$V8_H_RELEASE/v8.tar.gz \
  && curl -L -o v8lib-$V8_RELEASE.tar.gz https://raw.githubusercontent.com/just-js/libv8/$V8_RELEASE/v8.tar.gz \
  && gzip -d v8headers-$V8_H_RELEASE.tar.gz \
  && gzip -d v8lib-$V8_RELEASE.tar.gz \
  && tar -xvf v8headers-$V8_H_RELEASE.tar \
  && tar -xvf v8lib-$V8_RELEASE.tar \
  && rm -f v8headers-$V8_H_RELEASE.tar \
  && rm -f v8lib-$V8_RELEASE.tar

RUN cmake . && make