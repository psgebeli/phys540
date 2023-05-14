#include <cstddef>
using std::size_t;

#include <iostream>
using std::cout;
using std::endl;

#include <chrono>
using namespace std::chrono;

bool expensive_test(void)
{
   auto start = high_resolution_clock::now();
   while (duration_cast<milliseconds>
         (high_resolution_clock::now() - start).count() < 200)
   {}
   return true;
}

int main()
{
   cout << "Start" << endl;
   auto start = high_resolution_clock::now();
   for (size_t n = 1; n <= 50; ++n)
   {
      cout << n;
      //if (n%2 == 0 and expensive_test())
      if (expensive_test() and n%2 == 0)
         cout << " is even";
      else
         cout << " is odd";
      cout << " (" << duration_cast<milliseconds>
         (high_resolution_clock::now() - start).count() << " ms)" << endl;
   }
   cout << "Stop" << endl;
   return 0;
}

