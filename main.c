#include <time.h>
#include <stdio.h>
#include "structs.h"
#include "network_functions.h"

int main(int argc, char * argv[]){
//	const int layer_size[] = {1,2,1};
//	Network * network = alloc_network(3, layer_size);
	Network * network = load_network(argv[1]);
	network->layer[0].node[0].output=1;
	int i;
	clock_t start_time = clock();
	evaluate_network(network);
	double elapsed = (clock()-start_time)/(CLOCKS_PER_SEC*1.0f);
	print_network_layer_output(network, network->size-1);
	printf("%f\n", elapsed);
	save_network(network, "default.net");
	free_network(network);
	return 0;
}
