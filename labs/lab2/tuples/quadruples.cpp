/*Task: display 3 columns, N from 0-99, # of weakly ordered quadruples,
  and how many of the sums i^2 + j^2 + ... are perfect squares.*/

#include <cassert>

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <cmath>
using std::sqrt;

int main()
{
  for (int N = 0; N <= 99; ++N)
    {
      int number_of_quadruples = 0;
      int number_of_perfect_squares = 0; // init variables that will store the contents of columns 2/3

      for (int l = 0; l <= N; ++l)
        for (int k = 0; k <= l; ++k)
          for (int j = 0; j <= k; ++j)
            for (int i = 0; i <= j; ++i) // same loop as before but with a new int l, and starting from 0
              {
                number_of_quadruples++; // after each iteration add one to num of quads

		/* define the sums of the squares of each integer in the quadruple. then calculate its sqrt, which is done with the cmath function that returns a floating point number.
		// so, cast it back to an integer using (int). This means that if the square is not perfect (i.e not a whole integer), then the float will be rounded down to the nearest
		// integer, and that new integer will be stored as the sqrt. So, if root*root does NOT equal the sum, then it must have been rounded down, so it must have been an
		imperfect square.*/
		
                int sum_of_squares = i*i + j*j + k*k + l*l;
                int root = (int) sqrt(sum_of_squares);
		
                if (root * root == sum_of_squares)
                  {
                    number_of_perfect_squares++; // as described above, if its equal, then the sqrt was originally a whole integer -- so the sum is perfect
                  }
              }

      cout << setw(2) << N << setw(15) << number_of_quadruples << setw(15) << number_of_perfect_squares << endl;
    }

  return 0;
}
