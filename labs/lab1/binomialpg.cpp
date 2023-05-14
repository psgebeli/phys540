#include <cstdlib>
using std::atoi;

#include <iostream>
using std::cout;
using std::endl;

#include <algorithm> // used to find min/maxes

// the factorial function is largely unchanged from your original 
// file, I just changed the int type from unsigned long to 
// unsigned long long, to use the most memory possible and 
// avoid overflow

unsigned long long int factorial(unsigned long long int n){
  if (n==0 or n==1)
    return 1ul;
  else{
    unsigned long long int val = 2ul;
    for (unsigned long long int m = 3; m <= n; ++m)
      val*=m;
    return val;
  }
}

unsigned long long int binomial(unsigned long long int n, 
                                unsigned long long int k)
{
  unsigned long long int p = std::max(k, n-k); // find p 

  unsigned long long int q_fac = factorial(std::min(k, n-k)); // find q! (we aim to calculate (p+1 * p+2 * .. n)/q!

  unsigned long long int res = 1; // initialize an integer that we will update below


  // the for loop essentially does the following (I know you dont need 
  // an explanation but its good practice):
  // start with i = p+1. So initially, res = p + 1.
  // add one to res, and multiply this by the previous value of res 
  // (so the second iteration, res = p+1 * p+2)
  // do this until i <= n, giving us p+1 * p+2 * ... n
  // return the result of this value/q!, which is the identity we used.

  for (unsigned long long int i = p+1; i <=  n; i++) 
    res *= i;
  return res/q_fac;

}


int main(int argc, char *argv[]){ // again unchanged asides from new int types
  unsigned long long int n = atoi(argv[1]);
  for (unsigned long long int k = 0; k <= n; ++k){
    cout << "(" << n << " choose " << k << ") = " << binomial(n,k)  << endl;
  }
  return 0;
}
