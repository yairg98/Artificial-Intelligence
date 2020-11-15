'''
Yair Gross
12/07/2020
Artificial Intelligence (ECE-469)
Project 2 - Backpropogation Neural Network
'''

import numpy as np

# Backprop Neural Net class
class BPNN:
    
    # Constructor acceptingnetwork dimensions and optional pre-loaded weights
    def __init__(self, dims, weights = 0):
        
        # If weights are not specified, generate them randomly
        if weights == 0:
            # 3D array ( [layers-1] x [nodes in current layer] x [nodes in previous layer] )
            weights = [np.random.rand(dims[i], dims[i-1]+1) for i in range(1,len(dims))]

        # Save network dimensions and weights
        self.dims = dims
        self.weights = weights
        
        
    