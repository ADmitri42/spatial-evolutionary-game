import numpy as np
cimport cython

@cython.cdivision(True)
@cython.boundscheck(False)
def evolve(long[:, :] field, double b, long num_epoch=1):
    cdef:
        int L = field.shape[0]
        int x, y, x1, x2, x3, y1, y2, y3, i, j, bestX, bestY
        double N = field.shape[0]
        long[:, :] next_state = np.zeros((L, L), dtype=int)
        double[:, :] scores = np.zeros((L, L), dtype=float)
        double[:, :] _zeros = np.zeros((L, L), dtype=float)
        double f_c
        
    assert L != 0
    
    next_state = field.copy()
    
    for _ in range(num_epoch):
        f_c = np.sum(field)/(N*N)
        scores[...] = _zeros
        for x in range(L):
            for y in range(L):
                x1, x2, x3 = (x-1)%L, x%L, (x+1)%L
                y1, y2, y3 = (y-1)%L, y%L, (y+1)%L
#                 return ((x1, x2, x3), (y1, y2, y3))
                scores[x, y] = (field[x1, y1] + field[x1, y2] + field[x1, y3] +
                                field[x2, y1] + f_c + field[x2, y3] +
                                field[x3, y1] + field[x3, y2] + field[x3, y3])
                if field[x, y] == 0:
                    scores[x, y] *= b
#         return scores
        for x in range(L):
            for y in range(L):
                bestX = x
                bestY = y
                for i in range(-1, 2):
                    for j in range(-1, 2):
                        if scores[(x+i)%L, (y+j)%L] > scores[bestX, bestY]:
                            bestX = (x+i)%L
                            bestY = (y+j)%L

                next_state[x, y] = field[bestX, bestY]
        
        field = next_state.copy()
        
    return np.asarray(field)

@cython.cdivision(True)
@cython.boundscheck(False)
def evolve_old(long[:, :] field, double b, long num_epoch=1):
    cdef:
        int L = field.shape[0]
        int x, y, x1, x2, x3, y1, y2, y3, i, j, bestX, bestY
        long[:, :] next_state = np.zeros((L, L), dtype=int)
        double[:, :] scores = np.zeros((L, L), dtype=float)
        double[:, :] _zeros = np.zeros((L, L), dtype=float)

    assert L != 0

    next_state = field.copy()

    for _ in range(num_epoch):
        scores[...] = _zeros
        for x in range(L):
            for y in range(L):
                x1, x2, x3 = (x-1)%L, x%L, (x+1)%L
                y1, y2, y3 = (y-1)%L, y%L, (y+1)%L
#                 return ((x1, x2, x3), (y1, y2, y3))
                scores[x, y] = (field[x1, y1] + field[x1, y2] + field[x1, y3] + field[x2, y1] + field[x2, y2] + field[x2, y3] + field[x3, y1] + field[x3, y2] + field[x3, y3])
                if field[x, y] == 0:
                    scores[x, y] *= b
#         return scores
        for x in range(L):
            for y in range(L):
                bestX = x
                bestY = y
                for i in range(-1, 2):
                    for j in range(-1, 2):
                        if scores[(x+i)%L, (y+j)%L] > scores[bestX, bestY]:
                            bestX = (x+i)%L
                            bestY = (y+j)%L

                next_state[x, y] = field[bestX, bestY]

        field = next_state.copy()

    return np.asarray(field)

cdef long[:, :] collors = np.array(((255, 255, 0), (0, 0, 0), (255, 0, 0), (0, 0, 255), (0, 255, 0)), dtype=int)
@cython.cdivision(True)
@cython.boundscheck(False)
def make_rgb(long[:, :] field):
    cdef:
        int L = field.shape[0]
        long[:, :, :] new_field = np.zeros((L, L, 3), dtype=int)
        
    for i in range(L):
        for j in range(L):
            for t in range(3):
                new_field[i, j, t] = collors[field[i, j]+2][t]
                
    return np.asarray(new_field)