.PHONY: all clean

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -I include

lab_04: main.o mergesort.o | obj
	gcc $(CFLAGS) -o bin/lab_04 obj/main.o obj/mergesort.o

all:lab_04

main.o: src/main.c | obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o

mergesort.o: src/mergesort.c | obj
	gcc $(CFLAGS) -c src/mergesort.c -o obj/mergesort.o

obj:
	mkdir bin;
	mkdir obj;
clean:
	rm -rf bin obj;

