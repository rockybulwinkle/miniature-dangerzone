#include <stdio.h>
#include "structs.h"
void LinearActivation(Network * network, int layer, Node * self){
	int node_index;
	double * net = &(network->net[self->node_offset]);
	*net = 0;
	double * prev_output = &(network->output[network->layer[layer-1].node[0].node_offset]);

	double * weight = &(network->weight[self->weight_offset]);

//	printf("node_offset=%d\n", self->node_offset);
	for (node_index=0; node_index < network->layer[layer-1].size; node_index++){
		*net += weight[node_index]*prev_output[node_index];

//		printf("%f*%f\n", prev_output[node_index], weight[node_index]);
	}
	network->output[self->node_offset] = *net;
}

