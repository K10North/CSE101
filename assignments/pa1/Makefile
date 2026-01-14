TARGETS=ListTest Lex
CC=gcc
CFLAGS=-Wall -g -std=c17

all: $(TARGETS)

ListTest: ListTest.o List.o
	gcc $(CFLAGS) -o $@ ListTest.o List.o 

ListTest.o: List.h ListTest.c
	gcc $(CFLAGS) -c ListTest.c

List.o: List.h List.c
	gcc $(CFLAGS) -c List.c

Words: Words.o List.o
	$(CC) $(CFLAGS) -o $@ Words.o List.o

Words.o: Words.c List.h
	gcc $(CFLAGS) -c Words.c

clean:
	@rm -f $(TARGETS) *.o

check: ListTest
	valgrind --leak-check=full ListTest
