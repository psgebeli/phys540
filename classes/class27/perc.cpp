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

void initialize_grid(void)
{
   for (size_t i = 0; i < Lx; ++i)
      for (size_t j = 0; j < Ly; ++j)
         grid[i][j] = UNASSIGNED;
   grid[halfLx][halfLy] = ON;
}

double prob;
bool sweep_grid(void)
{
   bool made_change = false;
   for (size_t i = 0; i < Lx; ++i)
   {
      for (size_t j = 0; j < Ly; ++j)
      {
         if ( grid[i][j] == UNASSIGNED
            and (grid[(i+1)%Lx][j] == ON
              or grid[(Lx+i-1)%Lx][j] == ON
              or grid[i][(j+1)%Ly] == ON
              or grid[i][(Ly+j-1)%Ly] == ON) )
         {
            made_change = true;
            grid[i][j] = (rnd() < prob ? ON : OFF);
         }
      }
   }
   return made_change;
}

void display(void)
{
   cout << "+";
   for (size_t i = 0; i < Lx; ++i)
      cout << "-";
   cout << "+" << endl;

   for (size_t j = 0; j < Ly; ++j)
   {  
      cout << "|";
      for (size_t i = 0; i < Lx; ++i)
         cout << (grid[i][j] == ON ? 'o' : ' ');
      cout << "|" << endl;
   }

   cout << "+";
   for (size_t i = 0; i < Lx; ++i)
      cout << "-";
   cout << "+" << endl;
}

int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      cerr << "Usage: perc (0 < prob < 1)" << endl;
      exit(1);
   }
   prob = atof(argv[1]);

   initialize_rng();
   initialize_grid();
   while(sweep_grid());
   display();

   return 0;
}

