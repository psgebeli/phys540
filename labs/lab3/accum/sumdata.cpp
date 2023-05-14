#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <limits>
using std::numeric_limits;

#include "add_methods.h"

#include "bitconvert.h"

int main()
{
   vector<float> v;
   float x;
   cin >> x;
   while (cin)
   {
      v.push_back(x);
      cin >> x;
   }
   
   if (v.size() != 0)
   {
      cout.precision(numeric_limits<float>::digits10+1);
      cout.setf(std::ios::scientific);

      convert32_t conventional, increasing, decreasing, pairwise, compensated, high;
      conventional.F32 = add_conventional(v);
      increasing.F32 = add_increasing(v);
      decreasing.F32 = add_decreasing(v);
      pairwise.F32 = add_pairwise(v);
      compensated.F32 = add_compensated(v);
      high.F32 = add_high_precision(v);
      cout << "I've read in " << v.size() << " elements" << endl;
      cout << "                                  s/eeeeeeee/fffffffffffffffffffffff" << endl;
      cout << "conventional sum: " << conventional.F32 << " : "; show_bits(cout,conventional,false);
      cout << "  increasing sum: " << increasing.F32 << " : "; show_bits(cout,increasing,false);
      cout << "  decreasing sum: " << decreasing.F32 << " : "; show_bits(cout,decreasing,false);
      cout << "    pairwise sum: " << pairwise.F32 << " : "; show_bits(cout,pairwise,false);
      cout << " compensated sum: " << compensated.F32 << " : "; show_bits(cout,compensated,false);
      cout << "  high-prec. sum: " << high.F32 << " : "; show_bits(cout,high,false);
   }
   return 0;
}

