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
    # dims contains the number of nodes in each layer of the network
    # weights is a 3D array of the multiplicative weights between network layers
    def setParams(self, dims, weights):
        
        # If weights are not specified, generate them randomly
        if weights == 0:
            weights = [np.random.rand(dims[i], dims[i-1]+1) for i in range(1,len(dims))]
        
        # Save network dimensions and weights
        self.values = [[0]*i for i in dims] # Current value of node (i,j)
        self.deltas = [[0]*i for i in dims] # Calculated error of node (i,j)
        self.dims = dims # Dimensions of the network
        self.weights = weights
        
        
    # Sigmoid function
    def sig(self, x):
        return 1/(1+np.exp(-x))      
    
    
    # Derivative of the sigmoid function
    def dsig(self, x):
        sig = self.sig(x)
        return sig*(1-sig)
    
    
    # Update jth node in layer i
    # Assumes previous layer is up-to-date and i!=0 (input layer)
    def updateNode(self, i, j):
        
        # Start by accounting for bias weight
        x = -1 * self.weights[i-1][j][0]
        
        # Add the weighted values of each incoming node
        for n in range(self.dims[i-1]):
            x += self.values[i-1][n] * self.weights[i-1][j][n+1]
        
        # Apply sigmoid transfer function and set/return value
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
    def forwardProp(self, X):
        
        # Set input layer values
        self.values[0] = X
        for i in range(1,len(self.dims)):
            self.updateLayer(i)
        return self.values[-1]
    

    # Back-propogates the error of the jth node in layer i
    # Makes same assumptions as layerError function (see below)
    def nodeError(self, i, j):
        
        # Iteratively add the weighted errors of each node in the next layer
        e = 0
        for n in range(self.dims[i+1]):
            e += (self.deltas[i+1][n] * self.weights[i][n][j+1])
        
        # Multiply error by derivative of transfer function and record/return
        e *= self.dsig(self.values[i][j])
        self.deltas[i][j] = e        
        return e

    
    # Back-propogates the error of layer i
    # Assumes that preceeding errors have already been calculated
    # Also assumes i is not the output layer
    def layerError(self, i):
        
        for j in range(self.dims[i]):
            self.nodeError(i, j)
        return self.deltas[i]
    
    
    # Propogate error backwards, through each layer of the network
    # Does not adjust weights, only fills in the error values
    def backProp(self, X, Y):
        
        # Get current system output H for given inputs X
        H = self.forwardProp(X)
        
        # Reset all the error values, and set the error of the output layer
        self.deltas = [[0]*i for i in self.dims]
        for j in range(self.dims[-1]):
            self.deltas[-1][j] = (Y[j] - H[j]) * self.dsig(H[j])
        
        # Propogate backwards, calculating the error for each successive layer
        for i in reversed(range(len(self.dims)-1)):
            self.layerError(i)
            
            
    # Update the model weights
    # Assumes values and deltas are up-do-date
    # weight += (learning rate) * (output error) * (input value)
    def updateWeights(self, rate):
        
        # Iterate through each set of weights between layers
        for i in range(len(self.weights)):
            
            # Iterate through each node that in layer following that set of weights
            for j in range(len(self.weights[i])):
                
                # First, adjust the bias weight (input of -1)
                self.weights[i][j][0] += rate * self.deltas[i+1][j] * -1
                
                # Iterate through each node in the preceeding layer
                for n in range(1, len(self.weights[i][j])):
                    self.weights[i][j][n] += rate * self.deltas[i+1][j] * self.values[i][n-1]
                    
                    
    # Train the model using provided data, learning rate, and number of epochs
    # Uses sequential gradient descent
    def train(self, data, rate, epochs):
        
        # Perform one full cycle of sequential gradient descent per epoch
        for epoch in range(epochs):
            
            # Update weights once for each sample in given data
            for X, Y in data:
                self.forwardProp(X) # Generate outputs H
                self.backProp(X, Y) # Compare H to Y and back-propogate error
                self.updateWeights(rate) # Update the model weights
                