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
		
		Node * current_node = current_layer->node;

		for (node_index=0; node_index < current_layer->size; node_index++){
			printf("Layer: %d Node: %d\n", layer_index, node_index);
			(*(ACTIVATION_FUNCTION[current_node->function]))(network, layer_index, current_node);
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
	int num_weights = 0;
	int num_nodes = 0;

	for (layer_index=0; layer_index < num_layers; layer_index++){ //we must allocate each layer, and the nodes inside each layer
		network->layer[layer_index].size = nodes_in_each_layer[layer_index];
		network->layer[layer_index].node = calloc(network->layer[layer_index].size, sizeof(Node));
		for (node_index = 0; node_index < network->layer[layer_index].size; node_index++){
			if (layer_index > 0){
				network->layer[layer_index].node[node_index].weight_offset = num_weights;
				num_weights += network->layer[layer_index-1].size;
			}
			network->layer[layer_index].node[node_index].node_offset = num_nodes;
			network->layer[layer_index].node[node_index].function = LINEAR_ACTIVATION;
		}
		num_nodes += 1;
	}
	
	network->weight = calloc(num_weights, sizeof(double));
	network->delta_weight = calloc(num_weights, sizeof(double));

	network->output = calloc(num_nodes, sizeof(double));
	network->net = calloc(num_nodes, sizeof(double));

	network->num_weights = num_weights;
	network->num_nodes = num_nodes;
	return network;
}

void free_network(Network * network){
	int layer_index;
	for (layer_index = 0; layer_index < network->size; layer_index++){
		free(network->layer[layer_index].node);
	}
	free(network->layer);
	free(network->weight);
	free(network->delta_weight);
	free(network->output);
	free(network->net);
	free(network);
}

void print_network_layer_output(Network * network, int layer_index){
	int node_index;
	if (!(layer_index<network->size)){
		fprintf(stderr, "Print network: layer index out of range.  Layer is %d, network size is %d\n", layer_index, network->size);
		exit(-1);
	}
	
	for (node_index = 0; node_index < network->layer[layer_index].size; node_index++){
		printf("%f\t", network->output[network->layer[layer_index].node[node_index].node_offset]);
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
				fprintf(fp, "%f\t", network->weight[network->layer[layer_index].node[node_index].weight_offset+weight_index]);
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

	int num_nodes = 0;
	int num_weights = 0;
	for (layer_index = 0; layer_index < network->size; layer_index += 1){
		fscanf(fp, "%d", &(network->layer[layer_index].size));
		network->layer[layer_index].node = calloc(network->layer[layer_index].size, sizeof(Node));
		num_nodes += network->layer[layer_index].size;
		if (layer_index > 0){
			num_weights += network->layer[layer_index-1].size*network->layer[layer_index].size;
		}
	}

	network->weight = calloc(num_weights, sizeof(double));
	network->delta_weight = calloc(num_weights, sizeof(double));

	network->output = calloc(num_nodes, sizeof(double));
	network->net = calloc(num_nodes, sizeof(double));

	network->num_weights = num_weights;
	network->num_nodes = num_nodes;

	num_nodes = 0;
	num_weights = 0;
	for (layer_index = 0; layer_index < network->size; layer_index++){
		for(node_index = 0; node_index < network->layer[layer_index].size; node_index ++){
			if (layer_index > 0){
				network->layer[layer_index].node[node_index].weight_offset = num_weights;
				
				for (weight_index = 0; weight_index < network->layer[layer_index-1].size; weight_index++){
					fscanf(fp, "%lf", &(network->weight[num_weights]));
					num_weights+=1;
				}
			}
			network->layer[layer_index].node[node_index].node_offset=num_nodes;
			fscanf(fp, "%d", &(network->layer[layer_index].node[node_index].function));
			num_nodes += 1;
		}
	}


	fclose(fp);
	return network;
}


