#include <cstddef>
using std::size_t;

#include <cstdlib>
using std::atoi;
using std::exit;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <iomanip>
using std::setw;

#include "mtrand.hpp"
mtrand R;

void bad(void) {

    cerr << "Usage: corners #points" << endl;
    exit(1);
}

int main(int argc, char* argv[]) {

    if (argc != 2) bad();
    size_t N;
    {
        const int N_ = atoi(argv[1]);
        if (N_ < 1) bad();
        N = N_;
    }

    unsigned long int corners[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

    for (size_t n = 0; n < N; ++n) {

        const double x = 2.0*R() - 1.0;
        const double y = 2.0*R() - 1.0;
        const double z = 2.0*R() - 1.0;

        size_t k = 0;
        if (x > 0.0) k += 1; // binary 001
        if (y > 0.0) k += 2; //        010
        if (z > 0.0) k += 4; //        100
        ++corners[k]; // corner[k] = corner[k] + 1
        //       ^
        //       0-7

    }

    for (size_t k = 0; k < 8; ++k) {
        
        cout << k << " " << double(corners[k])/N << endl;
    }

    return 0;

}
