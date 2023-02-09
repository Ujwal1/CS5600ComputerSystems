runMultiprocessing: main.c polybius.c
	gcc -o runMultiprocessing main.c polybius.c

cipher: cipher.c polybius.c
	gcc -o cipher cipher.c polybius.c

all: cipher runMultiprocessing

clean:
	rm -f cipher runMultiprocessing
