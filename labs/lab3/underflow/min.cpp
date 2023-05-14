#include <iostream>
using std::cout;
using std::endl;

#include <limits>
using std::numeric_limits;

#include <iomanip>
using std::setw;

#include <cmath>
using std::log10;

int main()
{
   const int pf = std::numeric_limits<float>::digits10;
   const int pd = std::numeric_limits<double>::digits10;
   const int pld = std::numeric_limits<long double>::digits10;
   const int pad = 10;

   float f = 1.0F;
   double d = 1.0;
   long double ld = 1.0L;

   const float finv = 1.0F / numeric_limits<float>::infinity();
   const double dinv = 1.0 / numeric_limits<double>::infinity();
   const long double ldinv = 1.0L / numeric_limits<long double>::infinity();

   // everything up to this point has been unchanged, besides redefining the
   // constants as 1/infinity for each data type (aka ~~0)

   cout.setf(std::ios::scientific);
   while (true)
   {
      cout.precision(pf-1);
      if (f == 0.0F)
         cout << setw(pf+pad) << "exact zero";
      else
         cout << setw(pf+pad) << f;
      cout.precision(pd-1);
      if (d == 0.0)
         cout << setw(pd+pad) << "exact zero";
      else
         cout << setw(pd+pad) << d;
      cout.precision(pld-1);
      if (ld == 0.0L)
         cout << setw(pld+pad) << "exact zero";
      else
         cout << setw(pld+pad) << ld;
      cout << endl;

      if (f == finv and d == dinv and ld == ldinv) break;

      f /= 10.0F;
      d /= 10.0;
      ld /= 10.0L;
      // also mostly unchanged besides dividing each value by 10 in each
      // increment rather than multiplying it by 10

      // and also printing within a set of if/else loops that checks
      // if the result is 0.0000.... and prints exact zero in that case,
      // otherwise it prints the result
   }

   return 0;
}
