#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memcmp
#include <stdint.h> // for int16_t and int32_t
#include <math.h>
#include <vector>
#include "dtw.h"


using namespace std;

void print(vector<vector<int> > matrice , int ligne , int colonne) {
    for (int i=0;i<ligne;i++) {
        for (int j=0;j<colonne;j++) {
            cout<<matrice[i][j]<<endl;
        }
    }
}

/**
* Dtw function that given two matrix of cep coefficient computes distance
* between those two signals.
*  @param n_ck      Dimension of unknow signal
*  @param n_cunk    Dimension of know signal
*  @param dim_mfcc  Size of nfcc decompostion base
*  @param c_k       Matrix of know signal
*  @param c_unk     Matrix of unknow signal
*  @return Distance between the two signals
*/

float dtw(int n_ck, int n_cunk, int dim_mfcc, float* c_k, float* c_unk) {

vector<vector<float> > g;
g.resize(n_ck*n_cunk);
	double inf=1.0/0.0;
	int contrainte = max(contrainte, abs(n_ck-n_cunk));



    for(int j=1;j<n_cunk+1;j++ ) {
        g[0][j] = inf;
    }


    for (int i=1;i<n_ck+1;i++) {
        g[i][0] = inf;
    }


    for (int i=1;i<n_ck+1;i++) {
        for (int j=max(2,i-contrainte);i<min(n_cunk+1,i+contrainte);i++) {
             int d = distance_vect(c_k ,c_unk , n_ck, n_cunk);
             g[i][j] = d + min(g[i-1][j]), g[i-1][j-1],  g[i][j-1]);


        }


    }

    print(g,n_ck,n_cunk);


    return (g(n_ck+1,n_cunk+1))/(n_ck+n_cunk);


}

int main() {

float* sequence1 = {1,2,3,4,5,6};
float* sequence2 = {1,2,3,4,5,6};

float result = dtw(6,6,sequence1,sequence2);
return 0;


}

float distance_vect(vector<vector <float>> sequence1, vector<vector<float>> sequence2, int i, int j){
	float d = 0;
	int taille = sequence1.front().size();
	int cmp;
	for(cmp = 0; cmp < taille; ++cmp){
		d += pow(sequence1.at(i).at(cmp) - sequence2.at(i).at(cmp), 2);
	}
	return sqrt(d);
}


