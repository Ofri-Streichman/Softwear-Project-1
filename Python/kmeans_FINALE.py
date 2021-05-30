import argparse
import copy
import sys

# Reading the arguments from command line:
arglen= len(sys.argv)
assert (arglen==2 or arglen==3) # making sure we have just 2 arguments (K and MAX_ITER) or just 1 (K)
K= int(sys.argv[1])
assert (K>0)
if (arglen==2):
    MAX_ITER=200
else:
    MAX_ITER= int(sys.argv[2])
    assert (MAX_ITER>0)



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

N = len(data)
assert (N>=K)

d = len(data[0])
assert (d>0)


# initiating our info into a 4 tables of size K for the K clusters, centroids, size and sums
Clstr = [[] for i in range(K)]  # has k empty lists which represent the clusters
Cntr = []
Cl_size = [0 for i in range(K)]

# Start by filling the Centroids array with K random vectors (deterministically)
for i in range(K):
    Cntr.append(copy.deepcopy(data[i]))


# the functions we'll need:
# calculating the difference between two vectors of length D
def diff(vec1, vec2):
    dif = 0
    for i in range(d):
        dif += ((vec1[i]) - (vec2[i])) ** 2
    assert isinstance(d, int)
    return dif ** (1 / 2)


# finding the right cluster for a vector of size d
def place(vec):
    min = [0, float('inf')]
    for i in range(K):
        dif = diff(vec, Cntr[i])
        if dif < min[1]:
            min = [i, dif]
    Clstr[min[0]].append(vec)
    return


# creating the new means
def update_means():
    for i in range(K):
        Cl_size[i]=(len(Clstr[i]))
        assert (Cl_size[i] > 0)
        v_sum = vectorsum(i)
        for j in range(d):
            Cntr[i][j] = v_sum[j]/Cl_size[i]




# creating a vector which is the sum of all the vectors in cluster i
def vectorsum(i):
    v_sum = [0 for i in range(d)]
    for j in range(Cl_size[i]):
        for l in range(d):
            v_sum[l] += Clstr[i][j][l]
    return v_sum


# clearing all the k cluster, so we can re-arrange them
def clear_Clstr():
    for i in range(K):
        Clstr[i]=[]


# comparing two arrays of vectors, return 1 if they are equal or 0 if they're not
def array_equal(arr1, arr2):
    assert (len(arr2) == len(arr1))
    for i in range(K):
        for j in range(d):
            if arr1[i][j] != arr2[i][j]:
                return False
    return True


def print_cen():
    for i in range(K):
        for j in range(d - 1):
            print("{:.4f}".format(Cntr[i][j]), end=",")
        if i < K - 1:
            print("{:.4f}".format(Cntr[i][d - 1]))
        else:
            print("{:.4f}".format(Cntr[i][d - 1]), end="")



# the main part of the function:
counter = 1
for vector in data:
    place(vector)
update_means()
clear_Clstr()

while counter < MAX_ITER:
    prev_cntr = copy.deepcopy(Cntr)
    for vector in data:
        place(vector)
    update_means()
    clear_Clstr()
    if array_equal(prev_cntr, Cntr):
        break
    counter += 1

print_cen()

