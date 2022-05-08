CC=gcc
all: src/fuzzer.c help.c
	$(CC) -o fuzzer src/fuzzer.c
clean:
	rm -f fuzzer

