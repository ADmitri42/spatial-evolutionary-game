# distutils: language = c++
import numpy as np
cimport cython

from libcpp.vector cimport vector
from numpy cimport import_array, PyArray_SimpleNewFromData, NPY_UINT8, NPY_UINT32, NPY_INT32, npy_intp, NPY_DOUBLE

from CGames cimport MeanGame, NovakMayGame, MeanTriangularGame, NovakMayTriangularGame
from utilities cimport py_n_m_distribution, clustering, LabeledField


cdef class NovakMayGamePy:
    cdef:
        NovakMayGame *c_game;
        cdef int _L, percfrom, perctill

    def __cinit__(self, int L, double b, int percfrom=-1, perctill=-1):
        self.c_game = new NovakMayGame(L, b)
        self._L = L
        self.percfrom = percfrom;
        self.perctill = perctill;

    def __dealloc__(self):
        del self.c_game

    @property
    def L(self):
        """"Return linear size of the field"""
        return self.c_game.size()

    @property
    def field(self):
        """Return the field as a numpy array."""
        cdef npy_intp dims[2]
        dims[0] = self._L
        dims[1] = self._L
        return PyArray_SimpleNewFromData(2, dims, NPY_UINT8, self.c_game.get_field_pointer())

    @field.setter
    def field(self, arr):
        """Set the game field."""
        arr = np.asarray(arr)
        if len(arr.shape) != 2:
            raise ValueError("Expected a 2D array, got %s-d." % len(arr.shape))
        if arr.size != self._L*self._L:
            raise ValueError(f"Size mismatch: expected {self._L*self._L}, got {arr.size}.")

        arr = arr.ravel()
        cdef vector[int] vec;
        vec.resize(self._L*self._L)
        for j in range(arr.size):
            vec[j] = arr[j]

        self.c_game.set_field(vec)
        vec.clear()

    @property
    def b(self):
        return self.c_game.get_b()

    @b.setter
    def b(self, double arr):
        self.c_game.set_b(arr)

    @property
    def densities(self):
        cdef npy_intp dims[1]
        dims[0] = self.c_game.get_densities_size()
        return PyArray_SimpleNewFromData(1, dims, NPY_DOUBLE, self.c_game.get_densities_pointer())

    @property
    def persistence(self):
        return self.c_game.get_persistence()

    def evolve(self, int num_steps = 1):
        self.c_game.evolve(num_steps, self.percfrom, self.perctill)




cdef class MeanGamePy:
    cdef:
        MeanGame *c_game;
        cdef int _L, percfrom, perctill

    def __cinit__(self, int L, double b, int percfrom=-1, perctill=-1):
        self.c_game = new MeanGame(L, b)
        self._L = L
        self.percfrom = percfrom;
        self.perctill = perctill;

    def __dealloc__(self):
        del self.c_game

    @property
    def L(self):
        """"Return linear size of the field"""
        return self.c_game.size()

    @property
    def field(self):
        """Return the field as a numpy array."""
        cdef npy_intp dims[2]
        dims[0] = self._L
        dims[1] = self._L
        return PyArray_SimpleNewFromData(2, dims, NPY_UINT8, self.c_game.get_field_pointer())

    @field.setter
    def field(self, arr):
        """Set the game field."""
        arr = np.asarray(arr)
        if len(arr.shape) != 2:
            raise ValueError("Expected a 2D array, got %s-d." % len(arr.shape))
        if arr.size != self._L*self._L:
            raise ValueError(f"Size mismatch: expected {self._L*self._L}, got {arr.size}.")

        arr = arr.ravel()
        cdef vector[int] vec;
        vec.resize(self._L*self._L)
        for j in range(arr.size):
            vec[j] = arr[j]

        self.c_game.set_field(vec)
        vec.clear()

    @property
    def b(self):
        return self.c_game.get_b()

    @b.setter
    def b(self, double arr):
        self.c_game.set_b(arr)

    @property
    def densities(self):
        cdef npy_intp dims[1]
        dims[0] = self.c_game.get_densities_size()
        return PyArray_SimpleNewFromData(1, dims, NPY_DOUBLE, self.c_game.get_densities_pointer())

    @property
    def persistence(self):
        return self.c_game.get_persistence()

    def evolve(self, int num_steps = 1):
        self.c_game.evolve(num_steps, self.percfrom, self.perctill)

    def n_m_distribution(self):
        cdef vector[int] result = py_n_m_distribution(self.c_game)
        cdef int x, y

        nmdist = np.zeros((9, 9), dtype="int")
        for x in range(9):
            for y in range(9):
                # print(result[y*9 + x])
                nmdist[y, x] = result[y*9 + x]
        return nmdist

    def clustering(self, size_only=False):
        cdef:
            LabeledField** result = clustering(self.c_game.get_field(), self._L, self._L)
            npy_intp dims[2]
            npy_intp dimss[1]
            int x, y

        zeros = []
        ones = []
        if not size_only:
            dims[0] = self._L
            dims[1] = self._L
            zeros.append(PyArray_SimpleNewFromData(2, dims, NPY_UINT32, &result[0].labeled_field[0]))
            ones.append(PyArray_SimpleNewFromData(2, dims, NPY_UINT32, &result[1].labeled_field[0]))


        dimss[0] = result[0].cluster_sizes.size()
        zeros.append(PyArray_SimpleNewFromData(1, dimss, NPY_INT32, &result[0].cluster_sizes[0]))
        dimss[0] = result[1].cluster_sizes.size()
        ones.append(PyArray_SimpleNewFromData(1, dimss, NPY_INT32, &result[1].cluster_sizes[0]))
        zeros.extend(ones)
        return zeros
    #      #
   ###    ###
  ## ##  ## ##
 ##   ####   ##
################
#  Triangular  #
################

cdef class NovakMayTriangularGamePy:
    cdef:
        NovakMayTriangularGame *c_game;
        cdef int _L, percfrom, perctill

    def __cinit__(self, int L, double b, int percfrom=-1, perctill=-1):
        self.c_game = new NovakMayTriangularGame(L, b)
        self._L = L
        self.percfrom = percfrom
        self.perctill = perctill

    def __dealloc__(self):
        del self.c_game

    @property
    def L(self):
        """"Return linear size of the field"""
        return self.c_game.size()

    @property
    def field(self):
        """Return the field as a numpy array."""
        cdef npy_intp dims[2]
        dims[0] = self._L
        dims[1] = self._L
        return PyArray_SimpleNewFromData(2, dims, NPY_UINT8, self.c_game.get_field_pointer())

    @field.setter
    def field(self, arr):
        """Set the game field."""
        arr = np.asarray(arr)
        if len(arr.shape) != 2:
            raise ValueError("Expected a 2D array, got %s-d." % len(arr.shape))
        if arr.size != self._L*self._L:
            raise ValueError(f"Size mismatch: expected {self._L*self._L}, got {arr.size}.")

        arr = arr.ravel()
        cdef vector[int] vec;
        vec.resize(self._L*self._L)
        for j in range(arr.size):
            vec[j] = arr[j]

        self.c_game.set_field(vec)
        vec.clear()

    @property
    def b(self):
        return self.c_game.get_b()

    @b.setter
    def b(self, double arr):
        self.c_game.set_b(arr)

    @property
    def densities(self):
        cdef npy_intp dims[1]
        dims[0] = self.c_game.get_densities_size()
        return PyArray_SimpleNewFromData(1, dims, NPY_DOUBLE, self.c_game.get_densities_pointer())

    @property
    def persistence(self):
        return self.c_game.get_persistence()

    def evolve(self, int num_steps = 1):
        self.c_game.evolve(num_steps, self.percfrom, self.perctill)




cdef class MeanTriangularGamePy:
    cdef:
        MeanTriangularGame *c_game;
        cdef int _L, percfrom, perctill

    def __cinit__(self, int L, double b, int percfrom=-1, perctill=-1):
        self.c_game = new MeanTriangularGame(L, b)
        self._L = L
        self.percfrom = percfrom;
        self.perctill = perctill;

    def __dealloc__(self):
        del self.c_game

    @property
    def L(self):
        """"Return linear size of the field"""
        return self.c_game.size()

    @property
    def field(self):
        """Return the field as a numpy array."""
        cdef npy_intp dims[2]
        dims[0] = self._L
        dims[1] = self._L
        return PyArray_SimpleNewFromData(2, dims, NPY_UINT8, self.c_game.get_field_pointer())

    @field.setter
    def field(self, arr):
        """Set the game field."""
        arr = np.asarray(arr)
        if len(arr.shape) != 2:
            raise ValueError("Expected a 2D array, got %s-d." % len(arr.shape))
        if arr.size != self._L*self._L:
            raise ValueError(f"Size mismatch: expected {self._L*self._L}, got {arr.size}.")

        arr = arr.ravel()
        cdef vector[int] vec;
        vec.resize(self._L*self._L)
        for j in range(arr.size):
            vec[j] = arr[j]

        self.c_game.set_field(vec)
        vec.clear()

    @property
    def b(self):
        return self.c_game.get_b()

    @b.setter
    def b(self, double arr):
        self.c_game.set_b(arr)

    @property
    def densities(self):
        cdef npy_intp dims[1]
        dims[0] = self.c_game.get_densities_size()
        return PyArray_SimpleNewFromData(1, dims, NPY_DOUBLE, self.c_game.get_densities_pointer())

    @property
    def persistence(self):
        return self.c_game.get_persistence()

    def evolve(self, int num_steps = 1):
        self.c_game.evolve(num_steps, self.percfrom, self.perctill)


cdef long[:, :] collors = np.array(((255, 255, 0, 255),
                                    (0, 0, 0, 255),
                                    (255, 0, 0, 255),
                                    (0, 0, 255, 255),
                                    (0, 0, 0, 255),
                                    (0, 255, 0, 255)), dtype=int)

cdef double[:, :] colors_f = np.array(((1, 1, 0, 1),
                                    (0, 0, 0, 1),
                                    (1, 0, 0, 1),
                                    (0, 0, 1, 1),
                                    (0, 0, 0, 1),
                                    (0, 1, 0, 1)), dtype=float)

@cython.cdivision(True)
@cython.boundscheck(False)
def _make_rgb(long[:, :] field):
    cdef:
        int L = field.shape[0]
        long[:, :, :] new_field = np.zeros((L, L, 3), dtype=int)

    for i in range(L):
        for j in range(L):
            for t in range(3):
                new_field[i, j, t] = collors[field[i, j]+2][t]

    return np.asarray(new_field)


def color_field_change(oldfield, newfield):
    return _make_rgb(newfield + 2*(newfield-oldfield))

@cython.cdivision(True)
@cython.boundscheck(False)
def _make_rgb_flat(long[:] field):
    cdef:
        int L = field.shape[0]
        double[:, :] new_field = np.zeros((L,  3), dtype=float)

    for i in range(L):
        for t in range(3):
            new_field[i, t] = colors_f[field[i]+2][t]

    return np.asarray(new_field)


def color_field_change_flat(oldfield, newfield):
    return _make_rgb_flat(newfield + 2*(newfield-oldfield))

import_array()