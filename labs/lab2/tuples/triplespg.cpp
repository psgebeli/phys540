/*Task: Modify the program so that instead it counts the number of such triplesGeneralize to integers 0,1,...,N and output the results in two-column format for all values of N from 2 to 10.*/


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
   int number_of_triples;
   for (int N = 2; N <= 10; ++N) // will need to find number of triples for each N
   {
     number_of_triples = 0; // initialize variable that we will increment for each valid
     // triple for that N
     
      for (int k = 2; k <= N; ++k)
         for (int j = 1; j < k; ++j)
            for (int i = 0; i < j; ++i)
	      number_of_triples++; /* same as your code, but rather than printing each
      triple to the terminal, simply add one to the number of triples for this N.
      this will then loop over all N from 2 to 10.*/

      cout << setw(2) << N << setw(15) << number_of_triples << endl;
      // here the set width function is used to create spaces between
      // our output (creates columns)
      // the first width, 2, is the width between the side of the terminal and the first
      // column, then there is a much larger width before the next column
   }

   return 0;
}
