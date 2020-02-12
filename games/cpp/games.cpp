#include "games.h"
#include <cmath>
#include <iostream>
#include <numeric>


void NovakMayGame::calculate_scores(std::vector<double> &scores){
    scores.assign(L*L, 0);
    double density = densities.back();

    //Payoffs
    for (size_t k = 0; k < L*L; k++) {
        int y = k / L; // Row
        int x = k % L; // Col

        for (int i = -1; i <= 1; i++) //Row
        {
            for (int j = -1; j <= 1; j++) //Col
            {
                size_t memberIndex = (x + i + L) % L + L * ((y + j + L) % L);
                scores[k] += field[memberIndex];
            }
        }

        if (field[k] == 0)
        {
            scores[k] = scores[k] * b;
        }
    }
}

void MeanGame::calculate_scores(std::vector<double> &scores){
    scores.assign(L*L, 0);
    double density = densities.back();

    //Payoffs
    for (size_t k = 0; k < L*L; k++) {
        int y = k / L; // Row
        int x = k % L; // Col

        for (int i = -1; i <= 1; i++) //Row
        {
            for (int j = -1; j <= 1; j++) //Col
            {
                size_t memberIndex = (x + i + L) % L + L * ((y + j + L) % L);
                if((i == 0)&&(j == 0)){
                    scores[k] += density;
                } else {
                    scores[k] += field[memberIndex];// == 0 ? 1 : 0;
                }
            }
        }

        if (field[k] == 0)
        {
            scores[k] = scores[k] * b;
        }
    }
}
