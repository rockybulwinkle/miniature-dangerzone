#include "structs.h"
#include "network_functions.h"

int main(int argc, char * argv[]){
//	const int layer_size[] = {1,2,1};
//	Network * network = alloc_network(3, layer_size);
	Network * network = load_network("default.net");
	network->layer[0].node[0].output=1;
	network->layer[0].node[1].output=6.92;
	evaluate_network(network);
	print_network_layer_output(network, network->size-1);
	save_network(network, "default.net");
	free_network(network);
	return 0;
}
