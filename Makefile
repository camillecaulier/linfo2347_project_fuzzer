CC=gcc
all: fuzzer.c help.c
	$(CC) -o fuzzer fuzzer.c
	$(CC) -o help help.c
clean:
	rm -f fuzzer
	rm -f help
