#include <cstddef>
using std::size_t;

#include <cstdlib>
using std::exit;
using std::atol;

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

// vector, set, and map are container classes
// in C++'s Standard Template Library (STL)
#include <vector>
using std::vector;

#include <set>
using std::set;

#include <map>
using std::map;

// sort, unique, and accumulate are generic
// algorithms that act on STL containers
#include <algorithm>
using std::sort;
using std::unique;

#include <numeric>
using std::accumulate;

// This problem is drawn from he Collatz conjecture: 
// https://en.wikipedia.org/wiki/Collatz_conjecture
//
// It is believed that the iterative map
//
// F(x) -> { x/2  if x is even, and
//         { 3x+1 if x is odd
//
// eventually transforms any initial seed into a
// sequence that repears 4, 2, 1 forever

long int next_step(long int x)
{
   return x%2 == 0 ? x/2 : 3*x+1;
}

const size_t nmax = 999;
int main(int argc, char* argv[])
{
   if (argc != 2)
   {
      cerr << "usage: collatz <integer start value>" << endl;
      exit(1);
   }

   vector<long int> history;
   set<long int> visited;
   map<long int, size_t> histogram;

   long int x = atol(argv[1]);
   for (size_t n = 0; n < nmax; ++n)
   {
      history.push_back(x);
      visited.insert(x);
      if (!histogram.contains(x))
         histogram[x] = 1;
      else
         histogram[x] += 1;
      x = next_step(x);
   }

   cout << "Complete history:" << endl;
   for (auto x : history)
      cout << x << " ";
   cout << endl;

   cout << endl << "Average value: "
      << accumulate(history.begin(), history.end(), 0.0)/history.size()
      << endl;

   cout << endl << "All values encountered:" << endl;
   for (auto x : visited)
      cout << x << " ";
   cout << endl;

   cout << endl << "All value encountered (alt):" << endl;
   sort(history.begin(), history.end());
   auto endptr = unique(history.begin(), history.end());
   for (auto step = history.begin(); step != endptr; ++step)
      cout << *step << " ";
   cout << endl;

   cout << endl << "Frequency histogram of encountered values:" << endl;
   for (auto [x,freq] : histogram)
      cout << x << ": " << freq << endl;
   cout << endl;

   return 0;
}

