#ifndef ADD_PAIRWISE_H
#define ADD_PAIRWISE_H

#include <vector>
using std::vector;

float add_pairwise(const vector<float>&);

float add_pairwise(const float[], int);

float add_increasing(const vector<float> &);

float add_decreasing(const vector<float> &);

float add_conventional(const vector<float> &);

float add_compensated(const vector<float> &);

float add_high_precision(const vector<float> &);

#endif // ADD_PAIRWISE_H