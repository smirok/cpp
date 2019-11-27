.PHONY: all clean

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -I include

lab_03: main.o clist.o | obj
	gcc $(CFLAGS) -o bin/lab_03 obj/main.o obj/clist.o

all:lab_03

main.o: src/main.c | obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o

clist.o: src/clist.c | obj
	gcc $(CFLAGS) -c src/clist.c -o obj/clist.o

obj:
	mkdir bin;
	mkdir obj;
clean:
	rm -rf bin obj lab;
