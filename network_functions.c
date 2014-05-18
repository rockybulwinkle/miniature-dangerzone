#include "structs.h"
#include "activation_functions.h"

void evaluate_network(Network * network){
	//assumes you've already set the input node's values
	int layer_index;
	int node_index;
	int weight_index;

	for (layer_index=1; layer_index < network->size; layer_index++){
		Layer * current_layer = network->layer[layer_index];
		Layer * prev_layer = network->layer[layer_index-1];
		
		Node * current_node = current_layer->node;

		for (node_index=0; node_index < current_layer->size; node_index++){
			current_node->function->act(prev_layer, current_node);
			current_node++;
		}
	}

}

Network * create_network(){

}

