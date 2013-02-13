#!/bin/sh

set -e -x

cc -std=c99 -Wall -Werror -o msg *.c
