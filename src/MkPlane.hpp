//---------------------------------------------------------------------------
#ifndef MkPlaneH
#define MkPlaneH

#include <algorithm>
#include <cassert>
#include "MkAbstract.hpp"
#include "MkShape.hpp"
#include "MkPoint.hpp"
#include "MkLine.hpp"
#include "MkMisc.hpp"
#include "MkTriangle.hpp"
#include "MkSphere.hpp"
#include "MkCylinder.hpp"
#include "MkPolygon.hpp"

enum THeightMode
{
  hmAbs,
  hmCut,
  hmPaste
};

class MkPointsPlane : public MkPoints
{
protected:
  MkOrient FOrient;
  THeightMode FHeightMode;
  double Alpha, Beta, Gamma; // X, Y, Z ����������� ȸ������(deg)
  double A, B, C, D;         // Ax + By + Cz = D
public:
  MkPointsPlane();
  MkPointsPlane(int size);
  MkPointsPlane(int size, boost::shared_ptr<MkPoint[]> rps);
  MkPointsPlane(int size, boost::shared_ptr<MkPoint[]> rps, MkOrient fo);
  void SetOrient(MkOrient fo);

  void SetHeightMode(THeightMode fhm) { FHeightMode = fhm; }
  THeightMode GetHeightMode() { return FHeightMode; }
  bool operator==(MkPointsPlane &mp);
  bool operator==(MkPointsPlane &&mp);
  bool operator!=(MkPointsPlane &mp);
  bool operator!=(MkPointsPlane &&mp);

  bool IsIn(MkPoint &rp);  // ���� x-y �����ǥ�� ������ �Ǵ��Ѵ�.
  bool IsIn(MkPoint &&rp); // ���� x-y �����ǥ�� ������ �Ǵ��Ѵ�.
  double CalcHeight(MkPoint &rp);
  double CalcHeight(MkPoint &&rp);

#ifdef __BCPLUSPLUS__
  void Draw(TObject *);
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
  void Draw(MkPaint *);
#endif
};
//---------------------------------------------------------------------------
#ifdef __BCPLUSPLUS__
#endif

class MkPointsPlanes : public MkShape, public MkAbstract
{
protected:
  boost::shared_ptr<MkPointsPlane[]> FPoints;
  // MkPointsPlane *FPoints;
  int FSize;
#ifdef __BCPLUSPLUS__
  TColor Color;
#endif

public:
  MkPointsPlanes()
  {
    FSize = 0;
    FPoints.reset();
  }
  MkPointsPlanes(int FSize);
  MkPointsPlanes(int size, boost::shared_ptr<MkPointsPlane[]>jp);
  MkPointsPlanes(const MkPointsPlanes &jp);
  ~MkPointsPlanes();
  virtual void Initialize(int size);
  virtual void Initialize(int size, boost::shared_ptr<MkPointsPlane[]>jp);
  int GetSize() { return FSize; };
  int GetNumber() { return FSize; };
  boost::shared_ptr<MkPointsPlane[]> GetPoints() { return FPoints; }
  bool Clear();

#ifdef __BCPLUSPLUS__
  TColor GetColor()
  {
    return Color;
  };
  void SetColor(TColor c) { Color = c; }
#endif

  virtual MkPointsPlane &operator[](int);

  MkPointsPlanes &operator=(MkPointsPlanes &);
  bool operator==(MkPointsPlanes &);

#ifdef __BCPLUSPLUS__
  void Draw(TObject *);
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
  void Draw(MkPaint *);
#endif

};

// plane primitive�� (-1,-1),(1,-1),(1,1),(-1,1)�� ������, ȸ��, �̵��� ������
// ���ؼ� ���ϴ� �簢���� ����� ����� �� �� �ִ�.
//---------------------------------------------------------------------------
class MkPlane : public MkShape
{
protected:
  MkPoint LD, RD, LU, RU;
  MkLine Edge[4];
  MkPoint FCenter;
  double ScaleX;
  double ScaleY;
  double Alpha, Beta, Gamma; // �� x,y,z �������� ȸ��, ������ x,y,z ��
  double A, B, C, D;         // Ax + By + Cz = D
  bool isFinite;

public:
  MkPlane(); // ������� ��ǥ
  MkPlane(int i);
  MkPlane(MkPoint &rp1, MkPoint &rp2, MkPoint &rp3);
  MkPlane(MkPoint &&rp1, MkPoint &&rp2, MkPoint &&rp3);
  MkPlane(MkPoint *rps);

#ifdef __BCPLUSPLUS__
  AnsiString ClassName()
  {
    return AnsiString("MkPlane");
  }
#else
  std::string ClassName()
  {
    return std::string("MkPlane");
  }
#endif

  void ResetAll();
  void ResetScale();
  void ResetRotate();
  void ResetTranslate();
  void SetPoints(MkPoint &rp1, MkPoint &rp2, MkPoint &rp3);
  void SetPoints(MkPoint &&rp1, MkPoint &&rp2, MkPoint &&rp3);
  void SetPoints(MkPoint *rps); // TODO: delete it or use vector instead
  void SetScale(double scalex, double scaley);
  void SetFiniteness(bool flag) { isFinite = flag; }
  void SetRotate(double Alpha, double Beta, double Gamma); // ������ �����ִ� ��...
  void SetTranslate(MkPoint &trans);
  void SetTranslate(MkPoint &&trans);
  void SetTranslate(double x, double y, double z);
  void SetCenter(MkPoint &center) { SetTranslate(center); }
  void SetCenter(MkPoint &&center) { SetTranslate(center); }
  void SetCenter(double x, double y, double z) { SetTranslate(x, y, z); }

  void Rotate(double alpha, double beta, double gamma); // ������ ���� ȸ��
  void RotateInX(double ang);
  void RotateInY(double ang);
  void RotateInZ(double ang);
  void RotateInA(double ang, double l, double m, double n);
  void RotateCen(double alpha, double beta, double gamma); // Trans�� ���� ȸ��
  void RotateInXCen(double ang);
  void RotateInYCen(double ang);
  void RotateInZCen(double ang);
  void RotateInACen(double ang, double l, double m, double n);

  void Translate(double x, double y, double z)
  {
    FCenter.X += x;
    FCenter.Y += y;
    FCenter.Z += z;
  }
  void Translate(MkPoint &rp) { FCenter = FCenter + rp; }
  void Translate(MkPoint &&rp) { FCenter = FCenter + rp; }

  double GetA(void) { return A; }
  double GetB(void) { return B; }
  double GetC(void) { return C; }
  double GetD(void) { return D; }

  bool GetIntParam(MkLine &rl, double &t1, double &t2);
  bool GetIntParam(MkLine &&rl, double &t1, double &t2);
  bool GetFiniteness() { return isFinite; }
  MkPoint &GetTrans() { return FCenter; }
  MkPoint &GetCenter() { return FCenter; }
  double GetDistance(MkPoint &pnt)
  {
    assert(A * A + B * B + C * C > 0.0001);
    return (A * pnt.X + B * pnt.Y + C * pnt.Z - D) / sqrt(A * A + B * B + C * C);
  }
  double GetDistance(MkPoint &&pnt)
  {
    assert(A * A + B * B + C * C > 0.0001);
    return (A * pnt.X + B * pnt.Y + C * pnt.Z - D) / sqrt(A * A + B * B + C * C);
  }

  void ApplyMatrix();

  MkPoint &LeftDown() { return LD; }
  MkPoint &RightDown() { return RD; }
  MkPoint &LeftUp() { return LU; }
  MkPoint &RightUp() { return RU; }

  void CalcABCD();
  bool IsIntersect(MkLine &);  // updated at 2001.8.25.
  bool IsIntersect(MkLine &&); // updated at 2001.8.25.
  bool IsIntersect(MkTriangle &rt);
  bool IsIntersect(MkTriangle &&rt);
  bool IsInPlane(MkLine &rl);
  bool IsInPlane(MkLine &&rl);
  bool IsIn(MkPoint &rp);
  bool IsIn(MkPoint &&rp);
  bool IsIn(MkLine &rl);
  bool IsIn(MkLine &&rl);
  bool IsInSurface(MkPoint &pnt, double thick);
  bool IsInSurface(MkPoint &&pnt, double thick);
  bool IsInnerSpace(MkPoint &pnt);
  bool IsInnerSpace(MkPoint &&pnt);

  MkPoint &CalcIntPnt(MkLine &);
  MkPoint &CalcIntPnt(MkLine &&);
  MkLine &CalcIntLine(MkTriangle &rt);
  MkLine &CalcIntLine(MkTriangle &&rt);
  MkPoint &CalcIntPnt(MkTriangle &rt);
  MkPoint &CalcIntPnt(MkTriangle &&rt);
  MkPoint &CalcIntPnt(MkTriangles &rts);
  MkPoint &CalcIntPnt(MkTriangles &&rts);

  void operator*(MkMatrix4_d &rm);

  bool operator==(MkPlane &);
  bool operator==(MkPlane &&);
  bool operator!=(MkPlane &);
  bool operator!=(MkPlane &&);
  MkPlane &operator=(MkPlane &rp);
  MkPlane &operator=(MkPlane &&rp);

  MkPoint &operator[](int i);
  MkLine &operator()(int i);

#ifdef __BCPLUSPLUS__
  void Draw(TObject *);
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
  void Draw(MkPaint *);
#endif
};
//---------------------------------------------------------------------------
class MkPlanes : public MkShape, public MkAbstract
{
protected:
  boost::shared_ptr<MkPlane[]> FPlane;
  // MkPlane *FPlane;
  int FSize;
#ifdef __BCPLUSPLUS__
  TColor Color;
#endif
public:
  MkPlanes()
  {
    FSize = 0;
    FPlane = NULL;
  }
  MkPlanes(int FSize);
  MkPlanes(int size, boost::shared_ptr<MkPlane[]> jp);
  MkPlanes(MkPlanes &jp);
  ~MkPlanes();
  virtual void Initialize(int size);
  virtual void Initialize(int size,boost::shared_ptr<MkPlane[]> jp);
  int GetSize() { return FSize; };
  int GetNumber() { return FSize; };
  boost::shared_ptr<MkPlane[]> GetReal() { return FPlane; }
  bool Clear();
  void Translate(double x, double y, double z);
  void Translate(MkPoint rp);

#ifdef __BCPLUSPLUS__
  TColor GetColor()
  {
    return Color;
  };
  void SetColor(TColor c) { Color = c; }
#endif
  virtual MkPlane &operator[](int);
  MkPlanes &operator=(MkPlanes &);
  bool operator==(MkPlanes &);


  std::string ClassName() { return std::string("MkPlanes"); }
#ifdef __BCPLUSPLUS__
  void Draw(TObject *);
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
  void Draw(MkPaint *);
#endif


};
//---------------------------------------------------------------------------
class MkJointPlane : public MkPlane
{
protected:
  double Dip, DipDir; // y axis = north, x axis = east.
  double Aperture;
  int Sort, Form, Condition;

public:
  MkJointPlane();
  MkJointPlane(double dip, double dipdir);
  void SetDipNDir(double dip, double dipdir);
  void SetDipDir(double dipdir) { DipDir = dipdir; }
  void SetDip(double dip) { Dip = dip; }
  void SetAperture(double a) { Aperture = a; }
  void SetSort(int s) { Sort = s; }
  void SetForm(int f) { Form = f; }
  void SetCondition(int c) { Condition = c; }
  double GetAperture() { return Aperture; };
  double GetDipDir() { return DipDir; }
  double GetDip() { return Dip; }
  MkOrient GetOrient() { return MkOrient(Dip, DipDir); }
  int GetSort() { return Sort; }
  void CalcABCD();
  MkJointPlane &operator=(MkJointPlane &p)
  {
    MkPlane::operator=((MkPlane &)p);
    Dip = p.Dip;
    DipDir = p.DipDir;
    Aperture = p.Aperture;
    Sort = p.Sort;
    Form = p.Form;
    Condition = p.Condition;
    return *this;
  }
  MkJointPlane &operator=(MkJointPlane &&p)
  {
    MkPlane::operator=((MkPlane &)p);
    Dip = p.Dip;
    DipDir = p.DipDir;
    Aperture = p.Aperture;
    Sort = p.Sort;
    Form = p.Form;
    Condition = p.Condition;
    return *this;
  }
  bool operator==(MkJointPlane &);
  bool operator==(MkJointPlane &&);
  bool operator!=(MkJointPlane &);
  bool operator!=(MkJointPlane &&);
};
//---------------------------------------------------------------------------
class MkJointPlanes
{
protected:
  boost::shared_ptr<MkJointPlane[]> FJoint;
  // MkJointPlane *FJoint;
  int FSize;
#ifdef __BCPLUSPLUS__
  TColor Color;
#endif
public:
  
  MkJointPlanes()
  {
    FSize = 0;
    FJoint = NULL;
  }
  MkJointPlanes(int FSize);
  MkJointPlanes(int size, boost::shared_ptr<MkJointPlane[]> jp);
  MkJointPlanes(MkJointPlanes &jp);
  ~MkJointPlanes();
  virtual void Initialize(int size);
  virtual void Initialize(int size, boost::shared_ptr<MkJointPlane[]> jp);
  int GetSize() { return FSize; };
  int GetNumber() { return FSize; };
  boost::shared_ptr<MkJointPlane[]> GetJoint() { return FJoint; }
  bool Clear();
#ifdef __BCPLUSPLUS__
  TColor GetColor()
  {
    return Color;
  };
  void SetColor(TColor c) { Color = c; }
#endif
  virtual MkJointPlane &operator[](int);
  MkJointPlanes &operator=(MkJointPlanes &);
  bool operator==(MkJointPlanes &);

  void Translate(double x, double y, double z);
  void Translate(MkPoint rp);

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

//---------------------------------------------------------------------------
class MkCylinder;
class MkPennyJoint : public MkJointPlane
{
protected:
  double FRadius;
  MkLine FLine; // for internal use
public:
  MkPennyJoint();
  MkPennyJoint(double dip, double dipdir);
  void SetRadius(double r) { FRadius = r; }
  double GetRadius() { return FRadius; }
  bool GetOutline(MkPolygon &poly, int div);
  bool GetOutline(MkPolygon &&poly, int div);
  bool IsIntersect(MkLine &);  // updated at 2001.8.25.
  bool IsIntersect(MkLine &&); // updated at 2001.8.25.
  bool IsIntersect(MkTriangle &rt);
  bool IsIntersect(MkTriangle &&rt);
  bool IsIntersect(MkPennyJoint &pj);
  bool IsIntersect(MkPennyJoint &&pj);
  bool IsIntersect(MkPlane &rp);
  bool IsIntersect(MkPlane &&rp);
  bool IsIntersect(MkCylinder &rc);
  bool IsIntersect(MkCylinder &&rc);
  MkPoint &CalcIntPnt(MkLine &);
  MkPoint &CalcIntPnt(MkLine &&);
  MkLine &CalcIntLine(MkTriangle &rt);
  MkLine &CalcIntLine(MkTriangle &&rt);
  MkLine &CalcIntLine(MkPennyJoint &pj);
  MkLine &CalcIntLine(MkPennyJoint &&pj);
  MkLine &CalcIntLine(MkPlane &rp);
  MkLine &CalcIntLine(MkPlane &&rp);
  MkPoint &CalcIntPnt(MkCylinder &rc);
  MkPoint &CalcIntPnt(MkCylinder &&rc);
  MkPoint &CalcIntPnt(MkTriangle &rt);
  MkPoint &CalcIntPnt(MkTriangle &&rt);
  MkPoint &CalcIntPnt(MkTriangles &rts);
  MkPoint &CalcIntPnt(MkTriangles &&rts);

  bool operator&&(MkLine &rl) { return IsIntersect(rl); }
  bool operator&&(MkLine &&rl) { return IsIntersect(rl); }
  bool operator&&(MkTriangle &rt) { return IsIntersect(rt); }
  bool operator&&(MkTriangle &&rt) { return IsIntersect(rt); }
  bool operator&&(MkPennyJoint &pj) { return IsIntersect(pj); }
  bool operator&&(MkPennyJoint &&pj) { return IsIntersect(pj); }
  bool operator&&(MkPlane &rp) { return IsIntersect(rp); }
  bool operator&&(MkPlane &&rp) { return IsIntersect(rp); }
  bool operator&&(MkCylinder &rc) { return IsIntersect(rc); }
  bool operator&&(MkCylinder &&rc) { return IsIntersect(rc); }
  MkPoint &operator&(MkLine &rl) { return CalcIntPnt(rl); }
  MkPoint &operator&(MkLine &&rl) { return CalcIntPnt(rl); }
  MkLine &operator&(MkPennyJoint &pj) { return CalcIntLine(pj); }
  MkLine &operator&(MkPennyJoint &&pj) { return CalcIntLine(pj); }
  MkLine &operator&(MkPlane &rp) { return CalcIntLine(rp); }
  MkLine &operator&(MkPlane &&rp) { return CalcIntLine(rp); }
  MkPoint &operator&(MkCylinder &rc) { return CalcIntPnt(rc); }
  MkPoint &operator&(MkCylinder &&rc) { return CalcIntPnt(rc); }
  MkPoint &operator&(MkTriangle &rt) { return CalcIntPnt(rt); }
  MkPoint &operator&(MkTriangle &&rt) { return CalcIntPnt(rt); }
  MkPoint &operator&(MkTriangles &rts) { return CalcIntPnt(rts); }
  MkPoint &operator&(MkTriangles &&rts) { return CalcIntPnt(rts); }
  MkPennyJoint &operator=(MkPennyJoint &p)
  {
    MkJointPlane::operator=((MkJointPlane &)p);
    FRadius = p.FRadius;
    FLine = p.FLine;
    return *this;
  }
  MkPennyJoint &operator=(MkPennyJoint &&p)
  {
    MkJointPlane::operator=((MkJointPlane &&) p);
    FRadius = p.FRadius;
    FLine = p.FLine;
    return *this;
  }
  bool operator==(MkPennyJoint &);
  bool operator==(MkPennyJoint &&);
  bool operator!=(MkPennyJoint &);
  bool operator!=(MkPennyJoint &&);

#ifdef __BCPLUSPLUS__
  void Draw(TObject *);
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
  void Draw(MkPaint *);
#endif
};
//---------------------------------------------------------------------------
class MkPennyJoints
{
protected:
  boost::shared_ptr<MkPennyJoint[]> FPenny;
  // MkPennyJoint *FPenny;
  int FSize;
#ifdef __BCPLUSPLUS__
  TColor Color;
#endif
public:
  MkPennyJoints(int size, boost::shared_ptr<MkPennyJoint[]> jp);
  MkPennyJoints(int FSize);
  MkPennyJoints()
  {
    FSize = 0;
    FPenny = NULL;
  }
  ~MkPennyJoints();
  virtual void Initialize(int size);
  virtual void Initialize(int size, boost::shared_ptr<MkPennyJoint[]> jp);
  int GetSize() { return FSize; };
  int GetNumber() { return FSize; };
  boost::shared_ptr<MkPennyJoint[]>GetJoint() { return FPenny; }
  bool Clear();
#ifdef __BCPLUSPLUS__
  TColor GetColor()
  {
    return Color;
  };
  void SetColor(TColor c) { Color = c; }
#endif
  virtual MkPennyJoint &operator[](int);

  MkPennyJoints &operator=(MkPennyJoints &);
  bool operator==(MkPennyJoints &);

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
//---------------------------------------------------------------------------
extern MkJointPlane NullJoint;
extern MkJointPlanes NullJoints;
extern MkPointsPlane NullPointPlane;
extern MkPlane NullPlane;
extern MkPennyJoint NullPenny;

#endif

// Scale->Rotate->Translate
