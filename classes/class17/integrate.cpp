#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <cmath>
using std::cos;
using std::pow;

#include <array>
using std::array;

#include <random>
using std::mt19937;
using std::uniform_real_distribution;
using std::uniform_int_distribution;

// mersenne twistor random number generator
static mt19937 rng; 
// random number drawn uniformly from [0,1)
static auto rnd = bind(uniform_real_distribution<double>(0,1),std::ref(rng));
// random number drawn uniformly from {1,2,3,4,5,6} 
static auto rnd_die = bind(uniform_int_distribution<double>(1,6),std::ref(rng)); 

void init_random()
{
   std::array<int,624> seed_data;
   std::random_device r;
   std::generate_n(seed_data.data(), seed_data.size(), std::ref(r));
   std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
   rng.seed(seq);
}

double trapezoidIntegrator( double (&f)(double), double a, double b, unsigned int N)
{
   assert(N > 0);
   const double width = b-a;
   const double h = width/N;
   double sum = 0.5*( f(a) + f(b) );
   for (unsigned int i = 1; i < N; ++i)
   {
      const double x_i = a + i*h;
      sum += f(x_i);
   }
   return sum*h;
}

double f(double x)
{
   const double c = cos(pow(x,3.5));
   return x*x*c*c;
}

int main()
{
   cout.precision(14);
   cout << "Trapezoid rule:" << endl;
   unsigned int slices[7] = { 10, 50, 250, 1000, 5000, 25000, 100000 };
   for (auto s : slices)
   {
      cout << "I = " << trapezoidIntegrator(f,0.0,2.0,s) << " (" << s << " slices)" << endl;
   }

   init_random();
   cout << "Monte Carlo:" << endl;
   unsigned int samples[3] = { 1000, 10000, 100000 };
   double sum = 0.0;
   unsigned int count = 0;
   for (auto max : samples)
   {
      for (; count < max; ++count)
      {
         const double x = pow(8.0*rnd(),1.0/3.0);
         const double c = cos(pow(x,3.5));
         sum += c*c;
      }
      cout << "I = " << (8.0/3.0)*sum/count << " (" << max << " samples)" << endl;
   }
	return 0;
}
