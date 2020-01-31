# distutils: language = c++
import numpy as np

from libcpp.vector cimport vector
from numpy cimport import_array, PyArray_SimpleNewFromData, NPY_INT, npy_intp, NPY_DOUBLE
from meangame import MeanGamePy
from utilities cimport n_m_distribution, clustering, LabeledField

def n_m_dist(MeanGamePy game):
    cdef vector[int] result = n_m_distribution(game->c_game);

import_array()