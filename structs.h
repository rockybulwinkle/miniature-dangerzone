
typedef struct Node{
	double * weight,delta_weight;
	double value;
	void (*activation_function)(Layer *,Node *); //previous layer, self
}Node;

typedef struct Layer{
	Node * node;
	int size;
} Layer;

typedef struct Network{
	Layer * layer;
	int size;
} Network;


