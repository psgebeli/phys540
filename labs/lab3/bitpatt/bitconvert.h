#ifndef BITCONVERT_H
#define BITCONVERT_H

#include <iostream>
using std::endl;
using std::ostream;

#include <stdint.h>

// test the endianness of the system
namespace {
const union 
{
   long l;
   char c[4];
} test = { 1L };
}

const bool is_bigendian = test.c[3] and !test.c[2] and !test.c[1] and !test.c[0];
const bool is_littleendian = !test.c[3] && !test.c[2] && !test.c[1] && test.c[0];

const size_t HIGH_BITS = (is_bigendian ? 0 : 1);
const size_t LOW_BITS = (is_bigendian ? 1 : 0);

/*
union convert64_t
{
   uint32_t I32[2];
   uint64_t I64;
   double F64;
};
*/

union convert32_t
{
   uint32_t I32;
   float F32;
};

/*
void show_bits(ostream &os, convert64_t C, bool header = true)
{
   if (header) os << "s/eeeeeeeeeee/fffffffffffffffffffffffffffffffffffffffffffffffffffff" << endl;
   uint64_t L = 0x8000000000000000ULL;
   for (int i=0 ; i < 64; ++i)
   {
      if (i == 1 or i == 12)
         os << " ";
      os << ((C.I64 & L) != 0 ? '1' : '0');
      L >>= 1;
   }
   os << endl;
}
*/

void show_bits(ostream &os, convert32_t C, bool header = true)
{
   if (header) os << "s/eeeeeeee/fffffffffffffffffffffff" << endl;
   uint32_t L = 0x80000000UL;
   for (int i=0 ; i < 32; ++i)
   {
      if (i == 1 or i == 9)
         os << " ";
      os << ((C.I32 & L) != 0 ? '1' : '0');
      L >>= 1;
   }
   os << endl;
}

#endif // BITCONVERT_H

