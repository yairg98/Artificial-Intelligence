'''
Backpropogation Neural Network class

'''

import numpy as np


#%% Backprop Neural Net Class


# Backprop Neural Net class
class BPNN:
    
    # Constructor accepting network dimensions and optional pre-loaded weights
    # Assumes legal initialization parameters
    def __init__(self, dims = [0,0], weights = 0):
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
        return x*(1-x)
    
    
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
        
        # Iterate through each set of weights between layers i and i+1
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
        results = []
        for i in range(len(H)):
            results.append( [A[i], B[i], C[i], D[i], accuracy[i], precision[i], recall[i], f1[i]] )
            
        results.append( [micro_accuracy, micro_precision, micro_recall, micro_f1] )
        results.append( [macro_accuracy, macro_precision, macro_recall, macro_f1] )
        
        return results
        

#%% Funcitions for retrieving and exporting data and network parameters


# Get neural network parameters from text file
def getParams():
    
    # Prompt the user for weights, training, and testing 
    filename = input("Enter the name of the input file: ")
    
    # Read the input file
    infile = open(filename, 'r')
    lines = infile.readlines()
    infile.close()
    
    # Read NN dimensions from fist line of input file
    dims = list(map(int,lines[0].split()))
    
    # Read and parse initial NN weights from input file
    weights = []
    n = 1
    for i in range(1,len(dims)):
        weights.append( [ list(map(float,line.split())) for line in lines[n : n+dims[i]] ] )
        n += dims[i]
        
    # Returns reformatted network dimensions and initial weights
    return dims, weights
        

# Get training data from text file
def getData():
    
    # Prompt the user for name of training data file
    filename = input("Enter the name of the training data file: ")
    
    # Read the input file
    infile = open(filename, 'r')
    lines = infile.readlines()
    infile.close()
    
    # Get number of training samples (first line = [N-samples, N-in, N-out])
    stats = list(map(int,lines[0].split()))
    
    # Read and parse training data samples from input file
    data = []
    for line in lines[1:]:
        d1 = list(map(float,line.split()))[:stats[1]]
        d2 = list(map(float,line.split()))[stats[1]:]
        data.append( [d1, d2] )
        
    # Returns number of samples and reformatted data
    return stats[0], data


# Test network nn on the given data, and print results to file ('outfile')
def getResults(nn, data, outfile):
    output = open(outfile, 'w')
    for line in nn.test(data):
        output.write(' '.join(map(str, line))+'\n')
    output.close()
        

# Format and output network parameters (dims, weights) to a text file
def exportNetwork(nn, filename):
    file = open(filename, 'w')
    # Print dimensions on first line
    file.write(' '.join(map(str,nn.dims))+'\n')
    # Print weights on remaining lines
    for i in nn.weights:
        for j in i:
            # Round each weight value to 3 decimal places
            file.write(' '.join(map(str, ['{:.3f}'.format(k) for k in j]))+'\n')
    file.close()
    
    
#%% Driver code 