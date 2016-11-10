#ifndef _DTW_H_
#define _DTW_H_

#include <vector>
#include <iostream>
 
/**

* Dtw function that given two matrix of cep coefficient computes distance

* between those two signals.
*  @param n_ck         Dimension of unknow signal
*  @param n_cunk         Dimension of know signal
*  @param dim_mfcc  Size of nfcc decompostion base
*  @param c_k       Matrix of know signal
*  @param c_unk     Matrix of unknow signal
*  @return Distance between the two signals
* @file
*/
float dtw(int n_ck, int n_cunk, int dim_mfcc, float * c_k, float * c_unk);

float distance_vect(std::vector<std::vector<float>> sequence1, std::vector<std::vector<float>>  sequence2, int i, int j);

#endif