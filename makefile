COMPILER = gcc -pedantic -std=c99 -Wall -fsanitize=address -g
OUT = transporte

all:
	$(COMPILER) src/main.c src/lectura.c src/queries.c src/transporteADT.c -o $(OUT)

debug: COMPILER += -DDEBUG=1
debug: all

ns: COMPILER = gcc -pedantic -std=c99 -Wall
ns: all
