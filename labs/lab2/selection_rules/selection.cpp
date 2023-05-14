#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

bool valid_l(int l, int n) { return l >= 0 and l < n; }
bool valid_m(int m, int l) { return m >= -l and m <= l; }

int main()
{
   const int Nmax = 20;
   for (int n2 = 1; n2 <= Nmax; ++n2)
      for (int n1 = 1; n1 < n2; ++n1)
      {
         // (!) insert your code here
      }
   return 0;
}

