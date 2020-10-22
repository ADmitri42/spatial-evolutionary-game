//
// Created by Dima on 12.02.2020.
//

#ifndef SPATIAL_EVOLUTIONARY_GAME_SPATGAME_H
#define SPATIAL_EVOLUTIONARY_GAME_SPATGAME_H

#include<vector>
#include <sys/types.h>

class AbstractSpatialGame{
protected:
    std::vector<char> field;
    std::vector<char> unchanged;

    std::vector<double> densities;

    size_t L;
    double b;
    int perCalFrom;
    int perCalTill;

public:
    AbstractSpatialGame(size_t size, double _b=1.8);
    virtual ~AbstractSpatialGame() {};

    virtual void calculate_scores(std::vector<double> &scores);
    virtual void update_field(const std::vector<double> &scores, int time_moment, int percfrom = -1, int perctill = -1);
    void evolve(int num_steps = 0, int percfrom = -1, int perctill = -1);

    std::vector<double> get_densities();
    size_t size();
    virtual double get_b();
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

/*
 * Double field basic game
 * 
 * Two field stored one after th other
 * Density for field 1 has indeces 2n
 * For field 2 indeces 2n+1
 */

class AbstractSpatialGame2Field: public AbstractSpatialGame{
protected:
    double b1, b2;

public:
    AbstractSpatialGame2Field(size_t size, double _b1=1.6, double _b2=1.6);
    virtual ~AbstractSpatialGame2Field() {};

    virtual void calculate_scores(std::vector<double> &scores);
    virtual void update_field(const std::vector<double> &scores, int time_moment, int percfrom = -1, int perctill = -1);
    void evolve(int num_steps = 0, int percfrom = -1, int perctill = -1);

    std::vector<double> get_b();
    void set_b(double new_b1, double new_b2);
    void set_field(const std::vector<int> &new_field1, const std::vector<int> &new_field2);
    std::vector<double> get_persistence();
    /*
     * Function to create numpy array
     */
    char* get_field_pointer();
    int get_densities_size();
    double* get_densities_pointer();
};

#endif //SPATIAL_EVOLUTIONARY_GAME_SPATGAME_H
