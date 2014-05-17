AR ?= ar
CC ?= gcc
CFLAGS = -Ideps -lm -O3 -pedantic -std=c99 -Wall -Wextra
PREFIX ?= /usr/local

DEPS += $(wildcard deps/*/*.c)
SRCS += $(wildcard src/*.c)

OBJS += $(DEPS:.c=.o)
OBJS += $(SRCS:.c=.o)

all: build/libgraph.a

%.o: %.c
	@$(CC) $< $(CFLAGS) -c -o $@

build/libgraph.a: $(OBJS)
	@mkdir -p build
	@$(AR) -crs $@ $^

clean:
	@rm -fr *.o build deps/*/*.o src/*.o

install: all
	@cp -f build/libgraph.a $(PREFIX)/lib/libgraph.a
	@cp -f src/graph.h $(PREFIX)/include/graph.h

uninstall:
	@rm -fr $(PREFIX)/lib/libgraph.a
	@rm -fr $(PREFIX)/include/graph.h

.PHONY: clean install uninstall
