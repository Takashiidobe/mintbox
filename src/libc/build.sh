#!/usr/bin/env bash

m68k-atari-mint-gcc -nostdlib crt0.S atexit.c $1 -lgcc -o "test"
