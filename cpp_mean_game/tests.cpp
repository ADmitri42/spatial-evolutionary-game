#include <iostream>
#include <vector>
#include "utilities.h"

using namespace std;

const string failed = "FAILED";
const string successful = "OK";

int main() {

    cout << "Clustering :\t";
    bool pass = true;
    vector<int> field = {1, 0, 0, 1, 1,
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
        for(int i = 0; i < labeled_field.size(); ++i){
            if(lbf->labeled_field[i] != labeled_field[i]){
                cout << failed << endl;
                cout << "\tWrong cluster number" << endl;
                pass = false;
                break;
            }
        }
        for(int i = 0; i < cluster_size.size(); i++){
            if(lbf->cluster_sizes[i] != cluster_size[i]){
                cout << failed << endl;
                cout << "\tWrong cluster size" << endl;
                pass = false;
                break;
            }
        }
    }
    if(pass) {
        cout << successful << endl;
    }
    return 0;
}