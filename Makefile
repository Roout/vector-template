CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wpedantic -Wextra -g -O0

main: main.o ring_buffer.o
	$(CC) $(CFLAGS) main.o ring_buffer.o -o main

main.o: main.c ring_buffer.o
	$(CC) $(CFLAGS) main.c -c

ring_buffer.o: ring_buffer.c
	$(CC) $(CFLAGS) ring_buffer.c -c

clean:
	rm *.o main

