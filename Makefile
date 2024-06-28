#
# https://github.com/0Magenta0/insurgency-external
# Copyright 0Magenta0 2024
# MIT License
#

CC=cc
CFLAGS=-std=gnu18 -O2 -Wall -Werror -m32
LDFLAGS=-lxcb -lxcb-xfixes -lxcb-dbe -lxcb-shape -lm
SRC=$(shell find src/ -type f -iname '*.c')
BINARY=overlay

all: clean build

clean:
	rm -f $(BINARY)

build:
	$(CC) $(SRC) -o $(BINARY) $(CFLAGS) $(LDFLAGS)
