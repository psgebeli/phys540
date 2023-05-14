#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
using std::vector;

template <typename T>
class rect_grid
{
private:
   size_t Lx;
   size_t Ly;
   vector<T> data;
public:
   rect_grid(): Lx(0), Ly(0), data() {}
   rect_grid(size_t Lx_, size_t Ly_) : Lx(Lx_), Ly(Ly_), data(Lx_*Ly_) {}
   void set_length(size_t Lx_, size_t Ly_)
   {
      Lx = Lx_;
      Ly = Ly_;
      data.resize(Lx*Ly);
   }
   size_t horizontal_dim(void) { return Lx; }
   size_t vertical_dim(void) { return Ly; }
   T& operator()(size_t i, size_t j)
   {
      assert(i < Lx); assert(j < Ly);
      return data[i+j*Lx];
   }
};

struct cell
{
   bool is_removed;
   long int cluster_membership;
};

#endif
