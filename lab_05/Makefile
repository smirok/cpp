.PHONY: all clean

CFLAGS = -Wall -Wextra -Werror -I include

//-fsanitize=address -fsanitize=undefined

lab_05: main.o clist.o point_list.o | obj
	gcc $(CFLAGS) -o bin/lab_05 obj/main.o obj/clist.o obj/point_list.o

all:lab_05

main.o: src/main.c | obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o

clist.o: src/clist.c | obj
	gcc $(CFLAGS) -c src/clist.c -o obj/clist.o

point_list.o: src/point_list.c | obj
	gcc $(CFLAGS) -c src/point_list.c -o obj/point_list.o

obj:
	mkdir bin;
	mkdir obj;
clean:
	rm -rf bin obj lab;
