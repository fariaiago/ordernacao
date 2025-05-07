CC ?= gcc
LIB = lib
EXE = ordem

$(EXE): $(LIB)/main.o $(LIB)/sort.o
	$(CC) -g -o $@ $^

$(LIB)/%.o: %.c
	$(CC) -g -c -o $@ $<

run:
	./$(EXE)

PHONY: run