CC=gcc
CFLAGS=-I.

qtest: queuetest.c queue.c
	$(CC) -o qtest queuetest.c queue.c $(CFLAGS)
	
clean:
	rm -f qtest