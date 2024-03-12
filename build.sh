#!/bin/sh

set -xe
cc -o ./target/main -g src/expr.c src/interp.c src/main.c src/scan.c src/tree.c
