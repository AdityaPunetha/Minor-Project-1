#ifndef BACKPROP_H
#define BACKPROP_H

#include "layer.h"

#define ERR_OPEN_FILE 1
#define SUCCESS_OPEN_FILE 0

#define SUCCESS_INIT 0
#define ERR_INIT 1

#define SUCCESS_INIT_WEIGHTS 0
#define ERR_INIT_WEIGHTS 1

#define SUCCESS_UPDATE_WEIGHTS 0

#define SUCCESS_CREATE_ARCHITECTURE 0
#define ERR_CREATE_ARCHITECTURE 1

int read_architecture(void);

int init(void);

int create_architecture(void);
int initialize_weights(void);

int read_training_data(void);
void read_test_data(void);

float sigmoid(float x);
float relu(float x);
float tan_h(float x);

void feed_input(int i);
void train_neural_net(void);
void forward_prop(void);
void back_prop(int p);
void update_weights(void);
void get_inputs(void);
void get_desired_outputs(void);
void test_nn(void);

int initialize_dummy_weights(void);

#endif
