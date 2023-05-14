#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#include <cmath>
using std::sin;
using std::cos;
using std::exp;
using std::fabs; // abs for floats

double newton_raphson(double (&f)(double),
		      double (&fp)(double),
		      double x0, double tolerance) // fp is f prime
{
  while (true) {
    
    const double dx = f(x0)/fp(x0);
    if (fabs(dx) < tolerance) return x0;
    x0 -= dx;
    cerr << " !! " << x0 << endl;
  }
}

// this function is useful if u dont have access to the derivative

double secant_method(double (&f)(double),
		     double x, double xx, double tolerance) 
{
  double dx;
  do {
    dx = -(xx-x)*f(xx)/(f(xx)-f(x));
    x = xx;
    xx += dx;
  } while (fabs(dx) > tolerance);
  return xx;
}

double g(double x) { return exp(-x) - sin(x); }
double gprime(double x) { return -exp(-x) - cos(x); }

int main()
{
  const double x1 = newton_raphson(g,gprime,0.1,1.2e-7);
  const double x2 = secant_method(g,0.0,0.2,1.2e-7);

  cout.precision(12);
  cout
    << "Root of g(x) = exp(-x) - sin(x) found at" << endl
    << " x = " << x1 << endl
    << "(x = " << x2 << ")" << endl;

  return 0;
}
