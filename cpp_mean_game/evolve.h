#ifndef __EVOLVE_FIELD__
#define __EVOLVE_FIELD__

#include<vector>

class Game{
private:
    std::vector<int> field;
    std::vector<double> densities;
    int L;
    double b;

public:
    Game(int size, double _b=1.8);

    void evolve(int num_steps = 0);

    std::vector<double> get_densities();
    int size();
    double get_b();
    void set_b(double new_b);
    std::vector<int> get_field();
    void set_field(const std::vector<int> &new_field);

    int* get_field_pointer();
    int get_densities_size();
    double* get_densities_pointer();
};

#endif
