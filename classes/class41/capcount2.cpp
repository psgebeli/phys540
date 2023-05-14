#include <cstddef>
using std::size_t;

#include <cstdlib>
using std::exit;
using std::atol; // unsafe, but I'm using it for simplicity

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <utility>
using std::pair;

#include <set>
using std::set;

#include "rational.hpp"

const rational C { 60 };

void report(set<pair<rational,size_t>> &S)
{
   for (auto [c, n] : S)
   {
      cout << c;
      if (c.denominator != 1)
         cout << " = " << double(c);
      cout  << "  (x" << n << ")" << endl;
   }
}

set<pair<rational,size_t>> this_set = { { C, 1 } };

int main(int argc, char* argv[])
{
   if (argc != 2)
   {
      cerr << "Usage: capcount2 <max number of capacitor elements>" << endl;
      exit(1);
   }
   const size_t nmax = atol(argv[1]);
      
   cout << "Single capacitor:" << endl;
   report(this_set);

   size_t sizestep = 1;
   while (true)
   {
      set<pair<rational,size_t>> next_set;
      const size_t l = this_set.size();
      for (auto [ cA, nA ] : this_set)
      {
         for (auto [ cB, nB ] : this_set)
         {
            const int n = nA + nB;
            if (n <= nmax)
            {
               next_set.insert({ cA+cB, n });
               next_set.insert({ inverse(inverse(cA)+inverse(cB)), n });
            }
         }
      }
      /* The built-in set union requires a complicated STL
      * iterator syntax.
      this_set = set_union(
      this_set.begin(), this_set.end(), 
      next_set.begin(), next_set.end(),
      distination.begin());
      * I'll do it manually instead by adding all the
      * elements of next_set to this set and then clearing
      * next_set
      */
      for (auto nc : next_set)
         this_set.insert(nc);
      if (this_set.size() > sizestep)
      {
         sizestep *= 2;
         cerr << "Exceeding " << this_set.size() << " combinations!"<< endl;
      }
      //next_set.clear();
      const size_t ll = this_set.size();
      if (l == ll) break;
   }
   
   cout << "Up to " << nmax << " capacitors:" << endl;
   report(this_set);
}