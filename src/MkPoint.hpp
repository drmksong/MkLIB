//---------------------------------------------------------------------------
#ifndef MkPointHPP
#define MkPointHPP
#include <math.h>
#include <vector>
#include <exception>
#include <iostream>
#include <boost/shared_array.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include "MkColor.hpp"

#include "MkMisc.hpp"
#include "MkMatrix.hpp"

struct MkPoint;
class MkPoints;
extern MkPoint NullPoint;
extern MkPoints NullPoints;

struct MkPoint
{
public:
  double X, Y, Z;

#if defined(__GL_H__)
  MkColor Color;
  double DotRadius;
#endif

  MkPoint()
  {
    X = 0;
    Y = 0;
    Z = 0;
  }

  MkPoint(double x, double y)
  {
    X = x;
    Y = y;
    Z = 0;
  }

  MkPoint(double x, double y, double z)
  {
    X = x;
    Y = y;
    Z = z;
  }

  void SetPoint(double x, double y)
  {
    X = x;
    Y = y;
  }

  void SetPoint(double x, double y, double z)
  {
    X = x;
    Y = y;
    Z = z;
  }

  void Set(double x, double y, double z)
  {
    X = x;
    Y = y;
    Z = z;
  }

  void Set(const MkPoint &rp)
  {
    X = rp.X;
    Y = rp.Y;
    Z = rp.Z;
  }

  void Set(MkPoint &&rp)
  {
    X = rp.X;
    Y = rp.Y;
    Z = rp.Z;
  }

#if defined(__GL_H__)
  void SetColor(MkColor c)
  {
    Color = c;
  }

  void SetDotRadius(double r) { DotRadius = r; }
  MkColor GetColor() { return Color; }
  double GetDotRadius() { return DotRadius; }
#endif

  MkPoint &operator=(const MkPoint &rp);
  MkPoint &operator=(MkPoint &&rp);

  MkPoint &operator+=(const MkPoint &rp)
  {
    X += rp.X;
    Y += rp.Y;
    Z += rp.Z;
    return *this;
  }

  MkPoint &operator+=(MkPoint &&rp)
  {
    X += rp.X;
    Y += rp.Y;
    Z += rp.Z;
    return *this;
  }

  friend MkPoint &operator+(const MkPoint &a, const MkPoint &b)
  {
    static MkPoint c;
    c.X = a.X + b.X;
    c.Y = a.Y + b.Y;
    c.Z = a.Z + b.Z;
    return c;
  }

  friend MkPoint &operator+(MkPoint &&a, MkPoint &&b)
  {
    static MkPoint c;
    c.X = a.X + b.X;
    c.Y = a.Y + b.Y;
    c.Z = a.Z + b.Z;
    return c;
  }

  MkPoint &operator-=(const MkPoint &rp)
  {
    X -= rp.X;
    Y -= rp.Y;
    Z -= rp.Z;
    return *this;
  }

  MkPoint &operator-=(MkPoint &&rp)
  {
    X -= rp.X;
    Y -= rp.Y;
    Z -= rp.Z;
    return *this;
  }

  friend MkPoint &operator-(const MkPoint &a, const MkPoint &b)
  {
    static MkPoint c;
    c.X = a.X - b.X;
    c.Y = a.Y - b.Y;
    c.Z = a.Z - b.Z;
    return c;
  }

  friend MkPoint &operator-(MkPoint &&a, MkPoint &&b)
  {
    static MkPoint c;
    c.X = a.X - b.X;
    c.Y = a.Y - b.Y;
    c.Z = a.Z - b.Z;
    return c;
  }

  friend double CalDist(const MkPoint &sp, const MkPoint &ep)
  {
    return sqrt(pow(sp.X - ep.X, 2) + pow(sp.Y - ep.Y, 2) + pow(sp.Z - ep.Z, 2));
  }

  friend double CalDist(MkPoint &&sp, MkPoint &&ep)
  {
    return sqrt(pow(sp.X - ep.X, 2) + pow(sp.Y - ep.Y, 2) + pow(sp.Z - ep.Z, 2));
  }

  double GetAng();
  void GetAng(double &alpha, double &beta, double &gamma);

  bool operator==(const MkPoint &rp);
  bool operator==(MkPoint &&rp);
  // bool operator==(const MkPoint &rp) const;
  // bool operator==(MkPoint &&rp) const;

  bool operator!=(const MkPoint &rp);
  bool operator!=(MkPoint &&rp);

  friend MkPoint &operator*(const MkPoint &rp, MkMatrix4<double> &rm)
  {
    static MkPoint rp_t;
    rp_t = rp;

    rp_t.X = rp.X * rm(0, 0) + rp.Y * rm(0, 1) + rp.Z * rm(0, 2) + 1 * rm(0, 3);
    rp_t.Y = rp.X * rm(1, 0) + rp.Y * rm(1, 1) + rp.Z * rm(1, 2) + 1 * rm(1, 3);
    rp_t.Z = rp.X * rm(2, 0) + rp.Y * rm(2, 1) + rp.Z * rm(2, 2) + 1 * rm(2, 3);

    return rp_t;
  }

  friend MkPoint &operator*(MkPoint &&rp, MkMatrix4<double> &rm)
  {
    static MkPoint rp_t;
    rp_t = rp;

    rp_t.X = rp.X * rm(0, 0) + rp.Y * rm(0, 1) + rp.Z * rm(0, 2) + 1 * rm(0, 3);
    rp_t.Y = rp.X * rm(1, 0) + rp.Y * rm(1, 1) + rp.Z * rm(1, 2) + 1 * rm(1, 3);
    rp_t.Z = rp.X * rm(2, 0) + rp.Y * rm(2, 1) + rp.Z * rm(2, 2) + 1 * rm(2, 3);

    return rp_t;
  }

  friend MkPoint &operator*(const MkPoint &rp, double f)
  {
    static MkPoint rp_t;
    rp_t = rp;

    rp_t.X *= f;
    rp_t.Y *= f;
    rp_t.Z *= f;
    return rp_t;
  }

  friend MkPoint &operator*(MkPoint &&rp, double f)
  {
    static MkPoint rp_t;
    rp_t = rp;

    rp_t.X *= f;
    rp_t.Y *= f;
    rp_t.Z *= f;
    return rp_t;
  }

  MkPoint &operator*=(MkMatrix4<double> &rm);

  MkPoint &operator*=(double f);
  MkPoint &operator/(double f)
  {
    static MkPoint p;
    static MkPoint NullPoint;
    p = *this;
    if (fabs(f) < EPS)
    {
      MkDebug("MkPoint::operator/(double) Try to divide with too small double\n");
      return NullPoint;
    }
    p.X = p.X / f;
    p.Y = p.Y / f;
    p.Z = p.Z / f;
    return p;
  }

  MkPoint &operator/(int i)
  {
    static MkPoint p;

    p = *this;
    if (i == 0)
    {
      MkDebug("MkPoint::operator/(int) Try to divide with zero\n");
      return NullPoint;
    }
    p.X = p.X / i;
    p.Y = p.Y / i;
    p.Z = p.Z / i;
    return p;
  }

  void Unify();
  void Normalize();
  MkPoint &Translate(const MkPoint &rp);
  MkPoint &Translate(MkPoint &&rp);

  MkPoint &Translate(double x, double y, double z);
  MkPoint &Rotate(double alpha, double beta, double gamma);
  MkPoint &RotateInX(double ang);
  MkPoint &RotateInY(double ang);
  MkPoint &RotateInZ(double ang);
  MkPoint &RotateInA(double ang, double l, double m, double n);
  MkPoint &Scale(double sx, double sy, double sz);

  bool IsNear(const MkPoint &rp) { return CalDist(*this, rp) < 0.001; }
  bool IsNear(MkPoint &&rp) { return CalDist(*this, rp) < 0.001; }
  bool IsNear(double x, double y)
  {
    static MkPoint rp;
    rp.SetPoint(x, y);
    return CalDist(*this, rp) < 0.001;
  }

#if defined(__GL_H__)
  void Draw();
#endif
};

std::ostream &operator<<(std::ostream &outputStream, const MkPoint &);
std::ostream &operator<<(std::ostream &outputStream, MkPoint &&);
void Swap(MkPoint &p1, MkPoint &p2);

class MkPoints
{
protected:
  boost::shared_ptr<MkPoint[]> FPoint;
  MkPoint FCenter;
  int FSize;     // Actual size of points
  int FCapacity; // Reserved size which is always equal or larger than FSize
  void FindCenter();

  // TODO: Color of the points should be replaced by the color of each point, 23.01.28
  // #if defined(__GL_H__)
  //   MkColor Color;
  //   double DotRadius;
  // #endif

public:
  MkPoints(std::vector<MkPoint> &p); // use this constructor instead
  MkPoints(int size, MkPoint *rps);  // TODO: do not use this constructor as much as you can...
  MkPoints(int size);
  MkPoints()
  {
    FCapacity = FSize = 0;
    FPoint.reset();
  }
  ~MkPoints();
  void Initialize(std::vector<MkPoint> &p); // use this
  void Initialize(int size, MkPoint *rps);  // do not use this
  void Initialize(int size);
  int GetSize() { return FSize; };
  int GetSize() const { return FSize; };
  int GetNumber() { return FSize; };
  int GetCapacity() { return FCapacity; }
  MkPoint *GetPoints() { return FPoint.get(); }
  MkPoint &GetCenter()
  {
    FindCenter();
    return FCenter;
  };
  bool Add(const MkPoint &point); // change of size of point
  bool Add(MkPoint &&point);      // change of size of point

  bool Add(int index, const MkPoint &point); // TODO: should avoid its usage as much as possible
  bool Add(int index, MkPoint &&point);      // TODO: should avoid its usage as much as possible

  bool Add(const MkPoints &p)
  {
    for (int i = 0; i < p.GetSize(); i++)
      Add(p[i]);
    return true;
  }

  bool Add(MkPoints &&p)
  {
    for (int i = 0; i < p.GetSize(); i++)
      Add(p[i]);
    return true;
  }
  bool Delete(const MkPoint &point); // TODO: should avoid its usage as much as possible
  bool Delete(MkPoint &&point);      // TODO: should avoid its usage as much as possible
  bool Delete(int index);            // use this instead
  bool Delete();                     // Delete the last point, 23.01.28
  int Reserve(int Delta);
  int Grow(int Delta);   // change of size of array
  int Shrink(int Delta); // change of size of array
  bool Swap(int i, int j);
  bool Clear();

  // TODO: Color of the points should be replaced by the color of each point, 23.01.28
  // #if defined(__GL_H__)
  //   void SetColor(MkColor c)
  //   {
  //     Color = c;
  //   }
  //   void SetDotRadius(double r) { DotRadius = r; }
  //   MkColor GetColor() { return Color; }
  //   double GetDotRadius() { return DotRadius; }
  // #endif

  bool hasPoint(const MkPoint &pnt)
  {
    for (int i = 0; i < FSize; i++)
      if (FPoint[i] == pnt)
        return true;
    return false;
  }

  bool hasPoint(MkPoint &&pnt)
  {
    for (int i = 0; i < FSize; i++)
      if (FPoint[i] == pnt)
        return true;
    return false;
  }

  int numPoint(const MkPoint &pnt)
  {
    for (int i = 0; i < FSize; i++)
      if (FPoint[i] == pnt)
        return i;
    return -1;
  }

  int numPoint(MkPoint &&pnt)
  {
    for (int i = 0; i < FSize; i++)
      if (FPoint[i] == pnt)
        return i;
    return -1;
  }

  MkPoint &operator[](int);
  MkPoint &operator[](int) const;
  MkPoints &operator*=(MkMatrix4<double> &rm);
  friend MkPoints &operator*(const MkPoints &rps, MkMatrix4<double> &rm)
  {
    static MkPoints rps_t;
    rps_t = rps;
    for (int i = 0; i < rps.FSize; i++)
      rps_t.FPoint[i] = rps.FPoint[i] * rm;
    return rps_t;
  }

  friend MkPoints &operator*(MkPoints &&rps, MkMatrix4<double> &rm)
  {
    static MkPoints rps_t;
    rps_t = rps;
    for (int i = 0; i < rps.FSize; i++)
      rps_t.FPoint[i] = rps.FPoint[i] * rm;
    return rps_t;
  }

  MkPoints &Translate(const MkPoint &rp);
  MkPoints &Translate(MkPoint &&rp);
  MkPoints &Translate(double x, double y, double z);
  MkPoints &Rotate(double alpha, double beta, double gamma);
  MkPoints &RotateInX(double ang);
  MkPoints &RotateInY(double ang);
  MkPoints &RotateInZ(double ang);
  MkPoints &RotateInA(double ang, double l, double m, double n);
  MkPoints &Scale(double sx, double sy, double sz);

  MkPoints &operator=(const MkPoints &points);
  MkPoints &operator=(MkPoints &&points);

  bool operator==(const MkPoints &points);
  bool operator==(MkPoints &&points);

  bool operator!=(const MkPoints &points);
  bool operator!=(MkPoints &&points);

#if defined(__GL_H__)
  void Draw(); // TODO: implement it
#endif

  class Alloc
  {
  public:
    std::string What;
    Alloc(std::string what) : What(what) {}
    std::string what() { return What; }
  };
  class Size
  {
  public:
    std::string What;
    int N;
    Size(std::string what, int n) : What(what), N(n) {}
    std::string what() { return What; }
  };
  class Range
  {
  public:
    std::string What;
    int N;
    Range(std::string what, int n) : What(what), N(n) {}
    std::string what() { return What; }
  };
};

//---------------------------------------------------------------------------
#endif
