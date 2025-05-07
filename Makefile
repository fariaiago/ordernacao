CC ?= gcc
LIB = lib
EXE = ordem

$(EXE): $(LIB)/main.o $(LIB)/sort.o
	$(CC) -o $@ $^

$(LIB)/%.o: %.c
	$(CC) -c -o $@ $<

run:
	./$(EXE)

PHONY: run