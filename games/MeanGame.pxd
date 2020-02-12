# distutils: sources = cpp/games.cpp
from libcpp.vector cimport vector

cdef extern from "cpp/evolve.h":
    cdef cppclass MeanGame:
        MeanGame(int, double)
        void evolve(int, int, int);
        vector[double] get_densities();
        int get_densities_size();
        int size();
        double get_b();
        void set_b(double);
        vector[int] get_field();
        void set_field(vector[int]);

        double get_persistence();
        char* get_field_pointer();
        double* get_densities_pointer();
