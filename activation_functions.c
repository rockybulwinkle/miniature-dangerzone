#include "structs.h"

void LinearActivation(Network * network, Layer * previous_layer, Node * self){
	int node_index;
	network->net[self->node_offset]=0;
	for (node_index=0; node_index < previous_layer->size; node_index++){
		network->net[self->node_offset] += network->output[previous_layer->node[node_index].node_offset]*network->weight[self->weight_offset+node_index];
	}
	network->output[self->node_offset] = network->net[self->node_offset];
}

