CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./include -I./src/defs -I./src/internal_api -I./src/shared_api -I./src/init -I./src/user_api

SRC = src/init/init.c \
      src/internal_api/intern_api.c \
      src/shared_api/shared_api.c \
      src/user_api/usr_api.c

build/libbettercurses.a: $(SRC)
	mkdir -p build
	$(CC) $(CFLAGS) -c $(SRC)
	ar rcs build/libbettercurses.a *.o
	rm *.o

clean:
	rm -rf build/
