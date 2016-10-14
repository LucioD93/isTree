#include "graph_tree.h"

int main(int argc, char *argv[])
{
        if (argc != 2) {
                printf("Error en la entrada de parametros\n");
                return 0;
        }
	printf("INPUT: %s\n",argv[1]);
        // Abrir el archivo recibido por parametros
	FILE *input_file = fopen(argv[1], "r");
        if (input_file != 0)
        {
                int from, to, graph_counter = 1;
                arcs *my_arcs = NULL;
                list *my_list = NULL;
                while (1) {
                        // Leer un par ordenado
                        fscanf(input_file, "%i", &from);
                        fscanf(input_file, "%i", &to);
                        if ((from != 0 && to != 0) && (from != -1 && to != -1)) {
                                add_to_arcs(&my_arcs,from,to);
                        }
                        else if (from != -1 && to != -1){
                                printf("Caso %i ", graph_counter++);
                                if (check_arcs_quantity_condition(my_arcs)) {
                                        int root = get_tree_root(my_arcs);
                                        if (root != 0) {
                                                int is_cyclic = has_cycle(my_arcs, &my_list, root);
                                                free_list(&my_list);
                                                if (is_cyclic && is_connected(my_arcs))
                                                        // Si cumple con todas las condiciones el grafo es un arbol
                                                        printf(IS_TREE_MESSAGE);
                                                else 
                                                        printf(NOT_TREE_MESSAGE);
                                        }
                                        else {
                                                printf(NOT_TREE_MESSAGE); 
                                        }
                                }
                                else {
                                        printf(NOT_TREE_MESSAGE);
                                }
                                free_arcs(&my_arcs);
                        }
                        if (from == -1 && to == -1) {
                                break;
                        }
                }
                fclose(input_file);
        }
        else
        {
                printf("ERROR: FILE NOT FOUND\n");
        }
        return 0;
}
