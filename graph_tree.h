#ifndef graph_tree
#define graph_tree

#include <stdlib.h>
#include <stdio.h>

#define IS_TREE_MESSAGE "es una arborescencia\n"
#define NOT_TREE_MESSAGE "no es una arborescencia\n"

/*
	Estructura tipo lista de enteros simplemente enlazada
*/
typedef struct _list {
	int value;
	struct _list *next;
} list;

/*
	Estructura tipo lista de pares ordenados simplemente enlazada que representara un grafo
*/
typedef struct _arcs {
	int from;
	int to;
	struct _arcs *next;
} arcs;

/*
	Funciones de estructuras tipo lista
*/
list* new_list(int);
void add_to_list(list**, int);
void add_to_list_no_repetition(list**, int);
void print_list(list*);
void remove_from_list(list**, int);
int list_contains(list*,int);
void free_list(list**);

/*
	Funciones de estructuras tipo grafo
*/
arcs* new_arcs(int, int);
void add_to_arcs(arcs**, int, int);
void print_arcs(arcs*);
int check_arcs_quantity_condition(arcs*);
int get_tree_root(arcs*);
void free_arcs(arcs**);
int has_cycle(arcs*, list**, int);
void reacheable_nodes(arcs*, list**, int);
list *get_neighbours(arcs*, int);
int is_connected(arcs*);

#endif
