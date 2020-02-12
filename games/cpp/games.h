#ifndef __EVOLVE_FIELD__
#define __EVOLVE_FIELD__

#include<vector>
#include "spatgame.h"

class MeanGame: public AbstractSpatialGame {
public:
    MeanGame(size_t size, double _b=1.8): AbstractSpatialGame(size, _b) {};

    void calculate_scores(std::vector<double> &scores);
};

#endif
