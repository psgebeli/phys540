#include <cstddef>

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

double A[4*4] = { 1, 2, 3, 4,
		  4, 1, 6, 2,
		  7, 8, 1, 3,
		  1, 5, 9, 2 };

double I[4*4] = { 1, 0, 0, 0,
		  0, 1, 0, 0,
		  0, 0, 1, 0,
		  0, 0, 0, 1 };

double u[4] = { -1, 2, 5, -4 };
double v[4] = { -2, 3, -1, 8 };

size_t idx4(size_t i, size_t j) { return 4*i + j; }

double inner_prod(const double u[], const double v[], int N) { // N = length

  double sum = u[0]*v[0];
  for (int i = 1; i < N; ++i) sum += u[i]*v[i];
  return sum;
}

void outer_prod(double out[], const double u[], const double v[], int N, int M) {

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      out[M*i+j] = u[i]*v[j];
}

void multiply(double out[], const double inL[], const double inR[],
	      int N, int K, int M) {

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
      out[M*i + j] = 0.0;
      for (int k = 0; k < K; ++k) out[M*i+j] += inL[M*i+k]*inR[K*k+j];
    }
}

int main()
{
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      cout << setw(5) << A[idx4(i,j)];
    }
    cout << endl;
  }
  double B[4*4] = {0};
  for (size_t n = 0; n < 16; ++n)
    B[n] = A[n] + 3*I[n];

  return 0;
}
