#!/bin/bash -xe

ROOT=$(pwd)
CONTAINER_ROOT=/build

docker build -t alkaid .

docker run --rm -it --platform linux/amd64 --entrypoint bash \
  -v $ROOT/src:$CONTAINER_ROOT/src:ro \
  -v $ROOT/CMakeLists.txt:$CONTAINER_ROOT/CMakeLists.txt:ro \
  -v $ROOT/example:$CONTAINER_ROOT/example:ro \
  alkaid
