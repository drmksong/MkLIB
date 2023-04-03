//---------------------------------------------------------------------------
#ifndef MkRectH
#define MkRectH
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "MkShape.hpp"
#include "MkLine.hpp"
//---------------------------------------------------------------------------
class MkRect : public MkShape
{
protected:
  MkPoint Center;
  MkPoint Origin;
  double Width, Height;

public:
  MkRect();
  MkRect(int);
  MkRect(MkPoint &p);
  MkRect(MkPoint &&p);
  MkRect(double x, double y);

public:
  void SetOrigin(MkPoint &pnt) { Origin = pnt; }
  void SetOrigin(MkPoint &&pnt) { Origin = pnt; }
  void SetCenter(MkPoint &pnt) { Center = pnt; }
  void SetCenter(MkPoint &&pnt) { Center = pnt; }

  void SetHeight(double h) { Height = h; }
  void SetWidth(double w) { Width = w; }

public:
  MkPoint &GetOrigin() { return Origin; }
  double GetHeight() { return Height; }
  double GetWidth() { return Width; }

  // TODO: Test whether void GetCross and MkPoints &GetCross version returns the same
  void GetCross(MkLine &, MkPoints &);
  void GetCross(MkLine &&, MkPoints &);
  MkPoints &GetCross(MkLine &);
  MkPoints &GetCross(MkLine &&);

  double GetTop() { return max(Origin.Y + Height, Origin.Y); }
  double GetBot() { return min(Origin.Y + Height, Origin.Y); }
  double GetLeft() { return min(Origin.X + Width, Origin.X); }
  double GetRight() { return max(Origin.X + Width, Origin.X); }

  MkPoints &GetIntPoints(MkLine &line);
  MkPoints &GetIntPoints(MkLine &&line);

  MkPoint &GetCenter()
  {
    Center = Origin;
    Center.X += Width / 2;
    Center.Y += Height / 2;
    return Center;
  }

  bool isRect() { return true; }
  bool IsIn(MkPoint &pnt);
  bool IsIn(MkPoint &&pnt);
  bool IsInSurface(MkPoint &pnt, double thick);
  bool IsInSurface(MkPoint &&pnt, double thick);
  bool IsInSpace(MkPoint &pnt);
  bool IsInSpace(MkPoint &&pnt);

  MkRect &operator=(MkRect &rect)
  {
    Origin = rect.Origin;
    Width = rect.Width;
    Height = rect.Height;
    return *this;
  }

  MkRect &operator=(MkRect &&rect)
  {
    Origin = rect.Origin;
    Width = rect.Width;
    Height = rect.Height;
    return *this;
  }

  bool operator==(MkRect &rect) { return Origin == rect.Origin && Width == rect.Width && Height == rect.Height; }
  bool operator==(MkRect &&rect) { return Origin == rect.Origin && Width == rect.Width && Height == rect.Height; }
  bool operator!=(MkRect &rect) { return Origin != rect.Origin || Width != rect.Width || Height != rect.Height; }
  bool operator!=(MkRect &&rect) { return Origin != rect.Origin || Width != rect.Width || Height != rect.Height; }

  MkPoint &operator[](int i);
  MkLine &operator()(int i);

  std::string ClassName() { return std::string("MkRect"); }

#ifdef __BCPLUSPLUS__
  void Draw(TObject *);
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
  void Draw(MkPaint *);
#endif
};

class MkRects
{
private:
  int FSize;
  boost::shared_ptr<MkRect[]> FRect;

public:
  MkRects();
  MkRects(int);
  MkRects(int, boost::shared_ptr<MkRect[]>rects);
  MkRects(MkRects &rects);
  ~MkRects();
  bool Initialize(int size);
  bool Initialize(int size, boost::shared_ptr<MkRect[]>rect);
  bool Initialize(MkRects &rects);
  void Clear();

  MkRect &operator()(int);
  MkRect &operator[](int);
  MkRects &operator=(MkRects &a);

  int GetSize() { return FSize; };

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
extern MkRect NullRect;
#endif
