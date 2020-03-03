#ifndef __EVOLVE_FIELD__
#define __EVOLVE_FIELD__

#include<vector>
#include "spatgame.h"

class NovakMayGame: public AbstractSpatialGame {
public:
    NovakMayGame(size_t size, double _b=1.8): AbstractSpatialGame(size, _b) {};
    void calculate_scores(std::vector<double> &scores);
};

class MeanGame: public AbstractSpatialGame {
public:
    MeanGame(size_t size, double _b=1.8): AbstractSpatialGame(size, _b) {};
    void calculate_scores(std::vector<double> &scores);
};

class NovakMayTriangularGame: public AbstractSpatialGame {
public:
    NovakMayTriangularGame(size_t size, double _b=1.8): AbstractSpatialGame(size, _b) {};
    void calculate_scores(std::vector<double> &scores);
    void update_field(const std::vector<double> &scores, int time_moment, int percfrom = -1, int perctill = -1);
};

class MeanTriangularGame: public AbstractSpatialGame {
public:
    MeanTriangularGame(size_t size, double _b=1.8): AbstractSpatialGame(size, _b) {};
    void calculate_scores(std::vector<double> &scores);
    void update_field(const std::vector<double> &scores, int time_moment, int percfrom = -1, int perctill = -1);
};

#endif
