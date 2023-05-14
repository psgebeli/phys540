#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <sstream>
using std::stringstream;

#include <string>
using std::string;

bool valid_l(int l, int n) { return l >= 0 and l < n; }
bool valid_m(int m, int l) { return m >= -l and m <= l; }

float energy(int n){ // define the energy at the nth orbital
  return (-13.6)/(n*n);
}

float wavelength(float energy){ // define the wavelength at the nth orbital
  const float hc = 1240.0;
  return hc / energy;
}

int main()
{
   const int Nmax = 20;
   for (int n2 = 1; n2 <= Nmax; ++n2)
      for (int n1 = 1; n1 < n2; ++n1)
      {

	int npathways = 0; // initialize a variable that we will increment for each valid transition between n1,n2

	for (int l=0; l<n2; l++) { // a really disgusting nested loop
	  for (int m=-l; m<=l; m++) {
	    if (valid_l(l, n2) && valid_m(m, l)) {
	      for (int l1=0; l1<n1; l1++) {
		if (abs(l-l1) == 1) {
		  for (int m1=-l1; m1<=l1; m1++) {
		    if (valid_l(l1, n1) && valid_m(m1, l1) && (m1==m || m1==m-1 || m1==m+1)) {
		      npathways++;
		      // we calculate the possible ls based on n2. for each l we calculate the possible ms.
		      // if they are both valid (since we add onto them for each increment), then
		      // we check if the transition abides by the electric dipole selection rules
		      // in other words, we then calculate the possible ls and ms for n1. and
		      // then we consider each transition l2-> l1, m2->m1. Only add one to the number of
		      // pathways if the transition is +/- 1 (or 0 in the case of m).
		      // Phew. This loop and comment are disgustingly long.
		    }
		  }
		}
	      }
	    }
	  }
	}
  

        float energy_emitted = energy(n2) - energy(n1); // these two lines are self explanatory
        float lambda = wavelength(energy_emitted);

	stringstream n1stringstream;
	n1stringstream << n1; // create a stringstream object and write the value of n1 onto it
	std::string n1string = n1stringstream.str() + "v"; // store the stringstream as a string and concatenate a "v"
	
	if (lambda >= 380.0 && lambda<= 750.0) // if lambda is visible, print the string above. if not, print normally.
	    cout << n2 << "-->" << n1string << setw(10) << npathways << setw(10) << energy_emitted << setw(10) << lambda << endl;
	  else 
        cout << n2 << "-->" << n1 << setw(10) << npathways << setw(10) << energy_emitted << setw(10) << lambda << endl;

	}
   return 0;
}
