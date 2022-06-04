#!/bin/bash -xe

docker build -t alkaid .
docker run --rm -it --entrypoint bash alkaid
