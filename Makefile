CC = gcc
CFLAGS = -g -Wall -Wextra -std=c11 -I./include -I./src/defs -I./src/internal_api -I./src/init -I./src/user_api

SRC = src/init/init.c \
      src/internal_api/intern_api.c \
      src/user_api/usr_api.c

build/libbettercurses.a: $(SRC)
	mkdir -p build
	$(CC) $(CFLAGS) -c $(SRC)
	ar rcs build/bettercurses.o *.o
	rm *.o
.PHONY: test test-hello test-colors

test: test-hello test-colors

test-hello: build/bettercurses.o
	$(CC) $(CFLAGS) examples/hello-world.c -I./include ./build/bettercurses.o -o build/test-hello
	./build/test-hello

test-colors: build/bettercurses.o
	$(CC) $(CFLAGS) examples/colors.c -I./include ./build/bettercurses.o -o build/test-colors
	./build/test-colors

clean:
	rm -rf build/
