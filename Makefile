##
# INFO603 TP Exercice 1
# Lucas CHARDONNET - Yohann THEPAUT
# Makefile

CFLAGS = -Wall -Wextra -pedantic -std=gnu99 -O3 -Wno-unused-parameter

CC = gcc $(CFLAGS)
#CC = clang $(CFLAGS)

all: partition boustrophedon graphe

partition: partition.o utils.o
	$(CC) -o $@ $^

boustrophedon: boustrophedon.o utils.o
	$(CC) -o $@ $^

graphe: graphe.o utils.o

graphe2: graphe2.o utils.o
	$(CC) -o $@ $^

%.o: %.c %.h
	$(CC) -c $< -o $@

clean:
	rm -f partition boustrophedon graphe *.o a.out
