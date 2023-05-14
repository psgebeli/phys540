#include <iostream>
using std::cout;
using std::endl;

#include <iomanip> // header file for special iostream manipulators
using std::setw;   // sets the character width of the output

// C and C++ support function overloading. The following three functions
// have the same name but are distinguished by their different argument
// lists.

double polynom(double a, double b, double x) // first-order polynomial
{
   return a*x + b;
}

double polynom(double a, double b, double c, double x) // second-order polynomial
{
   return (a*x + b)*x + c;
}

double polynom(double a, double b, double c, double d, double x) // third-order polynomial
{
   return ((a*x + b)*x + c)*x + d;
   // why this rather than "return a*x*x*x + b*x*x + c*x + d"?
   // Hint: count the number of operators
}

double polynom(double a, double b, double c, double d, double e, double x) // 4th order
{
  return (((a*x + b)*x + c)*x + d)*x +e; 
}

int main()
{
   cout.precision(6);
   // It's bad practice to write the loop this way:
   //    for (double x = -10.0; x <= 10.0; x += 0.2)
   // Think about why.
   // Instead, we should count up in integer steps:
   for (int i = -150; i <= 150; ++i)
   {
      const double x = i*0.1;
      cout << setw(5) << x << setw(10) << polynom(1,2,3,x) << setw(10) << polynom(-1.0/8, -1.0/2, 0, 1, 2,x) << setw(10) << endl;
   }
   return 0;
}

