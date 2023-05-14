#include <cstddef>
using std::size_t;

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <chrono>
using namespace std::chrono;

size_t fib(size_t n)
{
   static vector<size_t> val;
   if (val.size() == 0)
   {
      val.push_back(0);
      val.push_back(1);
   }
   while (n+1 > val.size())
   {
      const size_t xk = val.back();
      val.pop_back();
      const size_t xkm1 = val.back();
      const size_t xkp1 = xkm1 + xk;
      val.push_back(xk);
      val.push_back(xkp1);
   }
   return val[n];
}

int main()
{
   auto start = high_resolution_clock::now();

   for (size_t n : { 0, 1, 2, 3, 4, 5, 15, 10, 20, 40, 30, 50 })
      cout << "F(" << n << ") = " << fib(n) << endl;

   // F(0): hard-coded special case
   // F(1): ibid.
   // F(2): compute F(2)
   // F(3): compute F(3)
   // F(15): F(4) .. F(15)
   // F(10): look up F(10)
   // F(20): compute F(11) .. F(20)
   // F(40): compute F(21) .. F(3)
   // F(30): loop up F(30)

   for (size_t n : { 1, 10, 100, 1000, 10000, 1000, 100, 10, 1 })
      cout << "F(" << n << ") = " << fib(n) << endl;
   auto stop = high_resolution_clock::now();

   cout << "Run time = ";
   auto duration = duration_cast<microseconds>(stop-start);
   cout << duration.count() << " us" << endl;
   return 0;
}

