#!/bin/sh

set -xe

CFLAGS="-Wall -Wextra -ggdb `pkg-config --cflags raylib`"
LIBS="`pkg-config --libs raylib` -lm -ldl -lpthread -lrt -lX11"

g++ $CFLAGS -o snake src/main.cpp src/game.cpp -I./include $LIBS
