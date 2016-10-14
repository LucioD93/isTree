all: istree clean

istree: main.o graph_tree.o graph_tree.h
	gcc -o istree main.o graph_tree.o 

main.o: main.c graph_tree.h
	gcc -Wall -Wextra -c main.c

graph_tree.o: graph_tree.c graph_tree.h
	gcc -Wall -Wextra -c graph_tree.c

debug: main.c graph_tree.c
	gcc -g -c main.c
	gcc -g -c graph_tree.c
	gcc -o istree main.o graph_tree.o

clean:
	rm -f *.o
