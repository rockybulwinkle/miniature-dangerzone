#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Node{
	int weight_offset;
	int node_offset;
	int function;
}Node;

typedef struct Layer{
	Node * node;
	int size;
} Layer;

typedef struct Network{
	double * weight;
	double * delta_weight;
	double * output;
	double * net;
	int num_nodes;
	int num_weights;
	Layer * layer;
	int size;
} Network;

#endif

