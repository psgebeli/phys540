#include <cmath>
using std::sin;
using std::lround;

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

double sind_data[1440];
bool is_sind_prepped = false;

void sind_prep(void)
{
   for (size_t n = 0; n < 1440; ++n)
      sind_data[n] = sin(0.5*n*M_PI/360.0);
   is_sind_prepped = true;
}

double sind(double degrees)
{
   assert(is_sind_prepped);
   const size_t n = lround(4*degrees)%1440;
   return sind_data[n];
}

int main()
{
   sind_prep();
   cout << "# angle [degree]  |  sin(angle)" << endl;
   for (size_t n = 0; n <= 1440; ++n)
   {
      const double angle = 0.25*n;
      cout << setw(12) << angle << setw(16) << sind(angle) << endl;
   }
   return 0;
}

