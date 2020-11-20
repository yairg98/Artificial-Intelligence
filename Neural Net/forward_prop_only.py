'''
Backpropogation Neural Network class

'''

import numpy as np


# Backprop Neural Net class
class BPNN:
    
    # Constructor acceptingnetwork dimensions and optional pre-loaded weights
    def __init__(self, dims, weights = 0):
        self.setParams(dims, weights)
        
        
    # Set or reset the dimensions and weights of the model
    def setParams(self, dims, weights):
        # If weights are not specified, generate them randomly
        if weights == 0:
            # 3D array ( [layers-1] x [nodes in current layer] x [nodes in previous layer] )
            weights = [np.random.rand(dims[i], dims[i-1]+1) for i in range(1,len(dims))]
        # Save network dimensions and weights
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
    def nodeValue(self, prevLayer, weights):
        # Start with bias value
        s = -1 * weights[0]
        # Add each weighted previous-layer node
        for i in range(len(prevLayer)):
            s += prevLayer[i]*weights[i+1]
        # Apply sigmoid function and return the result
        return self.sig(s)
    
    
    # Evaluate next layer of node
    def getLayer(self, prevLayer, weightMatrix):
        nextLayer = []
        # Calculate node values one at a time
        for row in weightMatrix:
            nextLayer.append(self.nodeValue(prevLayer, row))
        # Return array of all evaluated nodes in the next layer
        return nextLayer
    
    
    # Forward-propogate input layer and return output predictions
    def forwardProp(self, layer):
        # Use each layer and weightMatrix to find the next
        for weightMatrix in self.weights:
            layer = self.getLayer(layer, weightMatrix)
        # Return final layer
        return layer
    
    
    # Train the neural net on the provided data
    def backProp(self, data):
        pass