#include <array>
using std::array;

#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <string>
using std::string;

// This is a 2x2 matrix class that only 
// handles integer entries
class matrix_of_int
{
   private:
      int x11, x12, x21, x22;
   public:
      matrix_of_int(array<int,4> a) : x11(a[0]), x12(a[1]), x21(a[2]), x22(a[3]) {}
      int trace() const { return x11+x22; }
      int det() const { return x11*x22-x12*x21; }
      friend ostream& operator<<(ostream &os, const matrix_of_int &M)
      {
         os << "{" << setw(4) << M.x11 << setw(4) << M.x12 << " }" << endl;
         os << "{" << setw(4) << M.x21 << setw(4) << M.x22 << " }";
         return os;
      }
};

// Here is a generic version.
template <class T>
class matrix
{
   private:
      T x11, x12, x21, x22;
   public:
      matrix(array<T,4> a) : x11(a[0]), x12(a[1]), x21(a[2]), x22(a[3]) {}
      T trace() const { return x11+x22; }
      T det() const { return x11*x22-x12*x21; }
      friend ostream& operator<<(ostream &os, const matrix<T> &M)
      {
         os << "{" << setw(4) << M.x11 << setw(4) << M.x12 << " }" << endl;
         os << "{" << setw(4) << M.x21 << setw(4) << M.x22 << " }";
         return os;
      }
};


int main()
{
   matrix_of_int A(
         { 1, 2,
           3, 4 }
         );
   cout << "A = " << endl << A << endl;
   cout << "tr A = " << A.trace() << endl;
   cout << "det A = " << A.det() << endl;

   matrix_of_int b({ -12, 13, 3, 4});
   cout << "b = " << endl << b << endl; 
   cout << "tr b = " << b.trace() << endl;
   cout << "det b = " << b.det() << endl;

   matrix<double> C({ 0.5, 0.75, 0.25, -0.25});
   cout << "C = " << endl << C << endl; 
   cout << "tr C = " << C.trace() << endl;
   cout << "det C = " << C.det() << endl;

   // char is treated as numeric type in C (a signed integer, int8_t)
   matrix<char> D({ 'a', 'b', 'c', 'd' });
   cout << "D = " << endl << D << endl;
   cout << "tr D = " << D.trace() << endl;
   cout << "det D = " << D.det() << endl;

   // string is not a numeric type. The + operator implements
   // contatenation, but there is no * operator defined for strings.
   // This means that the trace() method is legal, but det() causes
   // an error at compile time.
   matrix<string> E({ "aa", "bb", "cc", "dd" });
   cout << "E = " << endl << E << endl;
   cout << "tr E = " << E.trace() << endl;
   //cout << "det E = " << E.det() << endl;
   
   return 0;
}
