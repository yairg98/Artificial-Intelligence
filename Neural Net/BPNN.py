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
    
    
    def predict(self, X):
        return [round(y, 0) for y in self.forwardProp(X)]
    

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
                
                
    def test(self, data):
        
        # Set initial values of confusion matrix quadrants to zero
        A = [0] * self.dims[-1]
        B = [0] * self.dims[-1]
        C = [0] * self.dims[-1]
        D = [0] * self.dims[-1]
        
        # Categorize the results of each data sample prediction
        for X, Y in data:
            H = self.predict(X)
            
            # Calculate separate results for each element in output layer 
            for i in range(len(H)):

                # If predicted value and actual value are both 1
                if H[i] and Y[i]: A[i] += 1
                
                # If predicted value is 1 and actual value is 0
                elif H[i]: B[i] += 1
                
                # If predicted value is 0 and actual value is 1
                elif Y[i]: C[i] += 1
                
                # If predicted value and actual value are both 0
                else: D[i] += 1
        
        # Calculate performance metrics for each element of output layer
        accuracy = [ (A[i] + D[i]) / (A[i] + B[i] + C[i] + D[i]) for i in range(len(H)) ]
        precision = [ A[i] / (A[i] + B[i]) for i in range(len(H)) ]
        recall = [ A[i] / (A[i] + C[i]) for i in range(len(H)) ]
        f1 = [ (2 * precision[i] * recall[i]) / (precision[i] + recall[i]) for i in range(len(H)) ]
        
        # Calculate micro-averaged performance metrics
        a, b, c, d = sum(A), sum(B), sum(C), sum(D)
        micro_accuracy = round( (a + d) / (a + b + c + d), 3)
        micro_precision = round( a / (a + b), 3)
        micro_recall = round( a / (a + c), 3)
        micro_f1 = round( (2 * micro_precision * micro_recall) / (micro_precision + micro_recall), 3)

        # Calculate macro-averaged performance metrics
        macro_accuracy = round(np.average(accuracy), 3)
        macro_precision = round(np.average(precision), 3)
        macro_recall = round(np.average(recall), 3)
        macro_f1 = round((2 * macro_precision * macro_recall) / (macro_precision + macro_recall), 3)
        
        # Round performance metrics to 3 decimal places
        accuracy = [round(i,3) for i in accuracy]
        precision = [round(i,3) for i in precision]
        recall = [round(i,3) for i in recall]
        f1 = [round(i,3) for i in f1]
        
        # Print test results
        for i in range(len(H)):
            print(A[i], B[i], C[i], D[i], accuracy[i], precision[i], recall[i], f1[i])
            
        print(micro_accuracy, micro_precision, micro_recall, micro_f1)
        print(macro_accuracy, macro_precision, macro_recall, macro_f1)
        