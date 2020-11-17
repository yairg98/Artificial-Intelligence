"""

"""
from BPNN import *

# Open the input file
filename = input("Enter the name of the input file: ")
infile = open(filename, 'r')
lines = infile.readlines()

# Read NN dimensions from fist line of input file
dims = list(map(int,lines[0].split()))

# Read and parse initial NN weights from input file
weights = []
n = 1
for i in range(1,len(dims)):
    weights.append( [ list(map(float,line.split())) for line in lines[n : n+dims[i]] ] )
    n += dims[i]

# Initialize the neural network with the given dimensions and weights
NN = BPNN(dims, weights)

