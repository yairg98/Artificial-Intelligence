'''
Backpropogation Neural Network class

'''

import numpy as np


# Backprop Neural Net class
class BPNN:
    
    # Constructor accepting network dimensions and optional pre-loaded weights
    # Assumes legal initialization parameters
    def __init__(self, dims, weights = 0):
        self.setParams(dims, weights)
        
        
    # Set or reset the dimensions and weights of the model
    # dims is an array of ints where each represents the number of nodes in that layer
    # weights is a 3D array of the weight between each two consecutive layers
    def setParams(self, dims, weights):
        # If weights are not specified, generate them randomly
        if weights == 0:
            # 3D array ( [layers-1] x [nodes in current layer] x [nodes in previous layer] )
            weights = [np.random.rand(dims[i], dims[i-1]+1) for i in range(1,len(dims))]
        # Save network dimensions and weights
        self.network = [[[0,0]]*i for i in dims] # [ 0:value, 1:error ]
        self.dims = dims
        self.weights = weights
        
        
    # Sigmoid function
    def sig(self, x):
        return 1/(1+np.exp(-x))
    
    
    # Derivative of the sigmoid function
    def dSig(self, x):
        sig = self.sig(x)
        return sig*(1-sig)
    
    
    # Get output value of a particular neuron
    # i contains the index of the current network layer
    # j contains the index of the current node within the current layer
    def updateNode(self, i, j):
        # Start with bias value
        x = -1 * self.weights[i-1][j][0]
        
        # Add each weighted previous-layer node
        for n in range(len(self.network[i-1])):
            x += self.network[i-1][n][0] * self.weights[i-1][j][n+1]
        
        # Apply sigmoid function and return the result
        self.network[i][j][0] = self.sig(x)
        return self.network[i][j][0]
    
    
    # Evaluate next layer of nodes
    # i contains the index of the current network layer being updated
    def updateLayer(self, i):
        # Calculate node values one at a time
        for j in range(len(self.network[i])):
            self.updateNode(i, j)
        # Return array of all evaluated nodes in the next layer
        return [n[0] for n in self.network[i]]
    
    
    # Forward-propogate input layer and return output layer
    def forwardProp(self, inputs):
        # Enter input values into first layer of network
        for n in range(len(inputs)):
            self.network[0][n][0] = inputs[n]
        # In order, update each layer of the network
        for i in range(1, len(self.network)):
            self.updateLayer(i)
        # Return final layer
        return [n[0] for n in self.network[-1]]
    
    
    # Train the neural net on the provided data
    def backProp(self, data):
        pass