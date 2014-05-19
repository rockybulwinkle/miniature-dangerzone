#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H
#define LINEAR_ACTIVATION 0
void  LinearActivation(Network * network, int layer, Node * self);

void (*ACTIVATION_FUNCTION[])(Network * network, int, Node *) = {LinearActivation};
const void (*TRAINING_FUNCTION[])(Network *, int, int) = {};



#endif
