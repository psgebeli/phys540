#include <numeric>
using std::gcd; // greatest common divisor

#include <iostream>
using std::ostream;

class rational
{
public:
   long int numerator;
   long int denominator;
   rational() : numerator(0), denominator(1) {}
   rational(long int n) : numerator(n), denominator(1) {}
   rational(long int n, long int d) : numerator(n), denominator(d) 
   {
      if (d < 0)
      {
         numerator *= -1;
         denominator *= -1;
      }
      const long int divisor = gcd(numerator, denominator);
      assert(numerator%divisor == 0);
      assert(denominator%divisor == 0);
      numerator /= divisor;
      denominator /= divisor;
      { // sanity check
         const long int divisor = gcd(numerator, denominator);
         assert(divisor == 1);
      }
   }
   operator double() const 
   { 
      return double(numerator)/double(denominator); 
   }
   friend rational operator+(const rational &r, const rational &s)
   {
      // rn/rd + sn/sd = (rn*sd + sn*rd) / (rd*sd)
      return rational(r.numerator*s.denominator 
         + s.numerator*r.denominator, r.denominator*s.denominator);
   }
   friend rational operator*(const rational &r, const rational &s)
   {
      // rn/rd * sn/sd = (rn*sn) / (rd*sd)
      return rational();
   }
   friend rational inverse(const rational &r)
   {
      return rational(r.denominator,r.numerator);
   }
   friend ostream& operator<<(ostream& os, const rational &r)
   {
      if (r.denominator == 1)
         os << r.numerator;
      else
         os << r.numerator << "/" << r.denominator;
      return os;
   }
};
