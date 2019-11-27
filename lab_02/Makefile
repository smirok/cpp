.PHONY: all clean

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -I include

lab_02: test.o str.o test_str.o | obj
	gcc $(CFLAGS) -o bin/lab_02 obj/test.o obj/str.o obj/test_str.o

all:lab_02

str.o: src/str.c | obj
	gcc $(CFLAGS) -c src/str.c -o obj/str.o

test_str.o: src/test_str.c | obj
	gcc $(CFLAGS) -c src/test_str.c -o obj/test_str.o

test.o: src/test.c | obj
	gcc $(CFLAGS) -c src/test.c -o obj/test.o

obj:
	mkdir bin;
	mkdir obj;
clean:
	rm -rf bin obj lab;
