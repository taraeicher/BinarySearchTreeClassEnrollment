CC=gcc -Wall -lm

all: classlist

classlist: utils.o bin_search_tree.o classlist.h classlist.c
	$(CC) -o classlist classlist.c utils.o bin_search_tree.o

utils.o: utils.h utils.c
	$(CC) -c utils.c

bin_search_tree.o: bin_search_tree.h bin_search_tree.c
	$(CC) -c bin_search_tree.c

tidy :
	rm -f utils.o bin_search_tree.o core

clean :
	rm -f classlist utils.o bin_search_tree.o core
