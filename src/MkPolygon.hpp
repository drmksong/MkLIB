//---------------------------------------------------------------------------
#ifndef MkPolygonH
#define MkPolygonH

#include <cassert>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "MkArray.hpp"
#include "MkCircle.hpp"
#include "MkLine.hpp"
#include "MkPoint.hpp"
#include "MkTriangle.hpp"

#ifdef __BCPLUSPLUS__
#include "MkPaintBox.h"
#endif

// How can I distingush between NullPoint and Origin Point.
// if two connected point are the same and is NullPoint then
// isFilled returns false.

enum MkBoolType
{
  btUni,
  btInt,
  btSub
}; // union, intersection, subtraction
enum MkPolygonSort
{
  psXA,
  psXD,
  psYA,
  psYD,
  psZA,
  psZD
};
enum MkCrossOption
{
  coMax,
  coAbsMax,
  coMin,
  coAbsMin
};

class MkPolygons;
class MkPolygon : public MkShape, public MkPoints
{
protected:
  bool Closeness; // is this polygon closed(true) or opened(false);
  bool Convexity;
  bool Crossing; // if lines are crossed(true) each other or not(false)?
  bool Fullness;
  bool isLengthChanged;    // if it is altered by any change of the points or configuration of points? 23.01.26
  bool isAreaChanged;      //  same as above
  bool isCrossingChanged;  // same as above
  bool isClosenessChanged; // same as above
  bool isConvexityChanged; // same as above
  bool doDrawPoint;
  bool doFill;
  bool isFormed; // if lines are refreshed after it is altered? 23.01.26

  MkCrossOption CrossOption;

  double FLength;
  double FArea;
  MkInt PointState;
  int FCurrent;
  MkLines FLines; // newly adopted in 23.01.25 for resolving copying by reference issues

  void CheckConvexity();
  void CheckCrossing();
  void CheckFullness();
  double CalLength();
  bool FormPolyLines(); // // newly adopted in 23.01.25 for resolving copying by reference issues , implementation on going 23.01.26
public:
  void ini_bools()
  {
    Closeness = false; // is this polygon closed(true) or opened(false);
    Convexity = false;
    Crossing = false; // if lines are crossed(true) each other or not(false)?
    Fullness = false;
    isLengthChanged = true;    // if it is altered by any change of the points or configuration of points? 23.01.26
    isAreaChanged = true;      //  same as above
    isCrossingChanged = true;  // same as above
    isClosenessChanged = true; // same as above
    isConvexityChanged = true; // same as above
    doDrawPoint = false;
    doFill = false;
    isFormed = false; // if lines are refreshed after it is altered? 23.01.26
  }

public:
  MkPolygon(int size, boost::shared_ptr< MkPoint[]>);
  MkPolygon(int size); // empty polygon
  MkPolygon();         // even memory is not allocated
  ~MkPolygon();
  void Initialize(int size);
  void Initialize(int size, boost::shared_ptr< MkPoint[]>);
  bool Clear()
  {
    isLengthChanged = true;
    isAreaChanged = true;
    CrossOption = coAbsMax;
    return MkPoints::Clear();
  }

  bool Add(MkPoint &p)
  {
    isLengthChanged = true;
    isAreaChanged = true;
    return MkPoints::Add(p);
  }

  bool Add(MkPoint &&p)
  {
    isLengthChanged = true;
    isAreaChanged = true;
    return MkPoints::Add(p);
  }

  bool Add(int index, MkPoint &p)
  {
    isLengthChanged = true;
    isAreaChanged = true;
    return MkPoints::Add(index, p);
  }

  bool Add(int index, MkPoint &&p)
  {
    isLengthChanged = true;
    isAreaChanged = true;
    return MkPoints::Add(index, p);
  }

  bool Add(MkPoints &p)
  {
    isLengthChanged = true;
    isAreaChanged = true;
    return MkPoints::Add(p);
  }

  bool Add(MkPoints &&p)
  {
    isLengthChanged = true;
    isAreaChanged = true;
    return MkPoints::Add(p);
  }

  bool AddInBetween(MkPoints &p);
  bool Delete(MkPoint &p)
  {
    isLengthChanged = true;
    isAreaChanged = true;
    return MkPoints::Delete(p);
  }
  bool Delete(int index)
  {
    isLengthChanged = true;
    isAreaChanged = true;
    return MkPoints::Delete(index);
  }

  void SetCloseness(bool b) { Closeness = b; };
  void SetCrossOption(MkCrossOption co) { CrossOption = co; }

  bool GetCloseness() { return Closeness; }
  MkCrossOption GetCrossOption() { return CrossOption; }
  double GetLength();
  double GetArea();
  int GetAlivePoint();

  bool isClosed() { return Closeness; }
  bool isFilled() { return Fullness; }; // all the data is not NullPoint?
  bool isCrossing() { return Crossing; };
  bool isCrossWith(MkLine &l);
  bool isCrossWithX(double x);
  bool isCrossWithY(double y);
  bool IsIn(MkPoint &rp);
  bool IsIn(MkPoint &&rp);
  bool IsIn(MkCircle &rc);
  bool IsIn(MkCircle &&rc);

  void getCrossWith(MkLine &l, MkPoints &pnts);
  void getCrossWith(MkLine &&l, MkPoints &pnts);
  void getCrossWithX(double x, MkPoints &pnts);
  void getCrossWithY(double y, MkPoints &pnts);
  void getCrossWithZ(double z, MkPoints &pnts);
  double getXWithY(double y);
  double getXWithZ(double y);
  double getYWithX(double x);
  double getYWithZ(double x);
  double getZWithX(double x);
  double getZWithY(double y);

  int Current() { return FCurrent; };
  void SetCurrent(int i)
  {
    if (i >= 0 && i < GetSize())
      FCurrent = i;
  };
  int Next();
  int Prev();
  int Next(int);
  int Prev(int);
  int AlivedNext();
  int AlivedPrev();
  int AlivedNext(int);
  int AlivedPrev(int);
  MkPoint &CurrentPoint() { return (*this)[FCurrent]; };
  MkPoint &NextPoint();
  MkPoint &PrevPoint();
  MkPoint &NextPoint(int);
  MkPoint &PrevPoint(int);
  MkPoint &NextPoint(MkPoint &pnt);
  MkPoint &PrevPoint(MkPoint &pnt);
  MkPoint &AlivedNextPoint();
  MkPoint &AlivedPrevPoint();
  MkPoint &AlivedNextPoint(int);
  MkPoint &AlivedPrevPoint(int);

  void Offset(MkPolygon &poly, bool dir, double space);
  void Offset(MkPolygon &poly, MkVector<double> &up, bool dir, double space);
  MkPoint &Measure(double dis);  // return point where the distance is dis within polygon???
  double Measure(MkPoint &pnt);  // 0 ~ 1
  double Measure(MkPoint &&pnt); // 0 ~ 1
  bool InverseDirection();
  bool Merge(MkPolygon &poly);
  bool FindInter(MkPolygon &poly, MkPoints &pnts);
  MkVector<double> &GetVector();

  int FindPoly(MkPolygon &b, MkBoolType bt);
  bool BoolSub(MkPolygon &b, MkPolygons &c); // C = A - B subtraction
  bool BoolInt(MkPolygon &b, MkPolygons &c); // C = A * B intersection
  bool BoolUni(MkPolygon &b, MkPolygons &c); // C = A + B union
  void Extract(MkPoints &b, MkPolygon &c);

  void Sort(MkPolygonSort ps);

  MkPoint &operator[](int i);
  MkLine &operator()(int i);
  MkPolygon &operator=(MkPolygon &polygon);
  bool operator==(MkPolygon &poly);
  bool operator!=(MkPolygon &poly);
  bool operator==(MkPolygon &&poly);
  bool operator!=(MkPolygon &&poly);
  
  double CalArea(); // TODO: figure out what is the difference
  double CalArea2();

  void SetDrawPoint(bool flag) { doDrawPoint = flag; }
  bool GetDrawPoint() { return doDrawPoint; }
  void SetDrawFill(bool flag) { doFill = flag; }
  bool GetDrawFill() { return doFill; }

  bool Out(char *fname);

  std::string ClassName() { return std::string("MkPolygon"); }
#ifdef __BCPLUSPLUS__
  void Draw(TObject *);
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
  void Draw(MkPaint *);
#endif
};

class MkPolygons : public MkShape, public MkAbstract
{
protected:
  boost::shared_ptr<MkPolygon []>FPolygon;
  int FSize; // Actual size of polys
  int FCapacity;
#ifdef __BCPLUSPLUS__
  TColor Color;
#endif

public:
  MkPolygons()
  {
    FCapacity = FSize = 0;
    FPolygon = NULL;
  }
  MkPolygons(int size);
  MkPolygons(int size, boost::shared_ptr<MkPolygon []>poly);
  MkPolygons(MkPolygons &poly);
  ~MkPolygons();
  virtual void Initialize(int size);
  virtual void Initialize(int size, MkPolygon *);
  int GetSize() { return FSize; };
  int GetNumber() { return FSize; };
  bool Add(MkPolygon &poly); // change of size of poly
  bool Add(MkPolygons &poly)
  {
    bool flag = true;
    MkDebug("MkPolygons::Add(Polygons) is called.\n");
    for (int i = 0; i < poly.GetSize(); i++)
      flag = Add(poly[i]) && flag;
    return flag;
  } // change of size of poly
  bool Add(int index, MkPolygon &poly);
  bool Delete(MkPolygon &poly); // change of size of poly
  bool Delete(int index);
  int Grow(int Delta);   // change of size of array
  int Shrink(int Delta); // change of size of array
  bool Clear();
#ifdef __BCPLUSPLUS__
  TColor GetColor()
  {
    return Color;
  };
  void SetColor(TColor c) { Color = c; }

#endif
  virtual MkPolygon &operator[](int);
  MkPolygons &operator=(MkPolygons &polys);
  bool operator==(MkPolygons &polys);
  bool operator==(MkPolygons &&polys);

  std::string ClassName() { return std::string("MkPolygons"); };

#ifdef __BCPLUSPLUS__
  void Draw(TObject *);
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
  void Draw(MkPaint *);
#endif

};

void GetSubPolygon(double ymin, double ymax, MkPolygon &inpoly, MkPolygon &outpoly);
void GetSubParam(int i, MkPolygon &in, double &aj, double &bj, double &lj1, double &lj);
//---------------------------------------------------------------------------
extern MkPolygon NullPolygon;
#endif
