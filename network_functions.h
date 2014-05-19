#ifndef NETWORK_FUNCTIONS_H
#define NETWORK_FUNCTIONS_H
void evaluate_network(Network * network);
Network * alloc_network (int num_layers, const int * nodes_in_each_layer);
void free_network (Network * network);
void print_network_layer_output(Network * network, int layer_index);
void save_network(Network * network, char * file_name);
Network * load_network(char * file_name);
#endif
