#include <cassert>

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <algorithm>
using std::swap;

#include <cmath>
using std::pow; // used to express num_states = 2^N


const int Nmax = 16;
const int Sshow = 7;
const int Smax = Nmax+1;

int buffer1[Smax];
int buffer2[Smax];

int* last = buffer1;
int* current = buffer2;

void crossbar(void)
{
   cout << "   +";
   for (int i = 0; i < Sshow; ++i)
      cout << "-------";
   cout << "+-------" << endl;
}

unsigned long int verify_singlet(unsigned long int N)
{
   // (!) write the function body
  if (N % 2 == 0) { // if N is even (otherwise, it cant be a singlet)
    unsigned long int res = 1;
    for (unsigned long int k=1; k <= N/2; ++k){ // calculate N choose N/2 
      res *= (N - k + 1); // gives the numerator (N-k+1) * (N-k+2) *...* N = N!/(N/2)!
      res /= k; // gives the denom k * (k+1) * .. * (N/2 - 1)*N/2 = (N/2)! 
    }
    return res / (N / 2 + 1); // the fraction above / (N/2 + 1) == # singlets, as given in instructions
    
  } else {
    return 0; // no singlet states for odd N
  }
}


int main()
{
   for (int i = 0; i < Smax; ++i)
      last[i] = current[i] = 0;

   for (int i = 0; i < Sshow; ++i)
      cout << setw(i == 0 ? 11 : 7) << i/2.0;
   cout << setw(7) << "num" << endl;
   crossbar();

   for (int n = 1; n <= Nmax; ++n)
   {
      if (n == 1)
	last[1] = 1; // spin 1/2 states
      else
      {
         // (!) increment elements of current
	for (int i = 1; i < n; i++)
	  {
	    current[i] = last[i-1] + last[i+1]; // each element in a row should equal the sum of the
	    // previous + preceding terms in the previous row.
	  }

	
	current[n] = 1; // the last element of each row should be 1
	current[0] = last[1]; // the first element of each row should be the second element of the
	// previous row

	swap(current,last);
	
         for (int k = 0; k < Smax; ++k)
            current[k] = 0;
      }

      // (!) uncomment the following line
      //      cout << "verify_singlet(" << n << ") = " << verify_singlet(n) << endl;
      //      cout << "last[0] = " << last[0] << endl;
      // used this to debug why my assertion was failing
      
       assert(n%2 == 1 or int(verify_singlet(n)) == last[0]);

      cout << setw(3) << n << "|";
      for (int i = 0; i < Sshow; ++i)
      {
         cout << setw(7);
         if (last[i] == 0)
            cout << ' ';
         else
            cout << last[i];
      }
      unsigned long int num_states = 0;
      // (!) accumulate values in num_states
      num_states = pow(2,n); // self explanatory
      
      cout << '|' << setw(7) << num_states << endl;
   }
   crossbar();


   return 0;
}

