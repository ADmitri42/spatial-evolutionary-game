#include <iostream>
#include <vector>
#include "utilities.h"
#include "games.h"
#include <numeric>

using namespace std;

const string failed = "FAILED";
const string successful = "OK";


int main() {
    bool pass;
    vector<int> field;

    cout << "Game:\t\t\t";
    pass = true;
    field = { 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
              1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,
              1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1,
              1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,
              1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
              0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
              1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
              1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
              1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
              1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
              1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
              1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
              1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
              1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
              1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0,
              0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
              1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0,
              1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1,
              1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1,
              1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    vector<int> changed_field = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
                                 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
                                 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
                                 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0,
                                 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
                                 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
                                 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
                                 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
                                 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0,
                                 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0,
                                 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1,
                                 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1};
    MeanGame game(20, 1.3);
    game.set_field(field);
    game.evolve(10);
    field = game.get_field();
    if((field.size() != changed_field.size())){
        cout << failed << endl;

        cout << "\tWrong field size" << endl;
        pass = false;
    } else if(!(field == changed_field)){
        cout << failed << endl;
        cout << "\tEvolution failed" << endl;
        pass = false;
    } else {
        cout << successful << endl;
    }

    cout << "N-M distribution:\t";
    pass = true;
//    field = changed_field;
    game.set_field(changed_field);
    vector<int> answer = {0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 1, 0, 0, 0, 0, 0,
                          0, 0, 1, 0, 1, 17, 0, 1, 19,
                          0, 0, 0, 0, 7, 13, 16, 11, 44,
                          0, 0, 0, 0, 0, 3, 10, 12, 33,
                          0, 0, 0, 0, 0, 5, 4, 2, 21,
                          0, 0, 0, 0, 0, 0, 1, 4, 13,
                          0, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<int> result = n_m_distribution(game);
    if(result.size() != 81){
        cout << failed << endl;
        cout << "\tWrong size" << endl;
        pass = false;
    } else if(!(result == answer)){
        cout << failed << endl;
        cout << "\tWrong distribution" << endl;
        cout << "\t" << std::accumulate(result.begin(),result.end(),0) << endl;
        for(int i = 0; i < 9; i++){
            for (int j = 0; j < 9; ++j) {
                cout << result[i*9+j] << "\t";
            }
            cout << endl;
        }
        pass = false;
    }

    if(pass){
        cout << successful << endl;
    }

    cout << "Clustering:\t\t";
    pass = true;
    field = {1, 0, 0, 1, 0,
             0, 1, 1, 1, 0,
             1, 0, 0, 0, 0,
             1, 0, 1, 1, 0,
             0, 0, 1, 0, 0};

    vector<int> labeled_field = {1, 0, 0, 2, 0,
                                 0, 2, 2, 2, 0,
                                 3, 0, 0, 0, 0,
                                 3, 0, 4, 4, 0,
                                 0, 0, 4, 0, 0};
    vector<int> cluster_size = {0, 1, 4, 2, 3};
    LabeledField** lbf = clustering(field, 5, 5);

    if(lbf[1]->cluster_sizes.size() != cluster_size.size()){
        cout << failed << endl;
        cout << "\tWrong number of 1's clusters(" << lbf[1]->cluster_sizes.size() << " instead of " << cluster_size.size() << endl;
        pass = false;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                std::cout << lbf[1]->labeled_field[i*5+j];
            }
            std::cout << std::endl;
        }
    } else if(lbf[0]->cluster_sizes.size() != 2){
        cout << failed << endl;
        cout << "\tWrong number of 0's clusters" << endl;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                std::cout << lbf[0]->labeled_field[i*5+j];
            }
            std::cout << std::endl;
        }
        for(auto t: lbf[1]->cluster_sizes){
            std::cout << t << " ";
        }
        pass = false;
    } else if(lbf[1]->labeled_field.size() != labeled_field.size()){
        cout << failed << endl;
        cout << "\tWrong size of field" << endl;
        pass = false;
    } else {
        if(!(lbf[1]->labeled_field == labeled_field)){
            cout << failed << endl;
            cout << "\tWrong cluster number" << endl;
            pass = false;
        }
        if(!(lbf[1]->cluster_sizes == cluster_size)){
            cout << failed << endl;
            for(auto t: lbf[1]->cluster_sizes){
                std::cout << t << " ";
            }
            cout << "\tWrong cluster size" << endl;
            pass = false;
        }
    }
    if(pass) {
        cout << successful << endl;
    }
    return 0;
}