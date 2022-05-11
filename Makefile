CC=gcc
all: src/fuzzer.c
	$(CC) -o fuzzer src/fuzzer.c -D_LARGEFILE64_SOURCE
clean:
	rm -f fuzzer
	rm -f *.tar

