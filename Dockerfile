FROM --platform=linux/amd64 debian:buster-slim

WORKDIR /build
ENV V8_RELEASE 0.1.8
ENV V8_H_RELEASE 0.1.7
ENV LLHTTP_V v6.0.6

COPY CMakeLists.txt .
COPY src ./src
COPY deps ./deps
COPY examples ./examples
COPY lib ./lib

RUN apt update && apt upgrade -y && apt install -y git curl python lsb-release sudo cmake build-essential

RUN curl -L -o v8headers-$V8_H_RELEASE.tar.gz https://raw.githubusercontent.com/just-js/v8headers/$V8_H_RELEASE/v8.tar.gz \
  && curl -L -o v8lib-$V8_RELEASE.tar.gz https://raw.githubusercontent.com/just-js/libv8/$V8_RELEASE/v8.tar.gz \
  && gzip -d v8headers-$V8_H_RELEASE.tar.gz \
  && gzip -d v8lib-$V8_RELEASE.tar.gz \
  && tar -xvf v8headers-$V8_H_RELEASE.tar \
  && tar -xvf v8lib-$V8_RELEASE.tar \
  && rm -f v8headers-$V8_H_RELEASE.tar \
  && rm -f v8lib-$V8_RELEASE.tar

WORKDIR /build/deps/llhttp
RUN curl -L -o libllhttp-$LLHTTP_V.tar.gz https://raw.githubusercontent.com/open-galaxy/libllhttp/main/dist/libllhttp-$LLHTTP_V.tar.gz \
  && tar zxf libllhttp-$LLHTTP_V.tar.gz \
  && rm -f libllhttp-$LLHTTP_V.tar.gz

WORKDIR /build
RUN cmake . && make