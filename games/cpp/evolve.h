#ifndef __EVOLVE_FIELD__
#define __EVOLVE_FIELD__

#include<vector>

class MeanGame{
private:
    std::vector<char> field;
    std::vector<char> unchanged;

    std::vector<double> densities;

    size_t L;
    double b;
    int perCalFrom;
    int perCalTill;

public:
    MeanGame(size_t size, double _b=1.8);

    void calculate_scores(std::vector<double> &scores);
    void evolve(int num_steps = 0, int percfrom = -1, int perctill = -1);

    std::vector<double> get_densities();
    size_t size();
    double get_b();
    void set_b(double new_b);
    std::vector<int> get_field();
    void set_field(const std::vector<int> &new_field);
    double get_persistence();
    /*
     * Function to create numpy array
     */
    char* get_field_pointer();
    int get_densities_size();
    double* get_densities_pointer();
};

#endif