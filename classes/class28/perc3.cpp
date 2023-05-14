// depleted lattice

#include <cstddef>
using std::size_t;

#include <cstdlib>
using std::exit;
using std::atof;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <iomanip>
using std::setw;

#include <functional>
using std::bind;
using std::ref;

#include <random>
using std::mt19937;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::random_device;
using std::seed_seq;

// mersenne twistor random number generator
static mt19937 rng; 
// draw a real random number uniformly from [0,1)
static auto rnd = bind(uniform_real_distribution<double>(0,1),ref(rng)); 

#include <array>
using std::array;

void initialize_rng()
{
   array<int,624> seed_data;
   random_device r;
   generate_n(seed_data.data(), seed_data.size(), std::ref(r));
   seed_seq seq(std::begin(seed_data), std::end(seed_data));
   rng.seed(seq);
}

#include "grid.hpp"

rect_grid<cell> G;

void initialize_grid(double p)
{
   for (size_t i = 0; i < G.horizontal_dim(); ++i)
      for (size_t j = 0; j < G.vertical_dim(); ++j)
      {
         G(i,j).cluster_membership = -1;
         G(i,j).is_removed = ( rnd() > p );
      }
}

long int assign_membership(size_t i, size_t j, long int m)
{
   if (!G(i,j).is_removed and G(i,j).cluster_membership == -1)
   {
      long int cluster_size = 1;
      G(i,j).cluster_membership = m;
      if (i+1 < G.horizontal_dim())
         cluster_size += assign_membership(i+1,j,m);
      if (i-1 < G.horizontal_dim())
         cluster_size += assign_membership(i-1,j,m);
      if (j+1 < G.vertical_dim())
         cluster_size += assign_membership(i,j+1,m);
      if (j-1 < G.vertical_dim())
         cluster_size += assign_membership(i,j-1,m);
      return cluster_size;
   }
   else
      return 0;
}

void build_clusters(unsigned long int &Nmax, double &N2, double &N4)
{
   long int m = 0;
   Nmax = 0;
   N2 = 0.0;
   N4 = 0.0;
   for (size_t i = 0; i < G.horizontal_dim(); ++i)
      for (size_t j = 0; j < G.vertical_dim(); ++j)
         if (!G(i,j).is_removed and G(i,j).cluster_membership == -1)
         {
            const size_t Ncl = assign_membership(i,j,m++);
            if (Ncl > Nmax) Nmax = Ncl;
            const double x = Ncl;
            const double x2 = x*x;
            N2 += x2;
            N4 += x2*x2;
         }
}

void usage()
{
   cerr << "Usage: perc3 (0 < L <= 1000) (0 <= p <= 1)" << endl;
   exit(1);
}

int main(int argc, char *argv[])
{
   if (argc != 3) usage();
   const size_t L = atoi(argv[1]);
   if (!(L > 0 and L <= 1000)) usage();
   const double p = atof(argv[2]);
   if (!(p >= 0.0 and p <= 1.0)) usage();
   G.set_length(L,L);

   initialize_rng();

   // you may want to reduce Nsamples to 1000, 500, or 100, depending
   // on your patience and how fast your own machine is
   const unsigned int Nsamples = 5000; 
   unsigned long int cluster_largest = 0;
   double cluster_2nd_moment = 0.0;
   double cluster_4th_moment = 0.0;
   for (unsigned int k = 0; k < Nsamples; ++k)
   {
      initialize_grid(p);
      unsigned long int Nmax;
      double N2, N4;
      build_clusters(Nmax, N2, N4);
      cluster_largest += Nmax;
      cluster_2nd_moment += N2;
      cluster_4th_moment += N4;
   }

   cout << setw(20) << double(cluster_largest)/Nsamples
        << setw(20) << cluster_2nd_moment/Nsamples
        << setw(20) << cluster_4th_moment/Nsamples << endl;

   return 0;
}

