#!/bin/bash -xe

ROOT=$(pwd)
CONTAINER_ROOT=/build

docker build -t alkaid .

docker run --rm -it --platform linux/amd64 --entrypoint bash \
  -v $ROOT/src:$CONTAINER_ROOT/src:ro \
  -v $ROOT/lib:$CONTAINER_ROOT/lib:ro \
  -v $ROOT/examples:$CONTAINER_ROOT/examples:ro \
  -v $ROOT/CMakeLists.txt:$CONTAINER_ROOT/CMakeLists.txt:ro \
  alkaid
