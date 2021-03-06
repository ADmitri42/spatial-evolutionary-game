from libcpp.vector cimport vector

cdef extern from "cpp/games.h":
    cdef cppclass AbstractSpatialGame:
        AbstractSpatialGame(int, double);
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
        
    cdef cppclass NovakMayGame(AbstractSpatialGame):
        NovakMayGame(int, double)

    cdef cppclass MeanGame(AbstractSpatialGame):
        MeanGame(int, double)

    cdef cppclass NovakMayTriangularGame(AbstractSpatialGame):
        NovakMayTriangularGame(int, double)

    cdef cppclass MeanTriangularGame(AbstractSpatialGame):
        MeanTriangularGame(int, double)

    cdef cppclass DoubleMeanFieldGame(AbstractSpatialGame):
        DoubleMeanFieldGame(int, double, double);
        void set_b(double, double);
        void set_field(vector[int], vector[int]);
        vector[double] get_bs();
        vector[double] get_persistences();
