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
