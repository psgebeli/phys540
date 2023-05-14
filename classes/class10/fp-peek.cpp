#include <cassert>

#include <iostream>
using std::endl;
using std::cout;
using std::ostream;

#include "bitconvert.h"

int main()
{
  assert(sizeof(double) == 2*sizeof(uint32_t));
  assert(sizeof(uint64_t) == 2*sizeof(uint32_t));
  assert(sizeof(convert64_t) == sizeof(uint64_t));

  cout << "Double-precision floating point: " << endl;
  convert64_t D;

  // 64-bit float: s1 e11 m52 (bit pattern) s * 2^(e-offset) * (1+.m)
  // s/eeeeeeeeeee/mmmmmmmmmmmm...
  // 1 11122223333 444455556666...
  // \_________________________________/\_________________________/
  //                HIGH                         LOW

  // ONE
  // +2^0*(1+.00000)_2
  // s/eeeeeeeeeee/mmmmmmmmmmmm...
  // 0 01111111111 000000000000...
  //     3   F   F   0   0   0

  
  D.I32[HIGH_BITS] = 0x3FF00000;
  D.I32[LOW_BITS] = 0x00000000;
  show_bits(cout,D);
  cout << "1 --> " << D.F64 << endl << endl;
  assert(D.F64 == 1);

  // TWO-epsilon (largest binary number i can make under 2)
  // +2^0*(1+0.111111 ...)_2
  // s/eeeeeeeeeee/mmmmmmmmmmmm...
  // 0 01111111111 111111111111...
  //     3   F   F   1   1   1


  D.I32[HIGH_BITS] = 0x3FFFFFFF;
  D.I32[LOW_BITS] = 0xFFFFFFFF;
  show_bits(cout,D);
  cout << "2-epsilon --> " << D.F64 << endl << endl;
  assert(D.F64 == 1);


  
  return 0;
    }
