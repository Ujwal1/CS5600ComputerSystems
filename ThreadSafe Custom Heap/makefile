CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11

SRC = pm_heap.c pm_heap_test.c
OBJ = $(SRC:.c=.o)

all: pm_heap_test

pm_heap_test: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) pm_heap_test

run: pm_heap_test
	./pm_heap_test

