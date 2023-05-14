#include <iostream>
using std::cout;
using std::endl;

#include <limits>
using std::numeric_limits;

#include <iomanip>
using std::setw;

#include <cmath>
using std::log;

int main()
{
   const int pf = std::numeric_limits<float>::digits10;
   const int pd = std::numeric_limits<double>::digits10;
   const int pld = std::numeric_limits<long double>::digits10;
   const int pad = 10;

   float f = 1.0F;
   double d = 1.0;
   long double ld = 1.0L;

   const float finf = numeric_limits<float>::infinity();
   const double dinf = numeric_limits<double>::infinity();
   const long double ldinf = numeric_limits<long double>::infinity();

   cout.setf(std::ios::scientific);
   while (true)
   {
      cout.precision(pf-1);
      cout << setw(pf+pad) << f;
      cout.precision(pd-1);
      cout << setw(pd+pad) << d;
      cout.precision(pld-1);
      cout << setw(pld+pad) << ld << endl;

      if (f == finf and d == dinf and ld == ldinf) break;

      f *= 10.0F;
      d *= 10.0;
      ld *= 10.0L;
   }

   return 0;
}

