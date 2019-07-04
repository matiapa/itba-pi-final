COMPILER = gcc -pedantic -std=c99 -Wall -fsanitize=address
OUT = transporte

all:
	$(COMPILER) src/main.c src/lectura.c src/queries.c src/transporteADT.c -o transporte

debug: COMPILER += -DDEBUG=1
debug: all
