#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Node{
	double * weight;
	double * delta_weight;
	double output;
	double net;
	int function;
}Node;

typedef struct Layer{
	Node * node;
	int size;
} Layer;

typedef struct Network{
	Layer * layer;
	int size;
} Network;

#endif

