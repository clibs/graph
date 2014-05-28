AR ?= ar
CC ?= gcc
CFLAGS = -Ideps -lm -O2 -pedantic -std=c99 -v -Wall -Wextra
PREFIX ?= /usr/local

DEPS += $(wildcard deps/*/*.c)
SRCS += $(wildcard src/*.c)

OBJS += $(DEPS:.c=.o)
OBJS += $(SRCS:.c=.o)

all: build

%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

build: build/lib/libgraph.a
	mkdir -p build/include/graph
	cp -f src/graph.h build/include/graph/graph.h

build/lib/libgraph.a: $(OBJS)
	mkdir -p build/lib
	$(AR) -crs $@ $^

clean:
	rm -fr *.o build deps/*/*.o src/*.o

example:
	$(CC) $(CFLAGS) -Ibuild/include -o example example.c -Lbuild/lib -lgraph

install: all
	mkdir -p $(PREFIX)/include
	mkdir -p $(PREFIX)/lib
	cp -f build/libgraph.a $(PREFIX)/lib/libgraph.a
	cp -f src/graph.h $(PREFIX)/include/graph.h

uninstall:
	rm -fr $(PREFIX)/lib/libgraph.a
	rm -fr $(PREFIX)/include/graph.h

.PHONY: build clean example install uninstall
