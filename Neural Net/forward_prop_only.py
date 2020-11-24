'''
Backpropogation Neural Network class

'''

import numpy as np
# from collections import defaultdict


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
            weights = [np.random.rand(dims[i], dims[i-1]+1) for i in range(1,len(dims))]
        
        # Save network dimensions and weights
        self.values = [[0]*i for i in dims]
        self.deltas = [[0]*i for i in dims]
        self.dims = dims
        self.weights = weights
        
        
    # Sigmoid function
    def sig(self, x):
        return 1/(1+np.exp(-x))      
    
    
    # Derivative of the sigmoid function
    def dSig(self, x):
        sig = self.sig(x)
        return sig*(1-sig)
    
    
    # Update jth node in layer i
    # Assumes previous layer is up-to-date and i!=0 (input layer)
    def updateNode(self, i, j):
        x = -1 * self.weights[i-1][j][0]
        for n in range(self.dims[i-1]):
            x += self.values[i-1][n] * self.weights[i-1][j][n+1]
        x = self.sig(x)
        self.values[i][j] = x
        return x
    
    
    # Update the ith layer in the network
    # Assumed previous layer is up-to-date and 1!=0 (input layer)
    def updateLayer(self, i):
        for j in range(self.dims[i]):
            self.updateNode(i, j)
        return self.values[i]
    
    
    # Forward-propogate input values, and return the output layer
    def forwardProp(self, inputs):
        # Set input layer values
        self.values[0] = inputs
        for i in range(1,len(self.dims)):
            self.updateLayer(i)
        return self.values[-1]