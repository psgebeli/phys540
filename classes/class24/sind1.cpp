#include <cmath>
using std::sin;

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

double sind(double degrees)
{
   const double radians = degrees*2.0*M_PI/360.0;
   return sin(radians);
}

int main()
{
   cout << "# angle [degree]  |  sin(angle)" << endl;
   for (size_t n = 0; n <= 1440; ++n)
   {
      const double angle = 0.25*n;
      cout << setw(12) << angle << setw(16) << sind(angle) << endl;
   }
   return 0;
}

