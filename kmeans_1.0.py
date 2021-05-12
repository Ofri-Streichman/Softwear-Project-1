from typing import Any

import argparse

# This function reads from the commend line.
parser = argparse.ArgumentParser(description='the argument from cl')
parser.add_argument("K", type=int, help="K – the number of clusters")
parser.add_argument("N", type=int, help="N – the number of observations ")
parser.add_argument("d", type=int, help="d – the dimension of each observation")
parser.add_argument("MAX_ITER", type=int,
                                   help="MAX_ITER – the maximum number of iterations")
args = parser.parse_args()

K = args.K
N = args.N
d = args.d
MAX_ITER = args.MAX_ITER

#________________________________________________________#

# reading the data from the file and putting n vectors in an array
data = []
while (True):
    try:
        vec = []
        for num in input().split(','):
            vec.append(float(num))
        data.append(a)
    except EOFError:
        break

# initiating our info into a 4 tables of size K for the K clusters, centroids, size and sums
Clstr = [[]*k] #has k empty lists ehich represent the ckusters
Global Cntr = []
Cl_size = []
Cl_sum = []

# Start by filling the Centroids array with K random vectors (deterministically)
for i in range(k):
    Clstr[i] = data[i]

#the functions we'll need:
# calculating the difference between two vectors of length D
def diff(vec1, vec2):
    dif =0
    for i in range(d):
        dif += ((vec1[i])-(vac2[i]))**2
    assert isinstance(d, int)
    return dif**(1/d)

# finding the right cluster for a vector of size d
def place(vec):
    min=[0,float('inf')]
    for i in range(k):
        dif= diff(vec, Clstr[i])
        if (dif<min[1]):
            min= [i, dif]
    Clstr[min[0]].add(vec)
    return




#the main part of the function:
int i=0
Var: Bool = True
#While ((i < MAX_ITER) and Var):


