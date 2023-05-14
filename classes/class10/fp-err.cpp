#include <cassert>

#include <cstdlib>
using std::atoi;

#include <cmath>
using std::sqrt;
using std::tan;
using std::isinf;

#include <iostream>
using std::endl;
using std::cout;
using std::ostream;

#include "bitconvert.h"

int main(int argc, char*argv[])
{
  convert64_t D;
  assert(argc == 2);
  int c = atoi(argv[1]);
  switch (c)
    {
    case 1:
      cout << "Positive overflow:" << endl;
      D.F64 = 1.0;
      while (!isinf(D.F64))
	{
	  D.F64 *= 8.0;
	  cout << endl << "---> " << D.F64 << "  <---" << endl;
	  show_bits(cout,D);
	}
      break;

    case 2:
      cout << "Negative overflow" << endl;
      D.F64 = -1.0;
      while (!isinf(D.F64))
	{
	  D.F64 *= 8.0;
	  cout << endl << "---> " << D.F64 << "  <---" << endl;
	  show_bits(cout,D);
	}
      break;

    case 3:
      cout << "Near misses:" << endl;
      cout << "-1 + 0.1 + ... + 0.1 (ten times) = "
	   << -1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1
	   << endl;
      cout << "tan(-pi) = " << tan(-M_PI) << endl;
      cout << "tan(pi/2) = " << tan(0.5*M_PI) << endl;
      break;

      
    }
  return 0;
}
