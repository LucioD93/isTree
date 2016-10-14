#include "graph_tree.h"


/************
Funciones para estructura tipo lista simplemente enlazada
************/

/*
	Funcion para crear un nuevo nodo de tipo lista
*/
list* new_list(int value) {

	list *new_node;
	new_node = (list*) malloc(sizeof(list));
	
	if(!new_node){
		printf("ERROR: Reserva de memoria para nueva lista");
		exit(0);	
	}

	new_node -> value = value;
	new_node -> next = NULL;

	return new_node;
}

/*
	Procedimiento para agregar un nodo a una lista
	Se agrega el nodo como nuevo primer nodo
*/
void add_to_list(list **my_list, int value) {

	if (my_list == NULL) {
		*my_list = new_list(value);
	}
	else {
		list *new_node = new_list(value);
		new_node -> next = *my_list;
		*my_list = new_node;
	}
}

/*
	Procedimiento para agregar un valor a una lista evitando repetidos
*/
void add_to_list_no_repetition(list **my_list, int value) {
	
	if (*my_list == NULL) {
		*my_list = new_list(value);
	}
	else {
		if ((*my_list) -> value != value) {
			if ((*my_list) -> next == NULL) {
				(*my_list) -> next = new_list(value);
				return;
			}
			list *temp = *my_list;
			while (temp -> next != NULL && temp -> next -> value != value) {
				temp = temp -> next;
			}
			if (temp -> next == NULL) {
				temp -> next = new_list(value);
			}
		}
	}
}

/*
	Funcion para contar los nodos de una lista
*/
int size_of_list(list *my_list) {
	int counter = 0;
	list *temp = my_list;

	while (temp != NULL) {
		counter++;
		temp = temp -> next;
	}	

	return counter;
}

/*
	Funcion para determinar si una lista contiene un valor dado
*/
int list_contains(list *my_list, int value) {
	list *temp = my_list;
	while (temp != NULL && temp -> value != value) {
		temp = temp -> next;
	}
	return temp != NULL;
}

/*
	Procedimiento para eliminar un nodo especifico de una lista
*/
void remove_from_list(list **my_list, int value) {
	// Si el elemento se ubica en la primera posicion, mover el apuntador recibido a la
	// siguiente posicion
	if ( my_list != NULL && (*my_list) -> value == value) {
		list *temp = *my_list;
		*my_list = (*my_list) -> next;
		free(temp);
	}
	// Si no esta en la primera posicion buscarlo
	else if (my_list != NULL) {
		list *temp = (*my_list) -> next, *temp2 = *my_list;
		while (temp != NULL && temp -> value != value) {
			temp2 = temp;
			temp = temp -> next;
		}
		// Si se consigue el valor modificar el apuntador de la posicion anterior
		if (temp != NULL) {
			temp2 -> next = temp -> next;
			free(temp);
		}
	}
}

/*
	Procedimiento para liberar la memoria de una estructura tipo lista
*/
void free_list(list **my_list) {
	list *temp = *my_list;
	while (temp != NULL) {
		temp = temp -> next;
		free(*my_list);
		*my_list = temp;
	}
}

/*
	Procedimiento para mostrar una lista por consola
*/
void print_list(list *my_list) {
	list *temp = my_list;
	printf("Lista: ");
	while (temp != NULL) {
		printf("%i,", temp-> value);
		temp = temp -> next;
	}
	printf("\n");
}



/************
Funciones para estructura tipo lista de arcos
************/
/*
	Funcion para crear un nuevo nodo de tipo arco
*/
arcs* new_arcs(int from, int to) {

	arcs *new_arc;
	new_arc = (arcs*) malloc(sizeof(arcs));

	if(!new_arc){
		printf("ERROR: Reserva de memoria para nuevo arco");
		exit(0);	
	}

	new_arc -> from = from;
	new_arc -> to = to;
	new_arc -> next = NULL;

	return new_arc;
}

/*
	Procedimiento para agregar un nodo a una lista de arcos
*/
void add_to_arcs(arcs** my_arcs, int from, int to) {

	if(my_arcs == NULL) {
		*my_arcs = new_arcs(from,to);
	}
	else {
		arcs *new_arc = new_arcs(from,to);
		new_arc -> next = *my_arcs;
		*my_arcs = new_arc;		
	}
}

/*
	Procedimiento para liberar la memoria de una estructura tipo lista de arcos
*/
void free_arcs(arcs **my_arcs) {
	arcs *temp = *my_arcs;
	while (temp != NULL) {
		temp = temp -> next;
		free(*my_arcs);
		*my_arcs = temp;
	}
}

/*
	Procedimiento para mostrar una lista de arcos por consola
*/
void print_arcs(arcs *my_arcs) {
	arcs *temp = my_arcs;
	while (temp) {
		printf("(%i,%i), ",temp -> from, temp -> to);
		temp = temp -> next;
	}
	printf("\n");
}

/*
	Funcion para obtener la raiz del posible arbol,
	si no consigue una unica posible raiz retorna 0 para indicar que el grafo no es un arbol
*/
int get_tree_root(arcs* my_arcs) {
	// Primero se crean dos conjuntos, el de nodos que tienen lados saliendo
	// y el de nodos que tienen lados llegando
	arcs *temp_arcs = my_arcs;
	list *roots = NULL, * leaves = NULL;
	while (temp_arcs != NULL) {
		add_to_list_no_repetition(&roots, temp_arcs -> from);
		add_to_list_no_repetition(&leaves, temp_arcs -> to);
		temp_arcs = temp_arcs -> next;
	}

	// Al conjunto de nodos que tienen lados saliendo se le resta el otro conjunto
	list *temp_leaves = leaves;
	while (leaves != NULL) {
		remove_from_list(&roots,leaves -> value);
		leaves = leaves -> next;
	}
	free_list(&temp_leaves);

	// Si la cardinalidad del conjunto resultante es distinta de 1 el grafo no tiene raiz unica
	// por lo que no es un arbol, en caso contrario se retorna ese unico valor
	if (size_of_list(roots) != 1) {
		free_list(&roots);
		return 0;
	}
	else {
		int root = roots -> value;
		free_list(&roots);
		return root;
	}


}

/*
	Funcion para chequear que el grafo cumpe con la condicion de que para que un grafo sea un arbol
	se debe cumplir que el numero de vertices sea igual al numero de arcos mas uno
	La funcion retorna 1 si se cumple la condicion, 0 en caso contrario
*/
int check_arcs_quantity_condition(arcs *my_arcs) {
	int arc_counter = 0;
	list *nodes = NULL;
	arcs *temp = my_arcs;
	while (temp != NULL) {
		add_to_list_no_repetition(&nodes, temp -> from);
		add_to_list_no_repetition(&nodes, temp -> to);
		temp = temp -> next;
		arc_counter++;
	}

	int node_counter = size_of_list(nodes);
	free_list(&nodes);
	if (node_counter == arc_counter + 1) {
		return 1;
	}
	return 0;
}

/*
	Funcion para obtener todos los vecinos de un nodo especifico
*/
list* get_neighbours(arcs *my_arcs, int value) {
	list *my_list = NULL;
	arcs *temp = my_arcs;
	while (temp != NULL) {
		if (temp -> from == value) {
			add_to_list(&my_list, temp -> to);
		}
		temp = temp -> next;
	}

	return my_list;
}

/*
	Funcion recursiva que determina mediante una variacion del algoritmo de DFS
	si un grafo posee ciclos
*/
int has_cycle(arcs *my_arcs, list **visited, int value) {
	if (list_contains(*visited, value)) {
		// Si se visita un nodo que ya fue visitado anteriormente retornar false
		return 0;
	}
	else {
		int answer = 1;
		add_to_list(&*visited, value);
		list *neighbours = get_neighbours(my_arcs, value);
		if (neighbours == NULL) {
			return 1;
		}
		list *temp_list = neighbours;
		int node;
		while (temp_list != NULL) {
			node = neighbours -> value;
			neighbours = neighbours -> next;
			free(temp_list);
			temp_list = neighbours;
			// Visitar todos los vecinos del nodo actual
			answer = answer * has_cycle(my_arcs,&*visited, node);
		}
		return answer;
	}
}

/*
	Funcion que determina si un grafo es conexo
*/
int is_connected(arcs *my_arcs) {
	arcs *temp_arcs = my_arcs;
	list *nodes = NULL;
	while (temp_arcs != NULL) {
		// Agrupar todos los nodos del grafo
		add_to_list_no_repetition(&nodes, temp_arcs -> from);
		add_to_list_no_repetition(&nodes, temp_arcs -> to);
		temp_arcs = temp_arcs -> next;
	}
	list *temp_list = NULL;
	reacheable_nodes(my_arcs, &temp_list,get_tree_root(my_arcs));
	// Obtener la lista de todos los nodos alcanzables desde la raiz
	int n = size_of_list(temp_list), m = size_of_list(nodes);
	free_list(&temp_list);
	free_list(&nodes);
	// Si la lista de nodos y la lista de nodos alzanzables desde la raiz tienen la misma cantidad de elementos
	// el arbol es conexo
	return n == m;
}

/*
	Procedimiento recursivo que acumula en una lista los vertices alcanzables desde
	un nodo dado
*/
void reacheable_nodes(arcs* my_arcs, list **visited, int value) {
	if(list_contains(*visited, value)) {
		// Si el nodo ya fue visitado terminar la recursion
		return;
	}
	else {
		add_to_list(&*visited, value);
		list *neighbours = get_neighbours(my_arcs, value);
		if (neighbours == NULL) {
			// Si el nodo no tiene vecinos terminar la recursion
			return;
		}
		list *temp_list = neighbours;
		int node;
		while (temp_list != NULL) {
			node = neighbours -> value;
			neighbours = neighbours -> next;
			free(temp_list);
			temp_list = neighbours;
			// Visitar todos los nodos vecinos del nodo actul
			reacheable_nodes(my_arcs, &*visited, node);
		}
	}
}