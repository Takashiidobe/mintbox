#!/usr/bin/env bash

m68k-atari-mint-gcc crt0.S putchar.S putch.c puts.c atoi.c atexit.c $1 -lgcc -o "test"
