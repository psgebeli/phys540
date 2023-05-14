#include <cassert>

#include <iostream>
using std::endl;
using std::cout;
using std::ostream;

#include <limits>
using std::numeric_limits;

#include "bitconvert.h"
const float neg_inf = -1.0F / 0.0F; // will be used in later assertion

int main()
{
   assert(sizeof(float) == sizeof(uint32_t));
   assert(sizeof(double) == 2*sizeof(uint32_t));
   assert(sizeof(uint64_t) == 2*sizeof(uint32_t));
   //assert(sizeof(convert64_t) == sizeof(uint64_t));
   
   cout << "Single-precision floating point: " << endl;
   convert32_t S;

   // 32-bit float: s1 e8 f23 : s x 2^(e-offset)*(1 + .f)
   //  s/eeeeeeee/fffffffffffffffffffffff
   //  1 11122223 33344445555666677778888
   //  \________________________________/

   // ONE
   //  0/01111111/00000000000000000000000
   //  1 11122223 33344445555666677778888
   //  \________________________________/
   //      3   F    8   0   0   0   0   0
   // +2^0*(1+.0000....)_2
   S.I32 = 0x3F800000;
   //S.F32 = 1.0F;
   show_bits(cout,S);
   cout << S.F32 << endl << endl;
   assert(S.F32 == 1.0F);

   // THREE
   //  0/10000000/10000000000000000000000
   //  1 11122223 33344445555666677778888
   //  \________________________________/
   //      4   0    4   0   0   0   0   0
   // +2^1*(1+.1000....)_2 = 2*1.5 = 3
   S.I32 = 0x40400000;
   //S.F32 = 3.0F;
   show_bits(cout,S);
   cout << S.F32 << endl << endl;
   assert(S.F32 == 3.0F);

   // NEGATIVE EIGHTEEN
   //  1/10000011/00100000000000000000000
   //  1 11122223 33344445555666677778888
   //  \________________________________/
   //      C   1    9   0   0   0   0   0
   // -2^4*(1+.1000....)_2 = -16*1.125 = -18
   S.I32 = 0xC1900000;
   //S.F32 = -18F;
   show_bits(cout,S);
   cout << S.F32 << endl << endl;
   assert(S.F32 == -18.0F);

   // 214.25 
   // from the provided identity
   // 0/10000110/10101100100000000000000
   // 1 11122223 33344445555666677778888
   //  \_______________________________/
   //     4   3   5   6   4   0   0   0
   // 2^7*(1+.1000....)_2 = 128*1.673828125 = 214.25
   S.I32 = 0x43564000;
   //S.F32 = 214.25F;
   show_bits(cout,S);
   cout << S.F32 << endl << endl;
   assert(S.F32 == 214.25F);

   // negative infinity
   // 1/11111111/00000000000000000000000
   // 1 11122223 33344445555666677778888
   //  \_______________________________/
   //    F   F   8   0   0   0   0   0
   // -2^128*(1+.1000....)_2 = -3.4E38 * 1.... = neg_inf
   S.I32 = 0xFF800000;
   //S.F32 = -inf;
   show_bits(cout,S);
   cout << S.F32 << endl << endl;
   assert(S.F32 == neg_inf);

   return 0;
}

