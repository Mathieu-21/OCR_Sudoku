#ifndef BACKPROP_H
#define BACKPROP_H

#include "layer.h"

#define SUCCESS_INIT 0
#define ERR_INIT 1

#define SUCCESS_DINIT 0
#define ERR_DINIT 1

#define SUCCESS_INIT_WEIGHTS 0
#define ERR_INIT_WEIGHTS 1

#define SUCCESS_UPDATE_WEIGHTS 0

#define SUCCESS_CREATE_ARCHITECTURE 0
#define ERR_CREATE_ARCHITECTURE 1




int initialize_weights(void);
int create_architecture(void);
int init(void);
void feed_input(int i);
void update_weights(void);
void forward_prop(void);
void compute_cost(int i);
void back_prop(int p);
void train_neural_net(void);
void test_nn(void);
int dinit(void);

//void get_inputs(void);
//void get_desired_outputs(void);


//int initialize_dummy_weights(void);


#endif



