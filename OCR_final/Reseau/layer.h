#ifndef LAYER_H
#define LAYER_H

#include "neuron.h"


typedef struct layer_t
{
	int num_neu;
	struct neuron_t *neu; 
	//void (*dtor)(layer) = &destructor;
} layer;

layer create_layer(int num_neurons);

#endif