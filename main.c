#include <time.h>
#include <stdio.h>
#include <mpi.h>
#include "structs.h"
#include "network_functions.h"

int main(int argc, char * argv[]){
        MPI_Init(&argc, &argv);
	int total_procs, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &total_procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("total_procs: %d\n", total_procs);

//	const int layer_size[] = {1,2,1};
//	Network * network = alloc_network(3, layer_size);
	Network * network = load_network(argv[1]);
	network->output[network->layer[0].node[0].node_offset] = 1;
	int i;
	clock_t start_time = clock();
	evaluate_network(network);
	double elapsed = (clock()-start_time)/(CLOCKS_PER_SEC*1.0f);
	print_network_layer_output(network, network->size-1);
	printf("%f\n", elapsed);
	save_network(network, argv[1]);
	free_network(network);
	return 0;
}
