#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H
#define LINEAR_ACTIVATION 0
void LinearActivation(Layer * previous_layer, Node * self);

void (*ACTIVATION_FUNCTION[])(Layer *, Node *) = {LinearActivation};
const void (*TRAINING_FUNCTION[])(Network *, int, int) = {};



#endif
