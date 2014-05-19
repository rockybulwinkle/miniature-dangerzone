#include "structs.h"

void LinearActivation(Network * network, Layer * previous_layer, Node * self){
	int node_index;
	double * net = &(network->net[self->node_offset]);
	*net = 0;
	double * prev_output = &(network->output[previous_layer->node[0].weight_offset]);
	double * weight = &(network->weight[self->weight_offset]);

	for (node_index=0; node_index < previous_layer->size; node_index++){
		*net += weight[node_index]*prev_output[node_index];
	}
	network->output[self->node_offset] = *net;
}

