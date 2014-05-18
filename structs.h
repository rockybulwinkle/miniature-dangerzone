#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct ActivationFunction ActivationFunction;

typedef struct Node{
	double * weight,delta_weight;
	double output;
	double net;
	ActivationFunction * function;
}Node;

typedef struct Layer{
	Node * node;
	int size;
} Layer;

typedef struct Network{
	Layer * layer;
	int size;
} Network;

typedef struct ActivationFunction{
	void (*act)(Layer *,Node *); //previous layer, self
	void (*train)(Network *, int, int); //Network, layer number, node number
} ActivationFunction;

#endif

