"""
Create and test neural network using BPNN class
Load initialization parameters, training data, and testing data from text files

"""
from BPNN import BPNN


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
        

        
# dims, weights = getParams()
# NN = BPNN(dims, weights)
# n, data = getData()
# NN.train(data)