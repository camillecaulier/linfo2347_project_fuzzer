CC=gcc
all: src/fuzzer.c
	$(CC) -o fuzzer src/fuzzer.c
clean:
	rm -f fuzzer

