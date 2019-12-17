# distutils: language = c++
import numpy as np

from libcpp.vector cimport vector
from numpy cimport import_array, PyArray_SimpleNewFromData, NPY_INT, npy_intp, NPY_DOUBLE

from MeanGame cimport MeanGame

cdef class MeanGamePy:
    cdef:
        MeanGame *c_game;
        cdef int _L

    def __cinit__(self, int L, double b):
        self.c_game = new MeanGame(L, b)
        self._L = L

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
            raise ValueError("Size mismatch: expected %s, got %s." % (self._L*self._L, arr.size))

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

    def evolve(self, int num_steps = 1):
        self.c_game.evolve(num_steps)

import_array()