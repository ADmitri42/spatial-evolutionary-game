#include "evolve.h"
#include <cmath>
#include <iostream>
#include <numeric>


/*
 * initialize game field with vector for densities
 *
 * size - length of field
 * _b - initial payoff parameter
 */
MeanGame::MeanGame(int size, double _b){
    L = size;
    field.assign(L*L, 0);
    densities.push_back(0);
    b = _b;
}

/*
 * return vector of densities for all steps after resetting field
 */
std::vector<double> MeanGame::get_densities(){
    return densities;
}

int MeanGame::size(){
    return L;
}

double MeanGame::get_b(){
    return b;
}

/*
 * Set new payoff parameter
 * (doesn't reset the statistic)
 */
void MeanGame::set_b(double new_b){
    b = new_b;
}

std::vector<int> MeanGame::get_field(){
    return field;
}

/*
 * Set new field
 * (statistic would be reset)
 */
void MeanGame::set_field(const std::vector<int> &new_field){
    if(new_field.size() != L*L){
        throw std::length_error("Wrong size");
    }
    field.assign(new_field.begin(), new_field.end());
    densities.clear();
    densities.push_back(static_cast<double>(accumulate(field.begin(),field.end(),0))/field.size());
}

/*
 * Evolve num_steps
 */
void MeanGame::evolve(int num_steps)
{
    std::vector<double> scores(L*L, 0);
    std::vector<int> currentField(L*L, 0);

    double density;

    for(int step = 0; step < num_steps; step++)
    {
        //Field
        std::copy(field.begin(), field.end(), currentField.begin());

        //Scores
        scores.assign(L*L, 0);
        density = densities.back();

        //Payoffs
        for (int k = 0; k < L*L; k++) {
            int y = k / L; // Row
            int x = k % L; // Col

            for (int i = -1; i <= 1; i++) //Row
            {
                for (int j = -1; j <= 1; j++) //Col
                {
                    int memberIndex = (x + i + L) % L + L * ((y + j + L) % L);
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

        //Strategy
        for (int k = 0; k < L*L; k++) {
            int y = k / L; // Row
            int x = k % L; // Col

            int bestStrategyIndex = k;

            for (int i = -1; i <= 1; i++) //Row
            {
                for (int j = -1; j <= 1; j++) //Col
                {
                    int memberIndex = (x + i + L) % L + L * ((y + j + L) % L);

                    if (scores[bestStrategyIndex] < scores[memberIndex])
                    {
                        bestStrategyIndex = memberIndex;
                    }
                }
            }

            field[k] = currentField[bestStrategyIndex];
        }
        densities.push_back((1.*accumulate(field.begin(),field.end(),0))/field.size());
    }

    scores.clear();
    currentField.clear();
}

/*
 * Methods that simplify NumPy Array creation
 */
int* MeanGame::get_field_pointer(){
    return &field[0];
}

int MeanGame::get_densities_size(){
    return densities.size();
}

double* MeanGame::get_densities_pointer(){
    return &densities[0];
}