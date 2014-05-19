#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "activation_functions.h"

void evaluate_network(Network * network){
	//assumes you've already set the input node's values
	int layer_index;
	int node_index;

	for (layer_index=1; layer_index < network->size; layer_index++){
		Layer * current_layer = &(network->layer[layer_index]);
		Layer * prev_layer = &(network->layer[layer_index-1]);
		
		Node * current_node = current_layer->node;

		for (node_index=0; node_index < current_layer->size; node_index++){
			(*(ACTIVATION_FUNCTION[current_node->function]))(prev_layer, current_node);
			current_node++;
		}
	}

}

Network * alloc_network(int num_layers, const int * nodes_in_each_layer)
{
	Network * network = malloc(sizeof(Network));  //allocate for the network
	network->size = num_layers;
	network->layer = malloc(sizeof(Layer)*network->size);
	int layer_index;
	int node_index;

	for (layer_index=0; layer_index < num_layers; layer_index++){ //we must allocate each layer, and the nodes inside each layer
		network->layer[layer_index].size = nodes_in_each_layer[layer_index];
		network->layer[layer_index].node = calloc(network->layer[layer_index].size, sizeof(Node));
		for (node_index = 0; node_index < network->layer[layer_index].size; node_index++){
			if (layer_index > 0){
				network->layer[layer_index].node[node_index].weight = calloc(network->layer[layer_index-1].size, sizeof(double));
				network->layer[layer_index].node[node_index].delta_weight = calloc(network->layer[layer_index-1].size, sizeof(double));
				network->layer[layer_index].node[node_index].function=LINEAR_ACTIVATION;	
			} else{
				network->layer[layer_index].node[node_index].weight = NULL;
				network->layer[layer_index].node[node_index].delta_weight = NULL;
				network->layer[layer_index].node[node_index].function=-1;
			}
		}
	}
	return network;
}

void free_network(Network * network){
	int layer_index;
	int node_index;
	for (layer_index = 0; layer_index < network->size; layer_index++){
		for (node_index = 0; node_index < network->layer[layer_index].size; node_index++){
			free(network->layer[layer_index].node[node_index].weight);
			free(network->layer[layer_index].node[node_index].delta_weight);
		}
		free(network->layer[layer_index].node);
	}
	free(network->layer);
	free(network);
}

void print_network_layer_output(Network * network, int layer_index){
	int node_index;
	if (!(layer_index<network->size)){
		fprintf(stderr, "Print network: layer index out of range.  Layer is %d, network size is %d\n", layer_index, network->size);
		exit(-1);
	}
	
	for (node_index = 0; node_index < network->layer[layer_index].size; node_index++){
		printf("%f\t", network->layer[layer_index].node[node_index].output);
	}
	printf("\n");
}

void save_network(Network * network, char * file_name){
	int layer_index;
	int node_index;
	int weight_index;

	FILE * fp = fopen(file_name, "w");
	if (fp == NULL){
		fprintf(stderr, "Failed to open save file for writing");
		exit(-1);
	}

	fprintf(fp, "%d\n", network->size);
	for (layer_index = 0; layer_index < network->size; layer_index += 1){
		fprintf(fp, "%d ", network->layer[layer_index].size);
	}
	fprintf(fp, "\n");

	for (layer_index = 1; layer_index < network->size; layer_index++){
		fprintf(fp, "\n");
		for(node_index = 0; node_index < network->layer[layer_index].size; node_index ++){
			for (weight_index = 0; weight_index < network->layer[layer_index-1].size; weight_index++){
				fprintf(fp, "%f\t", network->layer[layer_index].node[node_index].weight[weight_index]);
			}
			fprintf(fp, "\n%d\n", network->layer[layer_index].node[node_index].function);
		}
	}

	fclose(fp);

}


Network * load_network(char * file_name){
	int layer_index;
	int node_index;
	int weight_index;

	FILE * fp = fopen(file_name, "r");
	if (fp == NULL){
		fprintf(stderr, "Failed to open save file for reading");
		exit(-1);
	}

	Network * network = malloc(sizeof(Network));

	fscanf(fp, "%d", &(network->size));
	network->layer = malloc(sizeof(Layer)*network->size);

	for (layer_index = 0; layer_index < network->size; layer_index += 1){
		fscanf(fp, "%d", &(network->layer[layer_index].size));
		network->layer[layer_index].node = calloc(network->layer[layer_index].size, sizeof(Node));
	}

	for (layer_index = 0; layer_index < network->size; layer_index++){
		for(node_index = 0; node_index < network->layer[layer_index].size; node_index ++){
			if (layer_index == 0){
				network->layer[layer_index].node[node_index].weight=NULL;
				network->layer[layer_index].node[node_index].delta_weight=NULL;
				network->layer[layer_index].node[node_index].function=-1;
				continue;
			} else{
				network->layer[layer_index].node[node_index].weight = malloc(sizeof(double)*network->layer[layer_index-1].size);
				network->layer[layer_index].node[node_index].delta_weight= malloc(sizeof(double)*network->layer[layer_index-1].size);
			}
			for (weight_index = 0; weight_index < network->layer[layer_index-1].size; weight_index++){
				fscanf(fp, "%lf\t", &(network->layer[layer_index].node[node_index].weight[weight_index]));
			}
			fscanf(fp, "\n%d\n", &(network->layer[layer_index].node[node_index].function));
		}
	}

	fclose(fp);
	return network;
}


