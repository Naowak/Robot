#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memcmp
#include <stdint.h> // for int16_t and int32_t
#include <math.h>
#include <vector>
#include "dtw.h"


using namespace std;

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

/* à compléter */
    
    
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

int main(){
	return 0;
}