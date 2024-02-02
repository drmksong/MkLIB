#include "MkArray.hpp"
//---------------------------------------------------------------------------
// ::new convienient float vector class
// This can be any dimension up to 3.
// Vector can be re-initialized even though
// previous data will be erased.
// But if you want to preserve it, you can do it simply...
// Author : M. K. Song. Seoul, Korea. 1999.2.2;
//---------------------------------------------------------------------------

#ifdef __BCPLUSPLUS__
#pragma package(smart_init)
#endif

template <class T>
MkArray<T>::MkArray(int s_x, int s_y, int s_z)
{
  if (s_x <= 0 || s_y <= 0 || s_z <= 0)
  {
    MkDebug("Three D::bad MkArray size\n");
    throw Size(std::string("MkArray<T>"), s_x, s_y, s_z);
  }

  Zero = 0;
  FDimension = 3;
  FI = FJ = FK = 0;

  long sz = long(s_x) * long(s_y) * long(s_z);

  sz_x = long(s_x);
  sz_y = long(s_y);
  sz_z = long(s_z);

  try
  {
    // MkDebug("MkArray memory reset 1\n");
    F = boost::make_shared<T[]>(sz);
  }
  catch (std::bad_alloc &a)
  {
    throw Alloc(std::string("MkArray<T>"));
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }

  for (int i = 0; i < sz; i++)
    F[i] = 0;
}

template <class T>
MkArray<T>::MkArray(int s_x, int s_y)
{
  if (s_x <= 0 || s_y <= 0)
  {
    MkDebug("Two D::bad MkArray size\n");
    throw Size(std::string("MkArray<T>"), s_x, s_y);
  }
  Zero = 0;
  FDimension = 2;
  FI = FJ = FK = 0;

  long sz = long(s_x) * long(s_y);
  sz_x = long(s_x);
  sz_y = long(s_y);
  sz_z = 1;

  try
  {
    // MkDebug("MkArray memory reset 2\n");
    F = boost::make_shared<T[]>(sz);
    // F.reset(new T[sz]);
  }
  catch (std::bad_alloc &a)
  {
    MkDebug("MkArray::MkArray(szx,szy) Not Enough Memory\n");
    throw Alloc(std::string("MkArray<T>"));
  }
  for (int i = 0; i < sz; i++)
    F[i] = 0;
}

template <class T>
MkArray<T>::MkArray(int s_x)
{
  if (s_x <= 0)
  {
    MkDebug("One D::bad MkArray size\n");
    throw Size(std::string("MkArray<T>"), s_x);
  }

  Zero = 0;
  FDimension = 1;
  FI = FJ = FK = 0;

  int sz = s_x;
  sz_x = long(s_x);
  sz_y = 1;
  sz_z = 1;

  try
  {
    // MkDebug("MkArray memory reset 3\n");
    F = boost::make_shared<T[]>(sz);
    // F.reset(new T[sz]);
  }
  catch (std::bad_alloc &a)
  {
    MkDebug("MkArray::MkArray(szx) Not Enough Memory %s\n", a.what());
    throw Alloc(std::string("MkArray<T>"));
  }
  for (int i = 0; i < sz; i++)
    F[i] = 0;
}

template <class T>
MkArray<T>::MkArray(const MkArray<T> &a)
{
  Zero = 0;
  FDimension = 0;
  FI = FJ = FK = 0;

  sz_x = 0;
  sz_y = 0;
  sz_z = 0;
  F.reset();

  operator=(a);
}

template <class T>
MkArray<T>::MkArray()
{
  Zero = 0;
  FDimension = 0;
  FI = FJ = FK = 0;

  sz_x = 0;
  sz_y = 0;
  sz_z = 0;
  F.reset();
}

template <class T>
MkArray<T>::~MkArray()
{
  Clear();
}

template <class T>
void MkArray<T>::Clear()
{
  Zero = 0;
  FDimension = 0;
  FI = FJ = FK = 0;

  sz_x = 0;
  sz_y = 0;
  sz_z = 0;
  // MkDebug("MkArray memory reset 4\n");
  F.reset();
}

template <class T>
void MkArray<T>::Initialize(int s_x, int s_y, int s_z)
{
  if (s_x <= 0 || s_y <= 0 || s_z <= 0)
  {
    MkDebug("bad MkArray size\n");
    throw Size(std::string("MkArray<T>"), s_x, s_y, s_z);
  }

  FDimension = 3;
  FI = FJ = FK = 0;

  long sz = long(s_x) * long(s_y) * long(s_z);
  sz_x = long(s_x);
  sz_y = long(s_y);
  sz_z = long(s_z);

  try
  {
    // MkDebug("MkArray memory reset 5\n");
    F = boost::make_shared<T[]>(sz);
    // F.reset(new T[sz]);
  }
  catch (std::bad_alloc &a)
  {
    MkDebug("Not Enough Memory\n");
    throw Alloc(std::string("MkArray<T>"));
  }

  for (int i = 0; i < sz; i++)
    F[i] = 0;
}

template <class T>
void MkArray<T>::Initialize(int s_x, int s_y)
{
  if (s_x <= 0 || s_y <= 0)
  {
    MkDebug("bad MkArray size\n");
    throw Size(std::string("MkArray<T>"), s_x, s_y);
  }

  FDimension = 2;
  FI = FJ = FK = 0;

  long sz = long(s_x) * long(s_y);
  sz_x = long(s_x);
  sz_y = long(s_y);
  sz_z = 1;

  try
  {
    // MkDebug("MkArray memory reset 6\n");
    F = boost::make_shared<T[]>(sz);
  }
  catch (std::bad_alloc &a)
  {
    MkDebug("Not Enough Memory\n");
    throw Alloc(std::string("MkArray<T>"));
  }
  for (int i = 0; i < sz; i++)
    F[i] = 0;
}

template <class T>
void MkArray<T>::Initialize(int s_x)
{
  if (s_x <= 0)
  {
    MkDebug("bad MkArray size\n");
    throw Size(std::string("MkArray<T>"), s_x);
  }
  FDimension = 1;
  FI = FJ = FK = 0;

  long sz = long(s_x);
  sz_x = long(s_x);
  sz_y = 1;
  sz_z = 1;

  try
  {
    // MkDebug("MkArray memory reset 7\n");
    F = boost::make_shared<T[]>(sz);
  }
  catch (std::bad_alloc &a)
  {
    MkDebug("Not Enough Memory\n");
    throw Alloc(std::string("MkArray<T>"));
  }
  for (int i = 0; i < sz; i++)
    F[i] = 0;
}

// it is destructive, erase the existing array
template <class T>
MkArray<T> &MkArray<T>::operator=(const MkArray<T> &value)
{
  // MkDebug("MkArray op = copy\n");
  // MkDebug("MkArray op = copy 1. 0x%p\n", value.F);
  if (!(value.sz_x * value.sz_y * value.sz_z)) // FIXME: is it an error???
    return *this;

  // MkDebug("MkArray op = copy 2. 0x%p\n", value.F);
  if (sz_x != value.sz_x || sz_y != value.sz_y || sz_z != value.sz_z)
  {
    try
    {
      // MkDebug("MkArray op = copy 3. 0x%p\n", value.F);
      Initialize(value.sz_x, value.sz_y, value.sz_z);
      FDimension = value.FDimension;
      FI = value.FI;
      FJ = value.FJ;
      FK = value.FK;
      sz_x = value.sz_x;
      sz_y = value.sz_y;
      sz_z = value.sz_z;
      Zero = value.Zero;
    }
    catch (Alloc &a)
    {
      MkDebug("MkArray::operator=() thows Alloc()");
      throw Alloc(std::string("MkArray<T>"));
    }
  }
  // MkDebug("MkArray op = copy 4. 0x%p\n", value.F);
  long sz = long(sz_x) * long(sz_y) * long(sz_z);
  for (long i = 0; i < sz; i++)
    F[i] = value.F[i];
  // MkDebug("MkArray op = copy 5. 0x%p\n", value.F);
  return *this;
}

template <class T>
MkArray<T> &MkArray<T>::operator=(MkArray<T> &&value)
{
  MkDebug("MkArry::op = move ... not quitely \n");
  // MkDebug("MkArray op = copy 1. 0x%p\n", value.F);
  if (!(value.sz_x * value.sz_y * value.sz_z)) // FIXME: is it an error???
    return *this;

  // MkDebug("MkArray op = copy 2. 0x%p\n", value.F);
  if (sz_x != value.sz_x || sz_y != value.sz_y || sz_z != value.sz_z)
  {
    try
    {
      // MkDebug("MkArray op = copy 3. 0x%p\n", value.F);
      Initialize(value.sz_x, value.sz_y, value.sz_z);
      FDimension = value.FDimension;
      FI = value.FI;
      FJ = value.FJ;
      FK = value.FK;
      sz_x = value.sz_x;
      sz_y = value.sz_y;
      sz_z = value.sz_z;
      Zero = value.Zero;
    }
    catch (Alloc &a)
    {
      // MkDebug("MkArray::operator=() thows Alloc()");
      throw Alloc(std::string("MkArray<T>"));
    }
  }
  // MkDebug("MkArray op = copy 4. 0x%p\n", value.F);
  long sz = long(sz_x) * long(sz_y) * long(sz_z);
  for (long i = 0; i < sz; i++)
    F[i] = value.F[i];
  // MkDebug("MkArray op = copy 5. 0x%p\n", value.F);
  return *this;
}

template <class T>
T &MkArray<T>::operator()(int &i, int &j, int &k)
{
  // Commented out on 23.02.07 as all the array is three dim
  // if (FDimension != 3)
  // {
  //   char str[256];
  //   sprintf(str, "MkArray::(i,j,k) called whereas Dim is %d ", FDimension);
  //   throw std::logic_error(std::string(str));
  // }

  if (FDimension <= 0)
  {
    MkDebug("Possibly Memory dosen't allocated!\n");
    throw Alloc(std::string("MkArray<T>"));
  }

  if (i < 0 || sz_x <= i)
  {
    MkDebug("MkArray index out of range\n");
    throw Range(std::string("sz_x"), i);
  }
  if (j < 0 || sz_y <= j)
  {
    MkDebug("MkArray index out of range\n");
    throw Range(std::string("sz_y"), j);
  }
  if (k < 0 || sz_z <= k)
  {
    MkDebug("MkArray index out of range\n");
    throw Range(std::string("sz_z"), k);
  }
  return F[long(i) + long(j) * sz_x + long(k) * sz_x * sz_y];
}

template <class T>
T &MkArray<T>::operator()(int &&i, int &&j, int &&k)
{
  // Commented out on 23.02.07 as all the array is three dim
  // if (FDimension != 3)
  // {
  //   char str[256];
  //   sprintf(str, "MkArray::(i,j,k) called whereas Dim is %d ", FDimension);
  //   throw std::logic_error(std::string(str));
  // }

  if (FDimension <= 0)
  {
    MkDebug("Possibly Memory dosen't allocated!\n");
    throw Alloc(std::string("MkArray<T>"));
  }

  if (i < 0 || sz_x <= i)
  {
    MkDebug("MkArray index out of range\n");
    throw Range(std::string("sz_x"), i);
  }
  if (j < 0 || sz_y <= j)
  {
    MkDebug("MkArray index out of range\n");
    throw Range(std::string("sz_y"), j);
  }
  if (k < 0 || sz_z <= k)
  {
    MkDebug("MkArray index out of range\n");
    throw Range(std::string("sz_z"), k);
  }
  return F[long(i) + long(j) * sz_x + long(k) * sz_x * sz_y];
}

// template <class T>
// T &MkArray<T>::operator()(int i, int j)
// {
//   if (FDimension <= 0)
//   {
//     MkDebug("Possibly Memory dosen't allocated!\n");
//     throw Alloc(std::string("MkArray<T>"));
//   }

//   if (i < 0 || sz_x <= i)
//   {
//     MkDebug("MkArray index out of range\n");
//     throw Range("sz_x", i);
//   }
//   if (j < 0 || sz_y <= j)
//   {
//     MkDebug("MkArray index out of range\n");
//     throw Range(std::string("sz_y"), j);
//   }
//   return F[long(i) + long(j) * sz_x];
// }

template <class T>
T &MkArray<T>::operator()(int &i, int &j)
{
  if (FDimension <= 0)
  {
    MkDebug("Possibly Memory dosen't allocated!\n");
    throw Alloc(std::string("MkArray<T>"));
  }

  if (i < 0 || sz_x <= i)
  {
    MkDebug("MkArray index i (%d) out of range\n",i);
    throw Range("sz_x", i);
  }
  if (j < 0 || sz_y <= j)
  {
    MkDebug("MkArray index j (%d) out of range\n",j);
    throw Range(std::string("sz_y"), j);
  }
  return F[long(i) + long(j) * sz_x];
}

template <class T>
T &MkArray<T>::operator()(int &&i, int &&j)
{
  if (FDimension <= 0)
  {
    MkDebug("Possibly Memory dosen't allocated!\n");
    throw Alloc(std::string("MkArray<T>"));
  }

  if (i < 0 || sz_x <= i)
  {
    MkDebug("MkArray index i (%d) out of range\n",i);
    throw Range("sz_x", i);
  }
  if (j < 0 || sz_y <= j)
  {
    MkDebug("MkArray index j (%d) out of range\n",j);
    throw Range(std::string("sz_y"), j);
  }
  return F[long(i) + long(j) * sz_x];
}

template <class T>
T &MkArray<T>::operator()(int &i)
{
  if (FDimension <= 0)
  {
    MkDebug("Possibly Memory dosen't allocated!\n");
    throw Alloc(std::string("MkArray<T>"));
  }

  if (i < 0 || sz_x <= i)
  {
    MkDebug("MkArray index i (%d) out of range\n",i);
    throw Range(std::string("sz_x"), i);
  }
  return F[long(i)];
}

template <class T>
T &MkArray<T>::operator()(int &&i)
{
  if (FDimension <= 0)
  {
    MkDebug("Possibly Memory dosen't allocated!\n");
    throw Alloc(std::string("MkArray<T>"));
  }

  if (i < 0 || sz_x <= i)
  {
    MkDebug("MkArray index i (%d) out of range\n",i);
    throw Range(std::string("sz_x"), i);
  }
  return F[long(i)];
}

template <class T>
MkArray<T> &MkArray<T>::operator+=(MkArray<T> &a)
{
  if (a.sz_x != sz_x || a.sz_y != sz_y || a.sz_z != sz_z)
    return *this;

  for (int i = 0; i < sz_x; i++)
    for (int j = 0; j < sz_y; j++)
      for (int k = 0; k < sz_z; k++)
        (*this)(i, j, k) += a(i, j, k);

  return *this;
}

template <class T>
MkArray<T> &MkArray<T>::operator+=(T &a)
{

  for (int i = 0; i < sz_x; i++)
    for (int j = 0; j < sz_y; j++)
      for (int k = 0; k < sz_z; k++)
        (*this)(i, j, k) += a;

  return *this;
}

template <class T>
MkArray<T> &MkArray<T>::operator+=(T &&a)
{

  for (int i = 0; i < sz_x; i++)
    for (int j = 0; j < sz_y; j++)
      for (int k = 0; k < sz_z; k++)
        (*this)(i, j, k) += a;

  return *this;
}

template <class T>
MkArray<T> &MkArray<T>::operator-=(MkArray<T> &a)
{
  if (a.sz_x != sz_x || a.sz_y != sz_y || a.sz_z != sz_z)
    return *this;

  for (int i = 0; i < sz_x; i++)
    for (int j = 0; j < sz_y; j++)
      for (int k = 0; k < sz_z; k++)
        (*this)(i, j, k) -= a(i, j, k);

  return *this;
}

template <class T>
MkArray<T> &MkArray<T>::operator-=(T &a)
{
  for (int i = 0; i < sz_x; i++)
    for (int j = 0; j < sz_y; j++)
      for (int k = 0; k < sz_z; k++)
        (*this)(i, j, k) -= a;

  return *this;
}

template <class T>
MkArray<T> &MkArray<T>::operator-=(T &&a)
{
  for (int i = 0; i < sz_x; i++)
    for (int j = 0; j < sz_y; j++)
      for (int k = 0; k < sz_z; k++)
        (*this)(i, j, k) -= a;

  return *this;
}

template <class T>
MkArray<T> &MkArray<T>::operator*=(T b)
{
  for (int i = 0; i < sz_x; i++)
    for (int j = 0; j < sz_y; j++)
      for (int k = 0; k < sz_z; k++)
        (*this)(i, j, k) *= b;

  return *this;
}

template <class T>
MkArray<T> &MkArray<T>::operator/=(T b)
{
  if (b < FTOL && b > -FTOL)
    return *this;
  for (int i = 0; i < sz_x; i++)
    for (int j = 0; j < sz_y; j++)
      for (int k = 0; k < sz_z; k++)
        (*this)(i, j, k) /= b;

  return *this;
}

template <class T>
bool MkArray<T>::operator==(MkArray<T> &a)
{
  bool flag = true;
  int i, j, k;
  flag = flag && (FDimension == a.FDimension);
  flag = flag && (sz_x == a.sz_x);
  flag = flag && (sz_y == a.sz_y);
  flag = flag && (sz_z == a.sz_z);
  if (!flag)
  {
    return flag;
  }
  for (i = 0; i < sz_x; i++)
  {
    for (j = 0; j < sz_y; j++)
    {
      for (k = 0; k < sz_z; k++)
      {
        flag = flag && (fabs((*this)(i, j, k) - a(i, j, k)) < EPS);
      }
    }
  }
  return flag;
}

template <class T>
bool MkArray<T>::operator!=(MkArray<T> &a)
{
  return !(*this == a);
}

// template <class T>
// MkArray<T> &operator+(MkArray<T> &a, MkArray<T> &b)
// {
//   static MkArray<T> c;
//   c.Clear();
//   if (a.sz_x != b.sz_x || a.sz_y != b.sz_y || a.sz_z != b.sz_z)
//     return c;

//   c.Initialize(a.sz_x, a.sz_y, a.sz_z);

//   for (int i = 0; i < a.sz_x; i++)
//     for (int j = 0; j < a.sz_y; j++)
//       for (int k = 0; k < a.sz_z; k++)
//         c(i, j, k) = a(i, j, k) + b(i, j, k);

//   return c;
// }

// template <class T>
// MkArray<T> &operator-(MkArray<T> &a, MkArray<T> &b)
// {
//   static MkArray<T> c;
//   c.Clear();
//   if (a.sz_x != b.sz_x || a.sz_y != b.sz_y || a.sz_z != b.sz_z)
//     return c;

//   c.Initialize(a.sz_x, a.sz_y, a.sz_z);

//   for (int i = 0; i < a.sz_x; i++)
//     for (int j = 0; j < a.sz_y; j++)
//       for (int k = 0; k < a.sz_z; k++)
//         c(i, j, k) = a(i, j, k) - b(i, j, k);

//   return c;
// }

// template <class T>
// MkArray<T> &operator*(MkArray<T> &a, T b)
// {
//   static MkArray<T> c;
//   c.Initialize(a.sz_x, a.sz_y, a.sz_z);
//   for (int i = 0; i < a.sz_x; i++)
//     for (int j = 0; j < a.sz_y; j++)
//       for (int k = 0; k < a.sz_z; k++)
//         c(i, j, k) = a(i, j, k) * b;

//   return c;
// }

// template <class T>
// MkArray<T> &operator/(MkArray<T> &a, T b)
// {
//   static MkArray<T> c;
//   if (b < FTOL && b > -FTOL)
//     return a;
//   c.Initialize(a.sz_x, a.sz_y, a.sz_z);
//   for (int i = 0; i < a.sz_x; i++)
//     for (int j = 0; j < a.sz_y; j++)
//       for (int k = 0; k < a.sz_z; k++)
//         c(i, j, k) = a(i, j, k) / b;

//   return c;
// }
//---------------------------------------------------------------------------

template class MkArray<int>;
template class MkArray<float>;
template class MkArray<double>;
