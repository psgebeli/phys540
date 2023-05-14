#include <cstddef>
using std::size_t;

#include <random>
using std::mt19937;
using std::uniform_int_distribution;

const size_t N = 1000;

static mt19937 rng;
static auto rnd = bind(uniform_int_distribution<size_t>(1,N-2),std::ref(rng));

#include <vector>
using std::vector;

#include <iostream>
using std::endl;

#include <string>
using std::to_string;

#include <algorithm>
using std::max;

#include <fstream>
using std::ofstream;

vector<size_t> H[N];

void ps(const char* filebase, size_t n, vector<size_t> *H)
{
    ofstream fout(filebase+to_string(n)+".ps");
     fout << "%!\n";
     fout << "%%BoundingBox: 0 0 400 400\n";
     fout << "/mkbox {\n";
     fout << "   newpath\n";
     fout << "   moveto\n";
     fout << "   0 1 rlineto\n";
     fout << "   1 0 rlineto\n";
     fout << "   0 -1 rlineto\n";
     fout << "   closepath\n";
     fout << "   1 0 0 setrgbcolor\n";
     fout << "   fill\n";
     fout << "} def\n";
     fout << 400./(1+N) << " " << 400./(1+N) << " scale\n";
     for (size_t x = 0; x < N; ++x)
         for (auto y : H[x])
             fout << x << " " << y << " mkbox\n";
     fout << "showpage\n";
}

int main()
{
   rng.seed(1975);
   for (size_t i = 0; i < N; ++i)
      H[i].push_back(0);
   size_t n = 0;
   for (size_t drops = 0; drops < 250*N; ++drops)
   {
      const size_t i = rnd();
      const size_t h = max(
            max( H[i-1].back(), H[i].back()+1 ), H[i+1].back()
            );
    H[i].push_back(h);
    if (drops%(N/2)==0)
    {
        n += 1;
        ps("snapshot",n,H);
    }
   }
   return 0;
}
