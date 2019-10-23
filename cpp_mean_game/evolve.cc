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
Game::Game(int size, double _b){
    L = size;
    field.assign(L*L, 0);
    densities.push_back(0);
    b = _b;
}

/*
 * return vector of densities for all steps after reseting field
 */
std::vector<double> Game::get_densities(){
    return densities;
}

int Game::size(){
    return L;
}

double Game::get_b(){
    return b;
}

/*
 * Set new payoff parameter
 * (doesn't reset the statistic)
 */
void Game::set_b(double new_b){
    b = new_b;
}

std::vector<int> Game::get_field(){
    return field;
}

/*
 * Set new field
 * (statistic would be reset)
 */
void Game::set_field(const std::vector<int> &new_field){
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
void Game::evolve(int num_steps)
{
    int size = L;

    std::vector<double> scores(size*size, 0);
    std::vector<int> currentField(size*size, 0);

    double density;

    for(int step = 0; step < num_steps; step++)
    {
        //Field
        std::copy(field.begin(), field.end(), currentField.begin());

        //Scores
        scores.assign(size*size, 0);
        density = densities.back();

        //Payoffs
        for (int k = 0; k < size*size; k++) {
            int y = k / size; // Row
            int x = k % size; // Col

            for (int i = -1; i <= 1; i++) //Row
            {
                for (int j = -1; j <= 1; j++) //Col
                {
                    int memberIndex = (x + i + size) % size + size * ((y + j + size) % size);
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
        for (int k = 0; k < size*size; k++) {
            int y = k / size; // Row
            int x = k % size; // Col

            int bestStrategyIndex = k;

            for (int i = -1; i <= 1; i++) //Row
            {
                for (int j = -1; j <= 1; j++) //Col
                {
                    int memberIndex = (x + i + size) % size + size * ((y + j + size) % size);

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
 * Methods for easier creating of numpy array in cython
 */
int* Game::get_field_pointer(){
    return &field[0];
}

int Game::get_densities_size(){
    return densities.size();
}

double* Game::get_densities_pointer(){
    return &densities[0];
}