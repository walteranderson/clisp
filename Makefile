CFLAGS=-Wall -Wextra
CFILES=$(wildcard src/*.c)
CINCLUDE=$(wildcard src/*.h)
BINARY=clisp
CC=gcc

clisp: $(CFILES) $(CINCLUDE)
	$(CC) $(CFLAGS) -o $(BINARY) $(CFILES)

.PHONY: repl
repl: $(BINARY)
	rlwrap ./$(BINARY)

