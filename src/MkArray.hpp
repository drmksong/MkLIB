//---------------------------------------------------------------------------
#ifndef MkVectHPP
#define MkVectHPP

#undef _MSC_EXTENSIONS

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/type_traits.hpp>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <string>
#include <new>
#include "MkMisc.hpp"
//---------------------------------------------------------------------------

// template <typename T>
// class Array {
// private:
//     T *ptr;
//     int size;
// public:
//     Array(T arr[], int s);
//     void print();
// };

// TODO: role of sz_x and FI should be fixed.
// FIXME: one of them has to be size(FI, ...) and the other has to be capacity (sz_x, ...)

template <class T>
class MkArray
{
private:
  int FDimension;
  int FI, FJ, FK;
  T Zero;

  // T *F;
  long sz_x, sz_y, sz_z;

public:
  boost::shared_ptr<T[]> F{NULL};
  MkArray(int, int, int);
  MkArray(int, int);
  MkArray(int);
  MkArray();
  ~MkArray();
  void Clear();
  void Initialize(int s_x, int s_y, int s_z);
  void Initialize(int s_x, int s_y);
  void Initialize(int s_x);

  T &operator()(int, int, int);
  T &operator()(int &, int &);
  T &operator()(int &&, int &&);
  T &operator()(int);
  T &operator[](int i) { return operator()(i); }
  MkArray<T> &operator=(const MkArray<T> &a);
  MkArray<T> &operator=(MkArray<T> &&a);

  MkArray<T> &operator+=(MkArray<T> &a);
  MkArray<T> &operator+=(T &a);
  MkArray<T> &operator+=(T &&a);
  MkArray<T> &operator-=(MkArray<T> &a);
  MkArray<T> &operator-=(T &a);
  MkArray<T> &operator-=(T &&a);
  MkArray<T> &operator*=(T a);
  MkArray<T> &operator/=(T a);

  bool operator==(MkArray<T> &a);
  bool operator!=(MkArray<T> &a);

  friend MkArray<T> &operator+(MkArray<T> &a, MkArray<T> &b)
  {
    static MkArray<T> c;
    c.Clear();
    if (a.sz_x != b.sz_x || a.sz_y != b.sz_y || a.sz_z != b.sz_z)
      return c;

    c.Initialize(a.sz_x, a.sz_y, a.sz_z);

    for (int i = 0; i < a.sz_x; i++)
      for (int j = 0; j < a.sz_y; j++)
        for (int k = 0; k < a.sz_z; k++)
          c(i, j, k) = a(i, j, k) + b(i, j, k);

    return c;
  }

  friend MkArray<T> &operator-(MkArray<T> &a, MkArray<T> &b)
  {
    static MkArray<T> c;
    c.Clear();
    if (a.sz_x != b.sz_x || a.sz_y != b.sz_y || a.sz_z != b.sz_z)
      return c;

    c.Initialize(a.sz_x, a.sz_y, a.sz_z);

    for (int i = 0; i < a.sz_x; i++)
      for (int j = 0; j < a.sz_y; j++)
        for (int k = 0; k < a.sz_z; k++)
          c(i, j, k) = a(i, j, k) - b(i, j, k);

    return c;
  }

  friend MkArray<T> &operator*(MkArray<T> &a, T b)
  {
    static MkArray<T> c;
    c.Initialize(a.sz_x, a.sz_y, a.sz_z);
    for (int i = 0; i < a.sz_x; i++)
      for (int j = 0; j < a.sz_y; j++)
        for (int k = 0; k < a.sz_z; k++)
          c(i, j, k) = a(i, j, k) * b;

    return c;
  }
  friend MkArray<T> &operator/(MkArray<T> &a, T b)
  {
    static MkArray<T> c;
    if (b < FTOL && b > -FTOL)
      return a;
    c.Initialize(a.sz_x, a.sz_y, a.sz_z);
    for (int i = 0; i < a.sz_x; i++)
      for (int j = 0; j < a.sz_y; j++)
        for (int k = 0; k < a.sz_z; k++)
          c(i, j, k) = a(i, j, k) / b;

    return c;
  }

  long getSzX() const { return sz_x; }
  long getSzY() const { return sz_y; }
  long getSzZ() const { return sz_z; }

  class Alloc
  {
  public:
    std::string What;
    Alloc(std::string what) : What(what) {}
    const char *what() { return What.c_str(); }
  };
  class Size
  {
  public:
    std::string What;
    int X, Y, Z;
    Size(std::string what, int x, int y, int z) : What(what), X(x), Y(y), Z(z) {}
    Size(std::string what, int x, int y) : What(what), X(x), Y(y), Z(1) {}
    Size(std::string what, int x) : What(what), X(x), Y(1), Z(1) {}
    const char *what() { return What.c_str(); }
  };
  class Range
  {
  public:
    std::string What;
    int N;
    Range(std::string what, int n) : What(what), N(n) {}
    const char *what() { return What.c_str(); }
  };
};

typedef class MkArray<int> MkInt;
typedef class MkArray<float> MkFloat;
typedef class MkArray<double> MkDouble;

template class MkArray<int>;
template class MkArray<float>;
template class MkArray<double>;

#endif
