//---------------------------------------------------------------------------
#ifndef MkSphereH
#define MkSphereH
#include <math.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "MkShape.hpp"
#include "MkPoint.hpp"
#include "MkLine.hpp"
#include "MkTriangle.hpp"

//---------------------------------------------------------------------------
#ifdef __BCPLUSPLUS__
#endif
//---------------------------------------------------------------------------
class MkSphere : public MkShape
{
private:
  MkTriangles Surf;
  int SurfDivision;
  bool needUpdate;
  bool UpdateSurf();

protected:
  MkPoint FCP;
  double FRadius;
  double FSphereVolume;
  MkPoints FRealPoints;
  virtual void CalcVolume();

public:
  MkSphere();
  MkSphere(double cx, double cy, double cz, double radius);
  MkSphere(MkPoint &cp, double radius);
  MkSphere(MkPoint &&cp, double radius);

  std::string ClassName()
  {
    return std::string("MkSphere");
  }

  void SetSphere(double cx, double cy, double cz, double radius);
  void SetSphere(MkPoint &cp, double radius);
  void SetSphere(MkPoint &&cp, double radius);
#ifdef __BCPLUSPLUS__
  void SetSphere(double cx, double cy, double cz, double radius, TColor C);
  void SetSphere(MkPoint cp, double radius, TColor C);
  void SetSurfDivision(int n) { SurfDivision = n; }
#endif
  virtual void SetCenter(double cx, double cy, double cz);
  virtual void SetCenter(MkPoint &cp);
  virtual void SetCenter(MkPoint &&cp);
  virtual void SetRadius(double radius);


  bool IsInSurface(MkPoint &pnt, double thick);
  bool IsInSurface(MkPoint &&pnt, double thick);
  bool IsInSpace(MkPoint &pnt);
  bool IsInSpace(MkPoint &&pnt);
  bool IsIntersect(MkLine &rl);
  bool IsIntersect(MkLine &&rl);
  bool isSphere() { return true; }

  MkPoints &CalcIntPnts(MkLine &rl);
  MkPoints &CalcIntPnts(MkLine &&rl);
  void GetIntParam(MkLine &rl, double &t1, double &t2);
  void GetIntParam(MkLine &&rl, double &t1, double &t2);

  MkPoint GetCenter();
  double GetRadius();
  double GetVolume();
  MkPoint &operator[](int);
  bool operator==(MkSphere &rs);
  bool operator==(MkSphere &&rs);
  bool operator!=(MkSphere &rs);
  bool operator!=(MkSphere &&rs);
  MkSphere &operator=(MkSphere &rs);
  MkSphere &operator=(MkSphere &&rs);
  bool operator&&(MkLine &rl);
  bool operator&&(MkLine &&rl);
  MkPoints operator&(MkLine &rl);
  MkPoints operator&(MkLine &&rl);

#ifdef __BCPLUSPLUS__
  void Draw(TObject *);
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
  void Draw(MkPaint *);
#endif
};

class MkSpheres
{
protected:
  boost::shared_ptr<MkSphere[]> FSphere;
  int FSize;

public:
  
  MkSpheres()
  {
    FSize = 0;
    FSphere.reset();
  }

  MkSpheres(int Size);
  MkSpheres(int size, boost::shared_ptr<MkSphere[]> spheres);
  MkSpheres(MkSpheres &spheres);

  ~MkSpheres()
  {
    FSize = 0;
    FSphere.reset();
  }
  bool Initialize(int Size);
  bool Initialize(int size, boost::shared_ptr<MkSphere[]> spheres);
  bool Initialize(MkSpheres &spheres);
  
  void Clear();
  int GetSize() { return FSize; }
  virtual MkSphere &operator[](int);
  MkSpheres &operator=(MkSpheres &spheres);

#ifdef __BCPLUSPLUS__
  void Draw(TObject *);
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
  void Draw(MkPaint *);
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

#endif
