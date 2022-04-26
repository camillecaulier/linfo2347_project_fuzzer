CC=gcc
all: fuzzer.c
	$(CC) -o fuzzer fuzzer.c
clean:
	rm -f fuzzer