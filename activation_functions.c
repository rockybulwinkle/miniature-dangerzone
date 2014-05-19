#include "structs.h"

void LinearActivation(Layer * previous_layer, Node * self){
	int node_index;
	self->net=0;
	for (node_index=0; node_index < previous_layer->size; node_index++){
		self->net += previous_layer->node[node_index].output*self->weight[node_index];
	}
	self->output = self->net;
}

