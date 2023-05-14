#include <cassert>

#include <iostream>
using std::cout;
using std::endl;

int main()
{
   int a = 1;

   assert(a == 1);
   cout << "2^0 = " << a << endl;
   a = a*2;

   assert(a == 2);
   cout << "2^1 = " << a << endl;
   a = a*2;

   assert(a == 2*2);
   cout << "2^2 = " << a << endl;
   a = a*2;

   assert(a == 2*2*2);
   cout << "2^3 = " << a << endl;
   a = a*2;

   cout << "2^4 = " << a << endl;
   a = a*2;

   cout << "2^5 = " << a << endl;
   a = a*2;

   // end of Dr. Beach's code, beginning of mine
   // first I want to make this grow faster bc i know
   // that the limit will be much a higher power
   

   cout << "2^6 = " << a << endl;
   a = a*2*2*2*2*2;

   cout << "2^11 = " << a << endl;
   a = a * a;

   cout << "2^22 = " << a << endl;
   a = a*2*2*2*2*2*2*2*2;

   cout << "2^30 = " << a << endl;
   a= a*2;
   
   cout << "2^31 = " << a << endl;
   a = a-1;

   // Here, I noticed that the cutoff is somewhere between 2^30 and 2^31,
   // because 2^30 displays the correct value but 2^31 is displayed as
   // negative, and 2^32 displays
   // as zero. So I will now search for values between these.

   cout << "2^31 - 1 = " << a << endl; 

   /*
    Evidently, 2^31 breaks the universe since it is suddenly negative.
    but 2^31 - 1 displays the correct value. Hence 2^31 - 1 seems to be
    the upper limit on integers in cpp.

    I wouldn't imagine a difference in the implementation for the
    other languages, since the limitation comes from the memory
    of my machine itself.
   */
   
   return 0;
}

