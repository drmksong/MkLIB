//---------------------------------------------------------------------------
#ifndef MkCircleH
#define MkCircleH

#include <math.h>
#include "MkShape.hpp"
#include "MkPoint.hpp"
#include "MkLine.hpp"
#include "MkTriangle.hpp"

// It is used for only 2 dimensional geometry operation
// I should upgrade this for 3 dimensional...
//---------------------------------------------------------------------------

class MkCircle : public MkShape
{
protected:
    MkPoint FCP;
    double FRadius;
    double FCircleArea;
    MkPoints FRealPoints;
    virtual void CalArea();

public:
    MkCircle();
    MkCircle(int);
    MkCircle(double cx, double cy, double radius);
    MkCircle(MkPoint &cp, double radius);
    MkCircle(MkPoint &&cp, double radius);
#ifdef __BCPLUSPLUS__
    MkCircle(double cx, double cy, double radius, TColor C);
    MkCircle(MkPoint cp, double radius, TColor C);
#endif
    void SetCircle(double cx, double cy, double radius);
    void SetCircle(MkPoint &cp, double radius);
    void SetCircle(MkPoint &&cp, double radius);
#ifdef __BCPLUSPLUS__
    void SetCircle(double cx, double cy, double radius, TColor C);
    void SetCircle(MkPoint cp, double radius, TColor C);
#endif
    virtual void SetCenter(double cx, double cy);
    virtual void SetCenter(MkPoint &cp);
    virtual void SetCenter(MkPoint &&cp);
    virtual void SetRadius(double radius);

    MkPoint &GetCenter() { return FCP; }
    double GetRadius() { return FRadius; }
    double GetArea()
    {
        CalArea();
        return FCircleArea;
    }
    MkPoint &operator[](int);

    std::string ClassName()
    {
        return std::string("MkCircle");
    }

    bool isCircle()
    {
        return true;
    }
    bool IsInSurface(MkPoint &pnt, double thick);
    bool IsInSpace(MkPoint &pnt);

    MkCircle &operator=(MkCircle &rc);
    bool operator&&(MkLine &rl);
    MkPoints &operator&(MkLine &rl);
    MkPoints &operator&(MkPoint &rp);

    bool operator==(MkCircle &c);
    bool operator!=(MkCircle &c);

#ifdef __BCPLUSPLUS__
    void Draw(TObject *);
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
    void Draw(MkPaint *);
#endif
};

class MkCircles : public MkShape
{
protected:
    boost::shared_ptr<MkCircle[]> FCircle;
    int FSize;

public:
    MkCircles(int Size);
    MkCircles()
    {
        FSize = 0;
        FCircle.reset();
    }
    // TODO: should revise if the implementation is not efficient!!!
    MkCircles(int size, boost::shared_ptr<MkCircle[]> circle);
    MkCircles(MkCircles &circles);

    ~MkCircles()
    {
        FSize = 0;
        FCircle.reset();
    }
    void Initialize(int Size);
    void Clear();
    int GetSize() { return FSize; }
    virtual MkCircle &operator[](int);
    MkCircles &operator=(MkCircles &circles);

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

class MkArc : public MkCircle
{
private:
    MkPoint FStartPoint, FEndPoint;
    double FStartAng, FEndAng;
    double FCrownArea;
    void CalArea(); // TODO: Implement it
    void CalCrownArea(); // TODO: Implement it
    void CalTriArea(); // TODO: Implement it
    void CalStartPoint();
    void CalEndPoint();
    void CalStartAngle();
    void CalEndAngle();

public:
    MkArc();
    MkArc(int);
    MkArc(MkPoint &p1, MkPoint &p2, MkLine &line);
    MkArc(MkPoint &&p1, MkPoint &&p2, MkLine &&line);
    MkArc(double cx, double cy, double radius, double start_ang, double end_ang);
    MkArc(MkPoint &cp, double radius, double start_ang, double end_ang);
    MkArc(MkPoint &&cp, double radius, double start_ang, double end_ang);
#ifdef __BCPLUSPLUS__
    MkArc(MkPoint cp, double radius, double start_ang, double end_ang, TColor C);
    MkArc(double cx, double cy, double radius, double start_ang, double end_ang, TColor C);
#endif
    void ReCalcPoint();
    void ReCalcAng();
    void SetCenter(double cx, double cy);
    void SetCenter(MkPoint &cp);
    void SetCenter(MkPoint &&cp);
    void SetRadius(double radius);
    void SetStartAng(double start_ang);
    void SetEndAng(double end_ang);
    double GetStartAng();
    double GetEndAng();
    double GetArea();
    double GetAngle() { return FEndAng - FStartAng; };
    double GetCrownArea();
    double GetTriArea();
    bool isWithInArc(MkPoint rp);
    bool isWithInAng(MkPoint rp);
    double CrossProduct();
    MkPoint &StartPoint() { return FStartPoint; };
    MkPoint &EndPoint() { return FEndPoint; };
    MkPoint &operator[](int);
    MkLine &operator()(int);

    std::string ClassName()
    {
        return std::string("MkArc");
    }
    
    MkArc &operator=(MkArc &ra);

#ifdef __BCPLUSPLUS__
    void Draw(TObject *);
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
    void Draw(MkPaint *);
#endif
};
extern MkCircle NullCircle;
extern MkArc NullArc;
//---------------------------------------------------------------------------

#endif
