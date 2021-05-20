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
while True:
    try:
        vec = []
        for num in input().split(','):
            vec.append(float(num))
        data.append(vec)
    except EOFError:
        break

# initiating our info into a 4 tables of size K for the K clusters, centroids, size and sums
Clstr = [[] for i in range(K)] #has k empty lists which represent the clusters
Cntr = []
Cl_size = []

# Start by filling the Centroids array with K random vectors (deterministically)
for i in range(K):
    Cntr[i] = data[i]

#the functions we'll need:
# calculating the difference between two vectors of length D
def diff(vec1, vec2):
    dif =0
    for i in range(d):
        dif += ((vec1[i])-(vec2[i]))**2
    assert isinstance(d, int)
    return dif**(1/d)

# finding the right cluster for a vector of size d
def place(vec):
    min=[0,float('inf')]
    for i in range(K):
        dif= diff(vec, Clstr[i])
        if (dif<min[1]):
            min= [i, dif]
    Clstr[min[0]].append(vec)
    return

# creating the new means
def update_means():
    for i in range(K):
        Cl_size[i]= len(Clstr[i])
        assert (Cl_size[i]>0)
        v_sum=vectorsum(i)
        for j in range(d):
            v_sum[j]/= Cl_size[i]


# creating a vector which is the sum of all the vectors in cluster i
def vectorsum(i):
    v_sum = [0 for i in range(d)]
    for j in range(Cl_size[i]):
        for l in range(d):
            v_sum[l]+=Clstr[i][j][l]
    return v_sum

#clearing all the k cluster, so we can re-arrange them
def clear_Clstr():
    Clstr= [[] for i in range(K)]

#comparing two arrays of vectors, return 1 if they are equal or 0 if they're not
def array_equal(arr1, arr2):
    assert (len(arr2)==len(arr1))
    for i in range(K):
        for j in range(d):
            if(arr1[i][j]!=arr2[i][j]):
                return False
    return True

#printing the current centeroids
def print_means():
    for i in range(K):
        for j in range(d - 1):
            print("{:.2f}".format(Cntr[i][j]), end=",")
        if i < K - 1:
            print("{:.2f}".format(Cntr[i][d - 1]))
        else:
            print("{:.2f}".format(Cntr[i][d - 1]), end="")


#the main part of the function:
counter=0
while(counter < MAX_ITER):
    prev_cntr = Cntr.copy()
    for vector in data:
        place(vector)
    update_means()
    clear_Clstr()
    if array_equal(prev_cntr, Cntr):
        break
    counter += 1
print_means()




