#include <iostream>
#include "evolve.h"
#include <vector>
#include <chrono>
#include <cstdint>
#include "cnpy.h"


/*
 * Compilation require cnpy lib
 * export LD_LIBRARY_PATH=/usr/local/lib/
 * g++ -o build/realization.out main.cpp -L/usr/local/lib evolve.cc -lcnpy -lz -O3 --std=c++11
 */
using namespace std;

const int total_steps = 18000;
const int drop_steps = 10000;
const int L = 100;
const int fields_number = 40;

vector<int> get_field(int num){
    stringstream ss;
    ss << "fields/field_" << L << "_" << num << ".npy";
    cnpy::NpyArray arr = cnpy::npy_load(ss.str());
    int64_t* loaded_data = arr.data<int64_t>();
    vector<int> field;
    for(int i = 0; i < L*L; i++){
        field.push_back(static_cast<int>(loaded_data[i]));
    }
    return field;
}


int main() {
    cout << "Initializing variables..." << endl;
    vector<double> bs = {1.5       , 1.50689655, 1.5137931 , 1.52068966, 1.52758621,
                         1.53448276, 1.54137931, 1.54827586, 1.55517241, 1.56206897,
                         1.56896552, 1.57586207, 1.58275862, 1.58965517, 1.59655172,
                         1.60344828, 1.61034483, 1.61724138, 1.62413793, 1.63103448,
                         1.63793103, 1.64482759, 1.65172414, 1.65862069, 1.66551724,
                         1.67241379, 1.67931034, 1.6862069 , 1.69310345, 1.7};
    Game game(L);
    vector<double> densities, new_den;
    chrono::duration<double> elapsed;
    cout << "Modeling..." << endl;
    for(int i = 0; i < bs.size(); i++){
        game.set_b(bs[i]);
        auto start = chrono::high_resolution_clock::now();
        for(int j = 0; j < fields_number; j++){
            game.set_field(get_field(j));
            game.evolve(total_steps/2);
            game.evolve(total_steps - total_steps/2);
            new_den = game.get_densities();
            densities.insert(densities.end(), new_den.begin()+drop_steps+1, new_den.end());
            new_den.clear();
        }

        auto finish = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = finish - start;
        cout << i+1 << "\\" << bs.size() << endl
             << "\tOne round in " << elapsed.count() << " s" << endl
             << " Time remaining: " << elapsed.count()*(bs.size()-i-1) << " s" << endl;
        cout << "Saving data: ";

        cnpy::npy_save("data/density_of_cooperators515-17.npy",
                       &densities[0],
                       {i+1, fields_number, total_steps-drop_steps},
                       "w");
        cout << "done" << endl;
    }
    cnpy::npy_save("data/density_of_cooperators515-17.npy",
                   &densities[0],
                   {bs.size(), fields_number, total_steps-drop_steps},
                   "w");
    return 0;
}