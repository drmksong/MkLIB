//---------------------------------------------------------------------------
#ifndef MkLineH
#define MkLineH

#include <cmath>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "MkShape.hpp"
#include "MkPoint.hpp"
#include "MkMatrix.hpp"

#if defined(_MSC_VER) && defined(_WINDOWS_)
class MkPaint;
#endif

class MkArc;
//---------------------------------------------------------------------------
class MkLine : public MkShape
{
private:
    MkPoint StartPoint, EndPoint;
    double Theta, Length;
    int Width;      // it is pixel base width for the thickness of line
    double A, B, C; // A*X + B*Y = C  (C = 0 or 1)
    double L, M, N; // direction cosine
    bool isSelected;
    bool isFinite;

    void CalLength();
    void CalTheta();
    void CalCoeff();
    double Tol;

public:
    MkLine();
    MkLine(MkPoint &sp, MkPoint &ep);
    MkLine(MkPoint &&sp, MkPoint &&ep);
    MkLine(double sx, double sy, double ex, double ey);

#ifdef __BCPLUSPLUS__
    MkLine(MkPoint sp, MkPoint ep, TColor C);
    MkLine(double sx, double sy, double ex, double ey, TColor C);
    void SetLine(MkPoint sp, MkPoint ep, TColor C);
    void SetLine(double sx, double sy, double ex, double ey, TColor C);
#endif

    std::string ClassName()
    {
        return std::string("MkLine");
    }

    void SetLine(MkPoint &sp, MkPoint &ep);
    void SetLine(MkPoint &&sp, MkPoint &&ep);
    void SetLine(double sx, double sy, double ex, double ey);
    void SetTol(double tol) { Tol = tol; }
    void SetLineWidth(int w) { Width = w; }

public:
    double GetLength() ;
    double GetTheta() ;
    bool GetFiniteness() const { return isFinite; }
    void SetFiniteness(bool fin) { isFinite = fin; }
    void AdjustTheta()
    {
        if (Theta > 360)
            Theta -= 360;
        else if (Theta < 0)
            Theta += 360;
    }
    MkPoint &GetMiddlePoint()
    {
        static MkPoint midpnt =
            MkPoint(
                ((*this)[0].X + (*this)[1].X) / 2,
                ((*this)[0].Y + (*this)[1].Y) / 2,
                ((*this)[0].Z + (*this)[1].Z) / 2);

        return midpnt;
    };
    MkPoint &GetDivision(double f);

    void Extend(double f);
    double DeltaX() { return EndPoint.X - StartPoint.X; };
    double DeltaY() { return EndPoint.Y - StartPoint.Y; };
    double DeltaZ() { return EndPoint.Z - StartPoint.Z; };
    double NormDeltaX() { return fabs(StartPoint.X) < 1.0e-6 ? 0 : ((EndPoint.X - StartPoint.X) / StartPoint.X); };
    double NormDeltaY() { return fabs(StartPoint.Y) < 1.0e-6 ? 0 : ((EndPoint.Y - StartPoint.Y) / StartPoint.Y); };
    bool IsIntersect(MkLine &realline);
    bool IsIntersect(MkLine &&realline);
    bool IsIn(MkPoint &rp);
    bool IsIn(MkPoint &&rp);
    bool IsIn(double x, double y);
    bool IsInLine(MkPoint &rp);
    bool IsInLine(MkPoint &&rp);
    bool IsInLine(double x, double y);
    bool IsInSamePlane(MkLine &rl);
    bool IsInSamePlane(MkLine &&rl);
    bool GetIntParam(MkLine &rl, double &t);
    bool GetIntParam(MkLine &&rl, double &t);
    bool GetIntParam(MkPoint &p, double &t);
    bool GetIntParam(MkPoint &&p, double &t);

    MkPoint &GetIntPoint(MkLine &rl);
    MkPoint &GetIntPoint(MkLine &&rl);

    double GetArea() { return 0; };
    double GetA() { return A; }
    double GetB() { return B; }
    double GetC() { return C; }
    double GetL() { return L; }
    double GetM() { return M; }
    double GetN() { return N; }
    int GetLineWidth() { return Width; }

    MkVector<double> &GetVector() const
    {
        static MkVector<double> vec(3);
        vec[0] = EndPoint.X - StartPoint.X;
        vec[1] = EndPoint.Y - StartPoint.Y;
        vec[2] = EndPoint.Z - StartPoint.Z;
        vec.Normalize();
        return vec;
    }

    void Select() { isSelected = true; }
    void Unselect() { isSelected = false; }
    bool GetSelected() { return isSelected; }

    double CalDist(MkPoint &rp) { return fabs(A * rp.X + B * rp.Y - C) / sqrt(A * A + B * B); }
    double CalDist(MkPoint &&rp) { return fabs(A * rp.X + B * rp.Y - C) / sqrt(A * A + B * B); }
    double CalDist(double x, double y) { return fabs(A * x + B * y - C) / sqrt(A * A + B * B); }

    double CalDist3D(MkPoint &rp);
    double CalDist3D(MkPoint &&rp);
    double CalDist3D(double x, double y, double z);

    MkPoint &GetNearestPnt(MkPoint &rp);
    MkPoint &GetNearestPnt(MkPoint &&rp);
    MkPoint &GetNearestPnt(double x, double y, double z);

    MkLine &Translate(MkPoint rp);
    MkLine &Translate(double x, double y, double z);
    MkLine &Rotate(double alpha, double beta, double gamma);
    MkLine &RotateInX(double ang);
    MkLine &RotateInY(double ang);
    MkLine &RotateInZ(double ang);
    MkLine &RotateInA(double ang, double l, double m, double n);

    MkLine &Scale(double sx, double sy, double sz);

    void Out();
    void Clear();
    bool operator&&( MkLine &rline1);
    bool operator&&(MkLine &&rline1);

    bool operator==(MkLine &rline1);
    bool operator==(MkLine &&rline1);

    bool operator!=(MkLine &rline1);
    bool operator!=(MkLine &&rline1);

    MkPoint &operator&(MkLine &l);
    MkPoint &operator&(MkLine &&l);

    MkPoint &operator[](int);

    double operator+(MkLine &l); // dot product
    double operator+(MkLine &&l);      // dot product
    double operator*(MkLine &l);
    double operator*(MkLine &&l);
    double operator*(MkPoint &rp); // cross product
    double operator*(MkPoint &&rp);      // cross product

    MkLine &operator*(MkMatrix4_d &rm);

    double operator+=(MkPoint &p);
    double operator+=(MkPoint &&p);
    double operator-=(MkPoint &p);
    double operator-=(MkPoint &&p);

    MkLine &operator=(MkLine &);
    MkLine &operator=(MkLine &&);
    MkLine &operator!();

#ifdef __BCPLUSPLUS__
    void Draw(TObject *);
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
    void Draw(MkPaint *);
#endif
};

class MkLines
{
protected:
    int FSize;
    boost::shared_ptr<MkLine[]>FRealLine;
#ifdef __BCPLUSPLUS__
    TColor Color;
#endif
#if defined(_MSC_VER) && defined(_WINDOWS_)
    MkColor PColor, BColor;
#endif
public:
    MkLines()
    {
        FSize = 0;
        FRealLine = NULL;
    }
    MkLines(int FSize);
    MkLines(int size, boost::shared_ptr<MkLine[]>rl);
    MkLines(const MkLines &rl);   
    ~MkLines();
    void Initialize(int size);
    void Initialize(int size, boost::shared_ptr<MkLine[]>rl);
    void Grow(int sz);
    void Add(MkLine &l)
    {
        Grow(1);
        FRealLine[FSize - 1] = l;
    }
    void DeleteSelected();
    int GetSize() { return FSize; };
    int GetNumber() { return FSize; };
    MkLine &GetLine(int i) { if (i < FSize) return FRealLine[i]; }
    boost::shared_ptr<MkLine[]> &GetLines() {return FRealLine;}
    bool Clear();
#ifdef __BCPLUSPLUS__
    TColor GetColor()
    {
        return Color;
    };
    void SetColor(TColor c) { Color = c; }
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
    MkColor GetColor()
    {
        return PColor;
    };
    void SetColor(MkColor c) { PColor = c; }
#endif

    virtual MkLine &operator[](int);

    MkLines &RotateInX(double ang);
    MkLines &RotateInY(double ang);
    MkLines &RotateInZ(double ang);
    MkLines &RotateInA(double ang, double l, double m, double n);

    MkLines &operator*(MkMatrix4_d &rm);
    MkLines &operator=(MkLines &);
    bool operator==(MkLines &);
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

void GetSubParam(int i, MkLines &in, double &aj, double &bj, double &lj1, double &lj);
extern MkLine NullLine;
extern MkLines NullLines;
//---------------------------------------------------------------------------
#endif
