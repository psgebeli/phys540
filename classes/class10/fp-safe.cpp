#include <cassert>

#include <cmath>
using std::fabs;

#include <iostream>
using std::endl;
using std::cout;
using std::ostream;

#include <vector>
using std::vector;

#include <utility>
using std::pair;

#include <tuple>
using std::tuple;

double norm_unsafe(double x, double y)
{
  return sqrt(x*x + y*y);
}

// if one of x or y (or both) are huge, then their square may not be fp
// representable. however, sqrt(x^2 + y^2) = abs(x)*sqrt[1+(y/x)^2]
// which is still representable, since y < x and x is representable
// same goes for the case where y is large

double norm(double x, double y)
{
  const double xx = fabs(x);
  const double yy = fabs(y);
  if (xx > yy)
    {
      const double r = yy/xx;
      return xx*sqrt(1.0+r*r);
    }else{
    const double r = xx/yy;
    return yy*sqrt(1.0+r*r);
  }

}

// we can do the same thing for the quadratic equation
// - b +/- sqrt(b^2-4ac)               2c
// ______________________ ==  _______________________
//          2a                    -b -/+ sqrt(b^2-4ac)

// same expression but the former might fail for small a (we dont have
// infinite precision

void quadratic_roots_unsafe(double a, double b, double c, double &x1, double &x2)
{
  const double X = sqrt(b*b - 4*a*c);
  x1 = (-b+X)/(2*a);
  x2 = (-b-X)/(2*a);
}
