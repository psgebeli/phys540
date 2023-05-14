#include <cassert>

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <algorithm>
using std::swap;

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
   return 0;
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
         last[1] = 1;
      else
      {
         // (!) increment elements of current
         swap(current,last);
         for (int k = 0; k < Smax; ++k)
            current[k] = 0;
      }

      // (!) uncomment the following line
      //assert(n%2 == 1 or int(verify_singlet(n)) == last[0]);

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
      cout << '|' << setw(7) << num_states << endl;
   }
   crossbar();


   return 0;
}

