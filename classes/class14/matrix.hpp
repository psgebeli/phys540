#ifndef MATRIX_HPP

#include <cstddef>
using std::size_t;

#include <algorithm>
using std::swap;

#include <vector>
using std::vector;

#include <iostream>
using std::cerr;
using std::endl;
using std::ostream;

#include <iomanip>
using std::setw;

class matrix
{
private:
   vector<double> data;
   size_t r, c;
public:
   matrix() : data(), r(0), c(0) {}
   matrix(size_t r_, size_t c_) : data(r_*c_,0.0), r(r_), c(c_) {}
   matrix(const vector<double> &v, size_t r_, size_t c_) : data(v), r(r_), c(c_) {}
   // copy constructor
   matrix (const matrix& A) : data(A.data), r(A.r), c(A.c)
   {
      cerr << "Copy constructor" << endl;
   }
   // move constructor
   matrix(matrix&& A) : matrix()
   {
      cerr << "Move constructor" << endl;
      swap(*this, A);
   }
   size_t size() const { return data.size(); }
   void reinit(int r_, int c_)
   {
      r=r_;
      c=c_;
      data.resize(r*c);
      data.assign(r*c,0.0);
   }
   size_t rows() const { return r; }
   size_t cols() const { return c; }
   double operator[](size_t n) const { return data[n]; }
   double& operator[](size_t n) { return data[n]; }
   double operator()(size_t i, size_t j) const { return data[c*i + j]; }
   double& operator()(size_t i, size_t j) { return data[c*i + j]; }
   friend void swap(matrix& A, matrix& B)
   {
      swap(A.data, B.data);
      swap(A.r, B.r);
      swap(A.c, B.c);
   }
   /*matrix& operator=(matrix A) // important: copy, not a reference here
   {
       swap(*this, A);
       return *this;
   }*/
   matrix& operator=(matrix&& A) // move assignment
   {
      cerr << "Move assignment" << endl;
      swap(*this, A);
      return *this;
   }
   double dot(const matrix& A)
   {
      assert(this->size() == A.size());
      double sum = data[0]*A[0];
      for (size_t n = 1; n < A.size(); ++n)
         sum += data[n]*A[n];
      return sum;
   }
   matrix transpose()
   {
      matrix B(cols(),rows());
      for (size_t i = 0; i < B.cols(); ++i)
         for (size_t j = 0; j < B.rows(); ++j)
            B(i,j) = this->operator()(j,i);
      return B;
   }
   /*friend matrix operator+(const matrix& A, const matrix &B)
   {
      assert(A.rows()==B.rows());
      assert(A.cols()==B.cols());
      matrix C(A.rows(),A.cols());
      for (size_t n = 0; n < C.size(); ++n)
         C[n] = A[n] + B[n];
      return C;
   }*/
   friend matrix operator+(matrix A, const matrix &B) // A is a local copy
   {
      assert(A.rows()==B.rows());
      assert(A.cols()==B.cols());
      for (size_t n = 0; n < A.size(); ++n)
         A[n] += B[n];
      return A;
   }
   friend matrix operator*(const matrix& A, const matrix &B)
   {
      matrix C(A.rows(),B.cols());
      assert(A.cols() == B.rows());
      for (int i = 0; i < C.rows(); ++i)
         for (int k = 0; k < C.cols(); ++k)
      {
         C(i,k) = 0.0;
         for (int j = 0; j < A.cols(); ++j)
            C(i,k) += A(i,j)*B(j,k);
      }
      return C;
   }
   friend matrix operator*(double s, const matrix &A)
   {
      matrix B(A.rows(),A.cols());
      for (size_t n = 0; n < A.size(); ++n)
         B[n] = s*A[n];
      return B;
   }
   friend matrix operator*(const matrix &A, double s)
   {
      return operator*(s,A);
   }
   friend ostream& operator<<(ostream& os, const matrix &A)
   {
      os.precision(4);
      for (int i = 0; i < A.rows(); ++i)
      {
         os << (i == 0 ? '/' : i == A.rows()-1 ? '\\' : '|');
         for (int j = 0; j < A.cols(); ++j)
            os << setw(5) << A(i,j);
         os
            << ' ' << (i == 0 ? '\\' : i == A.rows()-1 ? '/' : '|') 
            << endl;
      }
      return os;
   }
   friend bool operator==(const matrix &A, const matrix &B)
   {
      if (A.rows() != B.rows()) return false;
      if (A.cols() != B.cols()) return false;
      for (int n = 0; n < A.size(); ++n)
         if (A[n] != B[n])
            return false;
      return true;
   }
   friend bool operator!=(const matrix &A, const matrix &B)
   {
      return !(A==B);
   }
};

double dot(const matrix& A, const matrix& B)
{
   assert(A.size() == B.size());
   double sum = A[0]*B[0];
   for (size_t n = 1; n < A.size(); ++n)
      sum += A[n]*B[n];
   return sum;
}

matrix transpose(const matrix& A)
{
   matrix B(A.cols(),A.rows());
   for (size_t i = 0; i < B.cols(); ++i)
      for (size_t j = 0; j < B.rows(); ++j)
         B(i,j) = A(j,i);
   return B;
}

#endif // MATRIX_HPP
