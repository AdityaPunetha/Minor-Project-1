# Project Title

Implementation of neural network in C/C++ from scratch

## Abstract

Neural networks, also known as artificial neural networks (ANNs) are a subset of machine
learning and are at the heart of deep learning algorithms. Most sample neural networks posted
online are written in Python and use powerful math libraries such as NumPy. While the code
in these samples is clean and succinct, it can be hard to grasp the details behind backpropagation when complex matrix operations are collapsed into a single statement. When you
are forced to write out the loops in C, the math behind the concepts becomes much clearer.
Implementing backpropagation in C will give us detailed insights into how changing the
weights and bias changes the overall behaviour of the network.

## Introduction

Artificial neural networks (ANNs) are comprised of a node layers, containing an input layer,
one or more hidden layers, and an output layer. Each node, or artificial neuron, connects to
another and has an associated weight and threshold. If the output of any individual node is
above the specified threshold value, that node is activated, sending data to the next layer of the
network. Otherwise, no data is passed along to the next layer of the network.
Fundamentally activation of a neural network is a series of linear algebra, if we can implement
it in C/C++ along with training, forward propagation, loss calculation and back propagation
algorithm we can implement a fully functional general purpose deep learning network. A neural
network and its training loop offer following functionalities: forward propagation as the name
suggests, the input data is fed in the forward direction through the network. Each hidden layer
accepts the input data, processes it as per the activation function and passes to the successive
layer; loss/cost function which reduces all the various good and bad aspects of a complex
system down to a single number, a scalar value, which allows candidate solutions to be ranked
and compared; Backpropagation which allows us to calculate and attribute the error associated
with each neuron, allowing us to adjust and fit the parameters of the model(s) appropriately.
The backpropagation algorithm of choice would be the stochastic gradient descent (SGD), in
which weights are updated based on a single pair of inputs/expected outputs.
The network would be an array of layers consisting of neuron struct. This will possess feed
forward functionality and would be able to give output based on a given set of inputs. Then we
will calculate the error between the expected value of the output and the predicted output. The
next step involves calculating a small incremental change in the network weights that will move
the network towards minimizing the error of the output that the network just computed. This
step starts at the output nodes and works its way backwards. We calculate the change in weights
by calculating the derivative of the error and multiplying it by the derivative of the output at
that node. Here we are using the mean squared error (MSE) function to compute the error.
However, for the back-propagation itself, we only need to compute the derivative of the error
which for MSE is just the difference between expected and calculated output.

## Literature Review

The author of [1] built and explained a simple three-layer feed-forward back-propagation
network (multi-layer perceptron).
Author of [2] explains fundamental of backpropagation algorithm and gradients calculation
with proof of backpropagation equations.

## Problem Statement

Most sample neural networks posted online are written in Python and use powerful math
libraries such as numpy. While the code in these samples is clean and succinct, it can be hard
to grasp the details behind back-propagation when complex matrix operations are collapsed
into a single statement. Manually implementing a neural network in C/C++ will allow a deeper
understanding of algorithms used to train the network and the data structures used in it.

## Objectives

• To build a generic neural network framework in C/C++ with forward propagation, loss
and gradient calculation and weight updation functionality.
• Assist in understanding data structures used in creation of neural networks, layers nodes
and algorithms used to train and update weights.

## Methodology

• Architecture of the neural network would be created by creating struct of layer and
neurons.
• Inputs would be taken from data and would be passed through the neural network by
using its feed forward functionality,
• Loss would be calculated along with change in weights and bias.
• Weights will be updated through backpropagation algorithm.

## References

[1] Bullinaria, J.A. (2002) “Step by Step Guide to Implementing a Neural Network in C”,
The University of Birmingham, Accessed: Sep. 10, 2022. [Online]. Available:
https://www.cs.bham.ac.uk/~jxb/NN/nn.html

[2] Nielsen, M.A. (2015), "Neural Networks and Deep Learning", Determination Press
