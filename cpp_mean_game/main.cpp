#include <iostream>
#include "evolve.h"
#include <vector>
#include <chrono>
#include <cstdint>
#include "argparser.h"
#include "cnpy.h"


/*
 * Compilation require cnpy lib
 * export LD_LIBRARY_PATH=/usr/local/lib/
 * g++ -o build/realization.out main.cpp -L/usr/local/lib evolve.cc argparser.cpp -lcnpy -lz -O3 --std=c++11
 */
using namespace std;


vector<int> get_field(int num, int L, string f_dir){
    stringstream ss;
    ss << f_dir << "/field_" << L << "_" << num << ".npy";
    cnpy::NpyArray arr = cnpy::npy_load(ss.str());
    int64_t* loaded_data = arr.data<int64_t>();
    vector<int> field;
    for(int i = 0; i < L*L; i++){
        field.push_back(static_cast<int>(loaded_data[i]));
    }
    return field;
}


int main(int argc, char* argv[]) {
    Config config = get_config(argc, argv);
    if(!config->successful){
        return 0;
    }
    cout << "Initializing variables..." << endl;
    vector<double> bs = {1.54137931, 1.63793103};
    MeanGame game(config->L);

    vector<double> densities, new_den, persistence(config->fields_number*bs.size(), -1);
    chrono::duration<double> elapsed;


    cout << "Modeling..." << endl;
    for(int i = 0; i < bs.size(); i++){
        game.set_b(bs[i]);
        auto start = chrono::high_resolution_clock::now();
        for(int j = 0; j < config->fields_number; j++){
            game.set_field(get_field(j, config->L, config->fields_directory));
            //Evaluating
            game.evolve(config->total_steps/2, config->persistence_from, config->persistence_till);
            game.evolve(config->total_steps - config->total_steps/2, config->persistence_from, config->persistence_till);

            // Statistics
            new_den = game.get_densities();
            densities.insert(densities.end(), new_den.begin()+config->drop_steps+1, new_den.end());
            persistence[i*config->fields_number+j] = game.get_persistence();
            new_den.clear();
        }

        auto finish = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = finish - start;
        cout << i+1 << "\\" << bs.size() << endl
             << "\tOne round in " << elapsed.count() << " s" << endl
             << " Time remaining: " << elapsed.count()*(bs.size()-i-1) << " s" << endl;
        cout << "Saving data: ";

        cnpy::npy_save("densities_" + config->output_file,
                       &densities[0],
                       {i+1, config->fields_number, config->total_steps - config->drop_steps},
                       "w");
        cout << "done" << endl;
    }

    cnpy::npy_save("density_" + config->output_file + ".npy",
                   &densities[0],
                   {bs.size(), config->fields_number, config->total_steps - config->drop_steps},
                   "w");

    if(config->persistence_from >=0){
        cnpy::npy_save("persistence_" + config->output_file + ".npy",
                       &persistence[0],
                       {bs.size(), config->fields_number},
                       "w");
    }

    return 0;
}