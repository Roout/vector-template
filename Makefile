CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wpedantic -Wextra -g -O0

main: main.o
	$(CC) $(CFLAGS) main.o -o main

main.o: main.c
	$(CC) $(CFLAGS) main.c -c

clean:
	rm *.o main

