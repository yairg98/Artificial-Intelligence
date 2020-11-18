'''
Backpropogation Neural Network class

'''

import numpy as np

# Backprop Neural Net class
class BPNN:
    
    # Constructor acceptingnetwork dimensions and optional pre-loaded weights
    def __init__(self, dims, weights = 0):
        self.setParams(dims, weights)
        
        
    def setParams(self, dims, weights):
        # If weights are not specified, generate them randomly
        if weights == 0:
            # 3D array ( [layers-1] x [nodes in current layer] x [nodes in previous layer] )
            weights = [np.random.rand(dims[i], dims[i-1]+1) for i in range(1,len(dims))]

        # Save network dimensions and weights
        self.dims = dims
        self.weights = weights
    
    
    # Train the neural net on the provided data
    def train(data):
        pass