#include <iostream>
#include <vector>
#include "utilities.h"
#include "evolve.h"
#include <numeric>

using namespace std;

const string failed = "FAILED";
const string successful = "OK";


int main() {
    bool pass;
    vector<int> field;

    cout << "Game:\t\t";
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
                          0, 0, 0, 1, 2, 0, 0, 2, 0,
                          0, 0, 1, 0, 1, 14, 0, 2, 15,
                          0, 0, 0, 1, 6, 12, 17, 10, 41,
                          0, 0, 0, 0, 1, 3, 9, 13, 34,
                          0, 0, 0, 0, 0, 5, 3, 5, 23,
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

    cout << "Clustering:\t";
    pass = true;
    field = {1, 0, 0, 1, 1,
             0, 1, 1, 1, 0,
             1, 0, 0, 0, 0,
             1, 0, 1, 1, 0,
             0, 0, 1, 0, 0};

    vector<int> labeled_field = {1, 0, 0, 2, 2,
                                 0, 2, 2, 2, 0,
                                 3, 0, 0, 0, 0,
                                 3, 0, 4, 4, 0,
                                 0, 0, 4, 0, 0};
    vector<int> cluster_size = {0, 1, 5, 2, 3};
    LabeledField* lbf = clustering(field, 5, 5);

    if(lbf->cluster_sizes.size() != cluster_size.size()){
        cout << failed << endl;
        cout << "\tWrong number of clusters" << endl;
        pass = false;
    } else if(lbf->labeled_field.size() != labeled_field.size()){
        cout << failed << endl;
        cout << "\tWrong size of field" << endl;
        pass = false;
    } else {
        if(!(lbf->labeled_field == labeled_field)){
            cout << failed << endl;
            cout << "\tWrong cluster number" << endl;
            pass = false;
        }
        if(!(lbf->cluster_sizes == cluster_size)){
            cout << failed << endl;
            cout << "\tWrong cluster size" << endl;
            pass = false;
        }
    }
    if(pass) {
        cout << successful << endl;
    }
    return 0;
}