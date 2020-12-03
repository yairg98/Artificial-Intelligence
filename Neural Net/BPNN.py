'''
Backpropogation Neural Network class

'''

import numpy as np


#%% Backprop Neural Net Class


# Backprop Neural Net class
class BPNN:
    
    # Constructor accepting network dimensions and optional pre-loaded weights
    # Assumes legal initialization parameters
    # Initial weights must be specified in the file
    def __init__(self, filename=""):
        if filename:
            self.setParams(filename)
        
        
    # Get neural network parameters from text file
    def getParams(self, filename):
        
        # Read the input file
        infile = open(filename, 'r')
        lines = infile.readlines()
        infile.close()
        
        # Read NN dimensions from first line of input file
        dims = list(map(int,lines[0].split()))
        
        # Read and parse initial NN weights from input file
        weights = []
        n = 1
        for i in range(1,len(dims)):
            weights.append( [ list(map(float,line.split())) for line in lines[n : n+dims[i]] ] )
            n += dims[i]
            
        # Returns reformatted network dimensions and initial weights
        return dims, weights

        
    # Set or reset the dimensions and weights of the model
    def setParams(self, filename):
        dims, weights = self.getParams(filename)
        self.values = [[0]*i for i in dims] # Current value of node (i,j)
        self.deltas = [[0]*i for i in dims] # Calculated error of node (i,j)
        self.dims = dims # Dimensions of the network
        self.weights = weights
        
        
    # Get training data from text file
    def getData(self, filename):
        
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
        return data
        
        
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
    # Assumes previous layer is up-to-date and 1!=0 (input layer)
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
    def train(self, datafile, rate, epochs):
        
        # Get data from file
        data = self.getData(datafile)
        
        # Perform one full cycle of sequential gradient descent per epoch
        for epoch in range(epochs):
            
            # Update weights once for each sample in given data
            for X, Y in data:
                self.backProp(X, Y) # Compare H to Y and back-propogate error
                self.updateWeights(rate) # Update the model weights
                
                
    def test(self, datafile, outfile):
        
        # Get data from file
        data = self.getData(datafile)
        
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
        precision = [ 0 if A[i]==0 else A[i] / (A[i] + B[i]) for i in range(len(H)) ]
        recall = [ 0 if A[i]==0 else A[i] / (A[i] + C[i]) for i in range(len(H)) ]
        f1 = [ 0 if A[i]==0 else (2 * precision[i] * recall[i]) / (precision[i] + recall[i]) for i in range(len(H)) ]
        
        # Calculate micro-averaged performance metrics
        a, b, c, d = sum(A), sum(B), sum(C), sum(D)
        micro_accuracy = (a + d) / (a + b + c + d)
        micro_precision = 0 if a==0 else a / (a + b)
        micro_recall = 0 if a==0 else a / (a + c)
        micro_f1 = 0 if a==0 else (2 * micro_precision * micro_recall) / (micro_precision + micro_recall)
        micro = [micro_accuracy, micro_precision, micro_recall, micro_f1]

        # Calculate macro-averaged performance metrics
        macro_accuracy = np.average(accuracy)
        macro_precision = np.average(precision)
        macro_recall = np.average(recall)
        macro_f1 = 0 if a==0 else (2 * macro_precision * macro_recall) / (macro_precision + macro_recall)
        macro = [macro_accuracy, macro_precision, macro_recall, macro_f1]
        
        # Format and print results
        output = open(outfile, 'w', newline='\n')
        
        for i in range(len(H)):
            # Format each element
            line = [str(A[i]),
                    str(B[i]),
                    str(C[i]),
                    str(D[i]),
                    '{:.3f}'.format(accuracy[i]),
                    '{:.3f}'.format(precision[i]),
                    '{:.3f}'.format(recall[i]),
                    '{:.3f}'.format(f1[i]) ]
            # Write to file as space-separated string
            output.write(' '.join(line) + '\n')
        
        # Format and print micro/macro-averaged results
        output.write( ' '.join(map(str, ['{:.3f}'.format(x) for x in micro]))+'\n' )
        output.write( ' '.join(map(str, ['{:.3f}'.format(x) for x in macro]))+'\n' )
        
        
    # Format and output network parameters (dims, weights) to a text file
    def export(self, filename):
        file = open(filename, 'w', newline='\n')
        # Print dimensions on first line
        file.write(' '.join(map(str,self.dims))+'\n')
        # Print weights on remaining lines
        for i in self.weights:
            for j in i:
                # Round each weight value to 3 decimal places
                file.write(' '.join(map(str, ['{:.3f}'.format(k) for k in j]))+'\n')
        file.close()
        
        

#%% Driver code for testing BPNN functionality


nn = BPNN()

choice = ""
while(1):
    
    print("""\nWould you like to... 
          (1) Load network from text file
          (2) Train the network
          (3) Test the network
          (4) Export network to text file
          (5) Quit""")
    choice = input("(Enter the number corresponding to your selection): ")
    
    try:
        if choice == '1':
            nn.setParams(input("Name of network-parameters file: "))
            
        elif choice == '2':
            nn.train(input("Name of training data file: "),
                     float(input("Learning rate: ")),
                     int(input("Number of epochs: ")))
            
        elif choice == '3':
            nn.test(input("Name of testing data file: "),
                    input("Name of output file: "))
            
        elif choice == '4':
            nn.export(input("Name of destination file: "))
            
        elif choice == '5':
            break
            
        else:
            print("Invalid entry. Try again.")
                
    except:
        print("Invalid entry. try again.")