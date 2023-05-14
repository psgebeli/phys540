#include <cstddef>
using std::size_t;

#include <iostream>
using std::cout;
using std::endl;

#include <chrono>
using namespace std::chrono;

size_t fib(size_t n)
{
   if (n < 2) return n; // handle F(0) = 0, F(1) = 1
   size_t x0 = 0;
   size_t x1 = 1;
   for (size_t k = 1; k < n; ++k)
   {
      const size_t x2 = x0+x1;
      x0 = x1;
      x1 = x2;
   }
   return x1;
}

int main()
{
   auto start = high_resolution_clock::now();

   for (size_t n : { 0, 1, 2, 3, 4, 5, 15, 10, 20, 40, 30, 50 })
      cout << "F(" << n << ") = " << fib(n) << endl;

   for (size_t n : { 1, 10, 100, 1000, 10000, 1000, 100, 10, 1 })
      cout << "F(" << n << ") = " << fib(n) << endl;
   auto stop = high_resolution_clock::now();

   cout << "Run time = ";
   auto duration = duration_cast<microseconds>(stop-start);
   cout << duration.count() << " us" << endl;
   return 0;
}

