#include <map>
#include <assert.h>
#include "utilities.h"
#include <iostream>

/******************************
 ******************************
 ****                      ****
 ****   N-M distribution   ****
 ****                      ****
 ******************************
 ******************************/

std::vector<int> n_m_distribution(MeanGame &game){
    int L = game.size();
    std::vector<int> field = game.get_field();
    std::vector<double> score(L*L, 0);
    game.calculate_scores(score);
    std::vector<int> nmdistr(9*9, 0);
    int m, n, is;
    double n_sc, m_sc;

    for(int x = 0; x < L; ++x){
        for (int y = 0; y < L; ++y) {
            n = m = -1;
            n_sc = m_sc = -22;
            for (int i = -1; i < 2; ++i) {
                for (int j = -1; j < 2; ++j) {
                    is = ((L+y+j)%L)*L+(L + x+i)%L;
                    if((field[is] == 0)&&(score[is] > m_sc)){
                        m = field[(L*L+is-L-1)%(L*L)] + field[(L*L+is-L)%(L*L)] + field[(L*L+is-L+1)%(L*L)]
                                + field[(L*L+is-1)%(L*L)] +  field[(L*L+is+1)%(L*L)]
                                + field[(L*L+is+L-1)%(L*L)] + field[(L*L+is+L)%(L*L)] + field[(L*L+is+L+1)%(L*L)];

                        m_sc = score[is];
                    }

                    if((field[is] == 1)&&(score[is] > n_sc)){
                        n = field[(L*L+is-L-1)%(L*L)] + field[(L*L+is-L)%(L*L)] + field[(L*L+is-L+1)%(L*L)]
                              + field[(L*L+is-1)%(L*L)] +  field[(L*L+is+1)%(L*L)]
                              + field[(L*L+is+L-1)%(L*L)] + field[(L*L+is+L)%(L*L)] + field[(L*L+is+L+1)%(L*L)];

                        n_sc = score[is];
                    }
                }
            }

            if((m >= 0)&&(n >= 0)){
                nmdistr[m*9 + n] += 1;
            }
//            std::cout << n << " " << m << std::endl;
        }
    }
    return nmdistr;
}


/************************
 ************************
 ****                ****
 ****   CLUSTERING   ****
 ****                ****
 ************************
 ************************/

/*
 * Search for proper cluster label, since neighbor_cl can be not optimal(optimal == smallest os possible)
 */
int classify(int neighbor_cl, std::vector<int> &N){
    int t, r, c = 0;
    r = neighbor_cl;
    t = r;
    t = -N[t];
    while(t >= 0){
        r = t;
        t = -N[t];
        c++;
    }
    if(c > 2){
        N[neighbor_cl] = -r;
    }
    return r;
}

/*
 * Return proper label base on labels of top and left neighbours(0 if not proper class)
 */
int assign_label(int left, int top, std::vector<int> &N){
    int label;
    switch (!!left + !!top){
        case 0:
            N.push_back(1);
            label = N.size() - 1;
            break;
        case 1:
            label = (left == 0) ? top : left;
            label = classify(label, N);
            N[label] += 1;
            break;
        case 2:
            int label1 = classify(left, N);
            int label2 = classify(top, N);
            if (label1 == label2){
                label = label1;
            } else if (label1 > label2){
                label = label2;
                N[label] += N[label1];
                N[label1] = -label;
            } else {
                label = label1;
                N[label] += N[label2];
                N[label2] = -label;
            }
            N[label] += 1;
            break;
    }
    return label;
}

/*
 * Return field with labels
 * N - horizontal size of the field
 * M - vertical size of the field
 * field - vector of size N*M
 */
LabeledField* clustering(const std::vector<int>& field, int N, int M){
    assert((N*M == field.size()));

    // Variables
    int ileft, itop;
    std::vector<int> w_cluster_sizes(1, 0); // For every label on the field it contains size of the cluster
    std::map<int, int> fixed_label;
    LabeledField* lbf = new LabeledField(field.size());


    for(int i = 0; i < field.size(); ++i){
        if(field[i]){
            ileft = (N + i - 1)%N + (i/N) * N;
            itop = (N*M + i - N)%(N*M);
            lbf->labeled_field[i] = assign_label(lbf->labeled_field[ileft],
                                                 lbf->labeled_field[itop],
                                                 w_cluster_sizes);
        }
    }

    // Create map object where current label placed against
    for(int i = 0, counter = 1; i < w_cluster_sizes.size(); ++i){
        if(w_cluster_sizes[i] > 0){
            fixed_label[i] = lbf->cluster_sizes.size();
            lbf->cluster_sizes.push_back(w_cluster_sizes[i]);
            counter++;
        }
    }

    for(int i = 0; i < field.size(); ++i){
        if(field[i]){
            lbf->labeled_field[i] = fixed_label[classify(lbf->labeled_field[i],
                                                          w_cluster_sizes)];
        }
    }
    return lbf;
}