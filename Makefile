CC=gcc
all: src/fuzzer.c help.c
	$(CC) -o fuzzer fuzzer.c
clean:
	rm -f fuzzer

