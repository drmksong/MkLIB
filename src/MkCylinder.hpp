//---------------------------------------------------------------------------
#ifndef MkCylinderH
#define MkCylinderH

#include <math.h>
#include "MkShape.hpp"
#include "MkLine.hpp"
#include "MkPoint.hpp"
#include "MkTriangle.hpp"
#include "MkPlane.hpp"
//---------------------------------------------------------------------------
class MkPlane;
class MkJointPlane;
class MkPennyJoint;

class MkCylinder : public MkShape
{
private:
  // MkTriangles Surf;
  int SurfDivision;
  bool needUpdate;
  bool UpdateSurf();

protected:
  MkPoint FCP;
  double FRadius;
  double FLength;
  double Fl, Fm, Fn;
  double Psi, Theta; // Psi rotate in y-axis, Beta rotate in z-axis
  MkPoints FPoints;

public:
  MkCylinder();
  MkCylinder(double cx, double cy, double cz, double radius);
  MkCylinder(MkPoint &cp, double radius);
  MkCylinder(MkPoint &&cp, double radius);

  std::string ClassName()
  {
    return std::string("MkCylinder");
  }

  void SetCylinder(double cx, double cy, double cz, double radius);
  void SetCylinder(MkPoint &cp, double radius);
  void SetCylinder(MkPoint &&cp, double radius);

  void SetOrient(MkPoint &orient);
  void SetOrient(MkPoint &&orient);
  void SetOrient(double l, double m, double n);

  void SetLength(double len) { FLength = len; }

  void SetCenter(double cx, double cy, double cz);
  void SetCenter(MkPoint &cp);
  void SetCenter(MkPoint &&cp);
  void SetRadius(double radius);

  void SetDivision(int n) { SurfDivision = n; }

  bool IsInSurface(MkPoint &pnt, double thick);
  bool IsInSurface(MkPoint &&pnt, double thick);

  bool IsInSpace(MkPoint &pnt);
  bool IsInSpace(MkPoint &&pnt);
  bool IsIntersect(MkLine &rl);
  bool IsIntersect(MkLine &&rl);

  bool isCylinder() { return true; }

  MkPoints &CalcIntPnts(MkLine &rl);
  MkPoints &CalcIntPnts(MkLine &&rl);

  void GetIntParam(MkLine &rl, double &t1, double &t2);
  void GetIntParam(MkLine &&rl, double &t1, double &t2);

  MkPoint& GetCenter();
  double GetRadius();
  double GetDist(MkPoint &pnt);
  double GetDist(MkPoint &&pnt);
  MkPoint &operator[](int);

  MkCylinder &operator=(MkCylinder &rs);
  MkCylinder &operator=(MkCylinder &&rs);
  bool operator&&(MkLine &rl);
  bool operator&&(MkLine &&rl);
  MkPoints &operator&(MkLine &rl);
  MkPoints &operator&(MkLine &&rl);
  bool operator==(MkCylinder &rs);
  bool operator==(MkCylinder &&rs);
  bool operator!=(MkCylinder &rs);
  bool operator!=(MkCylinder &&rs);

  void RotateSpace(MkPoint &rp);
  void RotateSpace(MkPoint &&rp);
  void RotateSpace(MkLine &rl);
  void RotateSpace(MkLine &&rl);
  void RotateSpace(MkPlane &rp);
  void RotateSpace(MkPlane &&rp);
  void RotateSpace(MkJointPlane &jp);
  void RotateSpace(MkJointPlane &&jp);
  void RotateSpace(MkPennyJoint &pj);
  void RotateSpace(MkPennyJoint &&pj);

  void UnRotateSpace(MkPoint &rp);
  void UnRotateSpace(MkPoint &&rp);
  void UnRotateSpace(MkLine &rl);
  void UnRotateSpace(MkLine &&rl);
  void UnRotateSpace(MkPlane &rp);
  void UnRotateSpace(MkPlane &&rp);
  void UnRotateSpace(MkJointPlane &jp);
  void UnRotateSpace(MkJointPlane &&jp);
  void UnRotateSpace(MkPennyJoint &pj);
  void UnRotateSpace(MkPennyJoint &&pj);

#ifdef __BCPLUSPLUS__
  void Draw(TObject *);
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
  void Draw(MkPaint *);
#endif
};

class MkCylinders : public MkShape
{
protected:
  MkCylinder *FCylinder;
  int FSize;

public:
  MkCylinders(int Size);
  MkCylinders()
  {
    FSize = 0;
    FCylinder = NULL;
  }
  ~MkCylinders()
  {
    if (FCylinder)
    {
      delete (MkCylinder *)FCylinder;
      FCylinder = NULL;
    }
  }
  void Initialize(int Size);
  void Clear();
  int GetSize() { return FSize; }
  virtual MkCylinder &operator[](int);
  MkCylinders &operator=(MkCylinders &cylinders);

#ifdef __BCPLUSPLUS__
  void Draw(TObject *);
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
  void Draw(MkPaint *);
#endif
};
//---------------------------------------------------------------------------
#endif
