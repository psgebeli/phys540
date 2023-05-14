#include <cstddef>
using std::size_t;

#include <cstdlib>
using std::exit;

#include <random>
using std::mt19937;
using std::uniform_real_distribution;
using std::uniform_int_distribution;

const size_t N = 100000;

static mt19937 rng; // mersenne twistor random number generator
// random number drawn uniformly from {1,2,...,N-2}
static auto rnd = bind(uniform_int_distribution<double>(1,N-2),std::ref(rng));

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::to_string;

#include <algorithm>
using std::max;

#include <fstream>
using std::ofstream;

size_t H[N];
         
int main(int argc, char* argv[])
{
   if (argc != 2)
   {
      cerr << "usage: kpz3 (sticky|nonstick)" << endl;
      exit(1);
   }
   bool is_sticky = argv[1][0] == 's';
   rng.seed(1975);
   for (size_t i = 0; i < N; ++i)
      H[i] = 0;

   size_t n = 0;
   size_t hmax = 0;
   for (size_t drops = 0; drops < 1000*N; ++drops)
   {
       const size_t i = rnd();
       const size_t h = is_sticky ? max(
          max( H[i-1], H[i]+1 ), H[i+1]
             ) : H[i]+1;
       H[i] = h;
       if (h > hmax) hmax = h;
       if (drops%(N/2) == 0)
       {
          n += 1;
          // compute mean column height
          double hmean = 0.0;
          for (size_t i = 0; i < N; ++i)
             hmean += H[i];
          hmean /= N;
          // compute fluctuations about the mean
          double hvar = 0.0;
          for (size_t i = 0; i < N; ++i)
          {
             const double dh = H[i] - hmean;
             hvar += dh*dh;
          }
          hvar /= N;
          cout << n << "\t" << hmax << "\t" << hmean << "\t" << hvar << endl;
       }
    }
    return 0;
}
