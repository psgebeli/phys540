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

#include <algorithm>
using std::set_union;

const double C = 60.0;

void report(set<pair<double,size_t>> &S)
{
   for (auto [c, n] : S)
      cout << c << "  (x" << n << ")" << endl;
}

// We should really use a rational number class here in
// place of the double, as we did in the capacitor2.py
// code. Otherwise, there will be duplicates. See the
// capcount2.cpp program, where I've made that change.
set<pair<double,size_t>> this_set = { { C, 1 } };

int main(int argc, char* argv[])
{
   if (argc != 2)
   {
      cerr << "Usage: capcount <max number of capacitor elements>" << endl;
      exit(1);
   }
   const size_t nmax = atol(argv[1]);
      
   cout << "Single capacitor:" << endl;
   report(this_set);

   size_t sizestep = 1;
   while (true)
   {
      set<pair<double,size_t>> next_set;
      const size_t l = this_set.size();
      for (auto [ cA, nA ] : this_set)
      {
         for (auto [ cB, nB ] : this_set)
         {
            const int n = nA + nB;
            if (n <= nmax)
            {
               next_set.insert({ cA+cB, n });
               next_set.insert({ 1.0/(1.0/cA+1.0/cB), n });
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
      const size_t ll = this_set.size();
      if (l == ll) break;
   }
   
   cout << "Up to " << nmax << " capacitors:" << endl;
   report(this_set);
}