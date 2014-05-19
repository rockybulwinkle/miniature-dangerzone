#include "network_training.h"
#include "structs.h"

#define stuff 0

void LinearTraining(Network* network, int layerNum, int nodeNum){
	Layer layer = network->layer[layerNum];
	Node node = layer.node[nodeNum];
	int i;
	double output = network->layer[network->size -1].node[0].output;
	if(layer == size-1){ //output
		for(i=0; i<layer.size; i++){
			node.delta_weight[i] = stuff;
		}
	} 
	if(layer == size-2){ //last hidden unit
		for(i=0; i<layer.size; i++){
			node.delta_weight[i] = stuff;
		}
	}
}


