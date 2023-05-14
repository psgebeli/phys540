#include <cstddef>
using std::size_t;

#include <cstdlib>
using std::exit;
using std::atof;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <functional>
using std::bind;
using std::ref;

#include <random>
using std::mt19937;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::random_device;
using std::seed_seq;

const size_t halfLx = 20;
const size_t halfLy = 10;
const size_t Lx = 2*halfLx;
const size_t Ly = 2*halfLy;
enum cell_t { UNASSIGNED = 2, ON = 1, OFF = 0 };
char grid[Lx][Ly];

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

rect_grid<cell> G(40,20);

void initialize_grid(double p)
{
   for (size_t i = 0; i < G.horizontal_dim(); ++i)
      for (size_t j = 0; j < G.vertical_dim(); ++j)
      {
         G(i,j).cluster_membership = -1;
         G(i,j).is_removed = ( rnd() > p );
      }
}

void assign_membership(size_t i, size_t j, long int m)
{
   if (!G(i,j).is_removed and G(i,j).cluster_membership == -1)
   {
      G(i,j).cluster_membership = m;
      if (i+1 < G.horizontal_dim())
         assign_membership(i+1,j,m);
      if (i-1 < G.horizontal_dim())
         assign_membership(i-1,j,m);
      if (j+1 < G.vertical_dim())
         assign_membership(i,j+1,m);
      if (j-1 < G.vertical_dim())
         assign_membership(i,j-1,m);
   }
}

void build_clusters(void)
{
   long int m = 0;
   for (size_t i = 0; i < G.horizontal_dim(); ++i)
      for (size_t j = 0; j < G.vertical_dim(); ++j)
         if (!G(i,j).is_removed and G(i,j).cluster_membership == -1)
            assign_membership(i,j,m++);
}
void display(void)
{
   cout << "+";
   for (size_t i = 0; i < G.horizontal_dim(); ++i)
      cout << "-";
   cout << "+" << endl;

   for (size_t j = 0; j < G.vertical_dim(); ++j)
   {  
      cout << "|";
      for (size_t i = 0; i < G.horizontal_dim(); ++i)
      {
         if (G(i,j).is_removed)
            cout << ' ';
         else
         {
            const size_t sym = 35 + G(i,j).cluster_membership;
            if (sym < 126)
               cout << char(sym);
            else
               cout << char(34);
         }
      }
      cout << "|" << endl;
   }

   cout << "+";
   for (size_t i = 0; i < G.horizontal_dim(); ++i)
      cout << "-";
   cout << "+" << endl;
}

void usage(void)
{
   cerr << "Usage: perc2 (0 < prob < 1)" << endl;
   exit(1);
}

int main(int argc, char *argv[])
{
   if (argc != 2) usage();
   const double p = atof(argv[1]);
   if (!(p >= 0.0 and p <= 1.0)) usage();

   initialize_rng();
   initialize_grid(p);
   build_clusters();
   display();

   return 0;
}

