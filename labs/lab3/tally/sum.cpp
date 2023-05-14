#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

int main()
{
  // We need to calculate the sum for several N, so we can store the values
  // of N in an array and then pluck out the ones we need.

  int N[] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

  // we will use a nested for loop, where the inner loop calculates the
  // sum from n to N, and the outer loop changes the value of N
  // and we will do the same thing for descending


  
  for (int i = 0; i < 8; i++) // since we have 8 N elements
    {

      
      // ASCENDING

      float x = 0.0f;
      long int n = N[i];

      for (int j = 1; j <= n; j++)
	x += 1.0f/j;

      // DESCENDING
      
      float y = 0.0f;
      
      for (int k = n; k >= 1; k--)
	y += 1.0f/k;

      cout << setw(10) << n << setw(15) << x << setw(15) << y << endl;
    }

  


  return 0;
}

 
