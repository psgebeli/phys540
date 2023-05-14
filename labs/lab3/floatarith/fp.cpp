#include <iostream>
using std::cout;
using std::endl;

template <typename T>
void report(T a, char op, T b, T c)
{
   cout << a << " " << op << " " << b << " = " << c << endl;
}

int main()
{
   const float one = 1.0F;
   const float neg_one = -1.0F;
   
   float zero = one; --zero; // this tricks the compiler
   const float neg_zero = -1.0F * 0.0F; // defining -0 as const for report
   
   const float inf = 1.0F / 0.0F;
   const float neg_inf = -1.0F / 0.0F; // defining infinity and neg infinity as
   // const for report

   const float nan = 0.0F / 0.0F; // defining nan as const for report

   cout << "Floating point division:" << endl;

   report(one,'/',zero,one/zero);
   report(neg_one,'/',zero,neg_one/zero);
   report(zero,'/',zero,zero/zero);
   report(inf,'/',zero,inf/zero);
   report(neg_inf,'/',zero,neg_inf/zero);
   report(inf,'/',inf,inf/inf); // idk what to comment, just reporting what you // want reported :D

   cout << endl; // just used to print a blank line b4 next set of output
   
   cout << "Floating point multiplication:" << endl;

   report(one,'*',zero,one*zero);
   report(neg_one,'*',zero,neg_one*zero);
   report(one,'*',inf,one*inf);
   report(neg_one,'*',inf,neg_one*inf);
   report(zero,'*',inf,zero*inf);
   report(neg_inf,'*',zero,neg_inf*zero);
   report(inf,'*',inf,inf*inf);
   report(inf,'*',neg_inf,inf*neg_inf);
   report(one,'*',nan,one*nan);
   report(neg_one,'*',nan,neg_one*nan);
   report(zero,'*',nan,zero*nan);
   report(neg_zero,'*',nan,neg_zero*nan);

   cout << endl;
   cout << "Floating point addition and subtraction:" << endl;

   report(one,'+',inf,one+inf);
   report(one,'-',inf,one-inf);
   report(inf,'+',inf,inf+inf);
   report(inf,'-',inf,inf-inf);
   report(one,'+',nan,one+nan);
   report(one,'-',nan,one-nan);

   return 0;
}
