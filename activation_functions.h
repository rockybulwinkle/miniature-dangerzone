#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H
#define LINEAR_ACTIVATION 0
void LinearActivation(Network * network, Layer * previous_layer, Node * self);

void (*ACTIVATION_FUNCTION[])(Network * network, Layer *, Node *) = {LinearActivation};
const void (*TRAINING_FUNCTION[])(Network *, int, int) = {};



#endif
