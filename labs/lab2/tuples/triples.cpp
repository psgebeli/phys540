#include <cassert>

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <cmath>
using std::sqrt;

int main()
{
   const int N = 6;
   for (int k = 2; k <= N; ++k)
      for (int j = 1; j < k; ++j)
         for (int i = 0; i < j; ++i)
            cout << "(" << i << "," << j << "," << k << ")" << endl;
   return 0;
}

