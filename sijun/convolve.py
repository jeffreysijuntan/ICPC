import numpy as np
from timeit import default_timer as timer
import time

def MtoCol(M):
    h, w = M.shape
    i = np.repeat(np.arange(h), 3*(w-2))
    j = np.tile(np.arange(3), h*(w-2))
    j1 = np.tile(np.repeat(np.arange(w-2), 3), h)
    j = j+j1

    return M[i,j].reshape(-1,3)

def convolve(M, K):
    h, w = M.shape
    cols = MtoCol(M)
    res = np.dot(cols,K.T).reshape(h, -1)
    res[res < 0] = 0
    return res

def main():
    K = np.asarray([-1,0,1])

    m, n = input().split()
    m = int(m)
    n = int(n)

    M = np.random.randint(1,255, size=(m, n))
    start = timer()
    dy = convolve(M, K)
    dx = convolve(np.transpose(M), K)
    end = timer()
    print('Elapsed time: {}'.format((end-start)*1E6))

    #print(dx)
    #print(dy)
    
    print("Max dx: {}".format(np.max(dx)))
    print("Min dx: {}".format(np.min(dx)))

    print("Max dy: {}".format(np.max(dy)))
    print("Min dy: {}".format(np.min(dy)))

if __name__ == '__main__':
    main()