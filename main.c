#include "structs.h"
#include "network_functions.h"

int main(int argc, char * argv[]){
	const int layer_size[] = {1,2,1};
	Network * network = alloc_network(3, layer_size);
	evaluate_network(network);
	//print_network_layer_output(network, network->size-1);
	free_network(network);
	return 0;
}
