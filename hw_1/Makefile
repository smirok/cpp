.PHONY: all clean

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -I include

hw_1: main.o bmp.o | obj
	gcc $(CFLAGS) -o bin/hw_1 obj/main.o obj/bmp.o 

all:hw_1

main.o: src/main.c | obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o

bmp.o: src/bmp.c | obj
	gcc $(CFLAGS) -c src/bmp.c -o obj/bmp.o

obj:
	mkdir bin;
	mkdir obj;
clean:
	rm -rf bin obj;
