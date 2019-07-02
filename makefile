COMPILER = gcc -pedantic -std=c99 -Wall -fsanitize=address

all:
	$(COMPILER) main.c lectura.c queries.c transporteADT.c

debug: COMPILER += -DDEBUG=1
debug: all
