#include "backprop.h"
#include "layer.h"
#include "neuron.h"
#define ARCHITECTURE_FILE "architecture.txt"
#define TRAINING_DATA "train_data.txt"
#define TEST_DATA "test_data.txt"

layer *lay = NULL;
int num_layers;
int *num_neurons;
float alpha;
float *cost;
float full_cost;
float **input;
float **desired_outputs;
int num_training_ex;
int n = 1;
char choice;

int main(void)
{
    int i;

    srand(time(0));

    printf("Read architecture from file? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y')
    {
        read_architecture();
        // printf("Not implemented yet");
    }
    else
    {
        // Get number of layers
        printf("Enter the number of Layers in Neural Network:\n");
        scanf("%d", &num_layers);

        // Allocating memory for number of neurons in each layer dynamically
        num_neurons = (int *)malloc(num_layers * sizeof(int));
        memset(num_neurons, 0, num_layers * sizeof(int)); // Initialises the num_neurons array to 0

        // Get number of neurons per layer
        for (i = 0; i < num_layers; i++)
        {
            printf("Enter number of neurons in layer[%d]: \n", i + 1);
            scanf("%d", &num_neurons[i]);
        }
    }

    printf("\n");

    // Initialize the neural network module
    if (init() != SUCCESS_INIT)
    {
        printf("Error in Initialization...\n");
        exit(0);
    }

    // Get the learning rate
    printf("Enter the learning rate (Usually 0.15): \n");
    scanf("%f", &alpha);
    printf("\n");

    // Read the training data from file
    printf("Read training data from file? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y')
    {
        read_training_data();
    }
    else
    {

        // Get the number of training examples
        printf("Enter the number of training examples: \n");
        scanf("%d", &num_training_ex);
        printf("\n");

        // Allocating memory for input and desired output dynamically
        input = (float **)malloc(num_training_ex * sizeof(float *));
        for (i = 0; i < num_training_ex; i++) // Allocating memory for each row
        {
            input[i] = (float *)malloc(num_neurons[0] * sizeof(float));
        }
        // Allocating memory for desired output dynamically
        desired_outputs = (float **)malloc(num_training_ex * sizeof(float *));
        for (i = 0; i < num_training_ex; i++)
        {
            desired_outputs[i] = (float *)malloc(num_neurons[num_layers - 1] * sizeof(float));
        }
        // Allocating memory for cost dynamically
        cost = (float *)malloc(num_neurons[num_layers - 1] * sizeof(float));
        memset(cost, 0, num_neurons[num_layers - 1] * sizeof(float));

        // Get the training data
        get_inputs();
        get_desired_outputs();
    }
    // Train the network
    train_neural_net();
    test_nn(); // Test the network

    return 0;
}

int read_architecture()
{
    FILE *fp;
    int i;

    fp = fopen(ARCHITECTURE_FILE, "r");
    if (fp == NULL)
    {
        printf("Error in opening file...\n");
        return ERR_OPEN_FILE;
    }

    fscanf(fp, "%d", &num_layers);
    num_neurons = (int *)malloc(num_layers * sizeof(int));
    for (i = 0; i < num_layers; i++)
    {
        fscanf(fp, "%d", &num_neurons[i]);
    }

    fclose(fp);
    return SUCCESS_OPEN_FILE;
}

int init()
{
    if (create_architecture() != SUCCESS_CREATE_ARCHITECTURE)
    {
        printf("Error in creating architecture...\n");
        return ERR_INIT;
    }

    printf("Neural Network Created Successfully...\n\n");
    return SUCCESS_INIT;
}

// Read the training data from file
int read_training_data()
{
    FILE *fp;
    int i, j;

    fp = fopen(TRAINING_DATA, "r");
    if (fp == NULL)
    {
        printf("Error in opening file...\n");
        return ERR_OPEN_FILE;
    }

    fscanf(fp, "%d", &num_training_ex);
    // Allocating memory for input and desired output dynamically
    input = (float **)malloc(num_training_ex * sizeof(float *));
    for (i = 0; i < num_training_ex; i++) // Allocating memory for each row
    {
        input[i] = (float *)malloc(num_neurons[0] * sizeof(float));
    }
    // Allocating memory for desired output dynamically
    desired_outputs = (float **)malloc(num_training_ex * sizeof(float *));
    for (i = 0; i < num_training_ex; i++)
    {
        desired_outputs[i] = (float *)malloc(num_neurons[num_layers - 1] * sizeof(float));
    }
    // Allocating memory for cost dynamically
    cost = (float *)malloc(num_neurons[num_layers - 1] * sizeof(float));
    memset(cost, 0, num_neurons[num_layers - 1] * sizeof(float));

    for (i = 0; i < num_training_ex; i++)
    {
        for (j = 0; j < num_neurons[0]; j++)
        {
            fscanf(fp, "%f", &input[i][j]);
        }
    }
    for (i = 0; i < num_training_ex; i++)
    {
        for (j = 0; j < num_neurons[num_layers - 1]; j++)
        {
            fscanf(fp, "%f", &desired_outputs[i][j]);
        }
    }
    fclose(fp);
    return SUCCESS_OPEN_FILE;
}

// Get Inputs
void get_inputs()
{
    int i, j;

    for (i = 0; i < num_training_ex; i++)
    {
        printf("Enter the Inputs for training example[%d]:\n", i);

        for (j = 0; j < num_neurons[0]; j++)
        {
            scanf("%f", &input[i][j]);
        }
        printf("\n");
    }
}

// Get Labels
void get_desired_outputs()
{
    int i, j;

    for (i = 0; i < num_training_ex; i++)
    {
        for (j = 0; j < num_neurons[num_layers - 1]; j++)
        {
            printf("Enter the Desired Outputs (Labels) for training example[%d]: \n", i);
            scanf("%f", &desired_outputs[i][j]);
            printf("\n");
        }
    }
}

// Feed inputs to input layer
void feed_input(int i)
{
    int j;

    for (j = 0; j < num_neurons[0]; j++)
    {
        lay[0].neu[j].actv = input[i][j];
        printf("Input: %f\n", lay[0].neu[j].actv);
    }
}

// Create Neural Network Architecture
int create_architecture()
{
    int i = 0, j = 0;
    lay = (layer *)malloc(num_layers * sizeof(layer)); // Allocating memory for layers dynamically

    for (i = 0; i < num_layers; i++)
    {
        lay[i] = create_layer(num_neurons[i]);
        lay[i].num_neu = num_neurons[i];
        printf("Created Layer: %d\n", i + 1);
        printf("Number of Neurons in Layer %d: %d\n", i + 1, lay[i].num_neu);

        for (j = 0; j < num_neurons[i]; j++)
        {
            if (i < (num_layers - 1))
            {
                lay[i].neu[j] = create_neuron(num_neurons[i + 1]);
            }

            printf("Neuron %d in Layer %d created\n", j + 1, i + 1);
        }
        printf("\n");
    }

    printf("\n");

    // Initialize the weights
    if (initialize_weights() != SUCCESS_INIT_WEIGHTS)
    {
        printf("Error Initilizing weights...\n");
        return ERR_CREATE_ARCHITECTURE;
    }

    return SUCCESS_CREATE_ARCHITECTURE;
}

int initialize_weights(void)
{
    int i, j, k;

    if (lay == NULL)
    {
        printf("No layers in Neural Network...\n");
        return ERR_INIT_WEIGHTS;
    }

    printf("Initializing weights...\n");

    for (i = 0; i < num_layers - 1; i++)
    {

        for (j = 0; j < num_neurons[i]; j++) // For each neuron in the layer
        {
            for (k = 0; k < num_neurons[i + 1]; k++) // For each neuron in the next layer
            {
                // Initialize Output Weights for each neuron
                lay[i].neu[j].out_weights[k] = ((double)rand()) / ((double)RAND_MAX); // Randomly initialize weights
                printf("%d:w[%d][%d]: %f\n", k, i, j, lay[i].neu[j].out_weights[k]);  // Print the weights
                lay[i].neu[j].dw[k] = 0.0;                                            // Initialize the delta weights to 0
            }

            // Initialize Bias Weights for each neuron
            if (i > 0)
            {
                lay[i].neu[j].bias = ((double)rand()) / ((double)RAND_MAX);
            }
        }
    }
    printf("\n");
    // Initialize the weights for the output layer
    for (j = 0; j < num_neurons[num_layers - 1]; j++)
    {
        lay[num_layers - 1].neu[j].bias = ((double)rand()) / ((double)RAND_MAX);
    }

    return SUCCESS_INIT_WEIGHTS;
}

// Train Neural Network
void train_neural_net(void)
{
    int i;
    int it = 0;

    // Gradient Descent
    for (it = 0; it < 200; it++)
    {
        for (i = 0; i < num_training_ex; i++)
        {
            feed_input(i);
            forward_prop();
            back_prop(i);
            update_weights();
        }
    }
}

void update_weights(void)
{
    int i, j, k;

    for (i = 0; i < num_layers - 1; i++)
    {
        for (j = 0; j < num_neurons[i]; j++)
        {
            for (k = 0; k < num_neurons[i + 1]; k++)
            {
                // Update Weights
                lay[i].neu[j].out_weights[k] = (lay[i].neu[j].out_weights[k]) - (alpha * lay[i].neu[j].dw[k]);
            }

            // Update Bias
            lay[i].neu[j].bias = lay[i].neu[j].bias - (alpha * lay[i].neu[j].dbias);
        }
    }
}

void forward_prop(void)
{
    int i, j, k;

    for (i = 1; i < num_layers; i++)
    {
        for (j = 0; j < num_neurons[i]; j++)
        {
            lay[i].neu[j].z = lay[i].neu[j].bias;

            for (k = 0; k < num_neurons[i - 1]; k++)
            {
                lay[i].neu[j].z = lay[i].neu[j].z + ((lay[i - 1].neu[k].out_weights[j]) * (lay[i - 1].neu[k].actv));
            }

            // Relu Activation Function for Hidden Layers
            if (i < num_layers - 1)
            {
                if ((lay[i].neu[j].z) < 0)
                {
                    lay[i].neu[j].actv = 0;
                }

                else
                {
                    lay[i].neu[j].actv = lay[i].neu[j].z;
                }
            }

            // Sigmoid Activation function for Output Layer
            else
            {
                lay[i].neu[j].actv = 1 / (1 + exp(-lay[i].neu[j].z));
                printf("Output: %d\n", (int)round(lay[i].neu[j].actv));
                printf("\n");
            }
        }
    }
}

// Back Propogate Error
void back_prop(int p)
{
    int i, j, k;

    // Output Layer
    for (j = 0; j < num_neurons[num_layers - 1]; j++)
    {
        lay[num_layers - 1].neu[j].dz = (lay[num_layers - 1].neu[j].actv - desired_outputs[p][j]) * (lay[num_layers - 1].neu[j].actv) * (1 - lay[num_layers - 1].neu[j].actv);

        for (k = 0; k < num_neurons[num_layers - 2]; k++)
        {
            lay[num_layers - 2].neu[k].dw[j] = (lay[num_layers - 1].neu[j].dz * lay[num_layers - 2].neu[k].actv);
            lay[num_layers - 2].neu[k].dactv = lay[num_layers - 2].neu[k].out_weights[j] * lay[num_layers - 1].neu[j].dz;
        }

        lay[num_layers - 1].neu[j].dbias = lay[num_layers - 1].neu[j].dz;
    }

    // Hidden Layers
    for (i = num_layers - 2; i > 0; i--)
    {
        for (j = 0; j < num_neurons[i]; j++)
        {
            if (lay[i].neu[j].z >= 0)
            {
                lay[i].neu[j].dz = lay[i].neu[j].dactv;
            }
            else
            {
                lay[i].neu[j].dz = 0;
            }

            for (k = 0; k < num_neurons[i - 1]; k++)
            {
                lay[i - 1].neu[k].dw[j] = lay[i].neu[j].dz * lay[i - 1].neu[k].actv;

                if (i > 1)
                {
                    lay[i - 1].neu[k].dactv = lay[i - 1].neu[k].out_weights[j] * lay[i].neu[j].dz;
                }
            }

            lay[i].neu[j].dbias = lay[i].neu[j].dz;
        }
    }
}

// Test the trained network
void test_nn(void)
{
    int i;
    int it = 0;
    char c;

    printf("Read Test Data from File (y/n): ");
    scanf(" %c", &c);

    if (c == 'y')
    {
        read_test_data();
    }

    else
    {
        printf("Enter number of test cases: ");
        scanf("%d", &it);
        for (int ix = 0; ix < it; ix++)
        {
            printf("Enter input to test:\n");

            for (i = 0; i < num_neurons[0]; i++)
            {
                scanf("%f", &lay[0].neu[i].actv);
            }
            forward_prop();
        }
    }
}

// Read Test Data from File
void read_test_data(void)
{
    int i, it;
    FILE *fp;

    fp = fopen(TEST_DATA, "r");

    if (fp == NULL)
    {
        printf("Error opening file\n");
    }

    else
    {
        fscanf(fp, "%d", &it);
        for (int ix = 0; ix < it; ix++)
        {
            for (i = 0; i < num_neurons[0]; i++)
            {
                fscanf(fp, "%f", &lay[0].neu[i].actv);
            }
            forward_prop();
        }
    }
}

// Different Activation functions
float sigmoid(float x)
{
    return 1 / (1 + exp(-x));
}

float relu(float x)
{
    if (x < 0)
    {
        return 0;
    }
    else
    {
        return x;
    }
}

float tan_h(float x)
{
    return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}
