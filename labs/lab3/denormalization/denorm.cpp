#include <cassert>

#include <iostream>
using std::endl;
using std::cout;
using std::ostream;

#include "bitconvert.h"

int main()
{
   assert(sizeof(float) == sizeof(uint32_t));
   assert(sizeof(double) == 2*sizeof(uint32_t));
   assert(sizeof(uint64_t) == 2*sizeof(uint32_t));
   //assert(sizeof(convert64_t) == sizeof(uint64_t));

   cout << "Single-precision floating point: " << endl;
   convert32_t S;

   S.F32 = 5.9E-37F;
   show_bits(cout,S);
   cout << S.F32 << endl << endl;

   while (S.F32 != 0)
     {
       S.F32 /= 2.0F;
       show_bits(cout,S);
       cout << S.F32 << endl << endl;
     }

   // created a loop that will repeatedly half the value when it is not equal to zero. when it IS zero, it will terminate, so as to not repeatedly print 0
   
   return 0;
}

