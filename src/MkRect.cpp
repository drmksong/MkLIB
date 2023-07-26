//---------------------------------------------------------------------------
#pragma hdrstop

#include "MkRect.hpp"

#ifdef __BCPLUSPLUS__
#include <vcl.h>
#endif

//---------------------------------------------------------------------------
#ifdef __BCPLUSPLUS__
#pragma package(smart_init)
#endif
//---------------------------------------------------------------------------
MkRect NullRect(0);

MkRect::MkRect()
{
  Origin = NullPoint;
  Width = 0;
  Height = 0;
}

MkRect::MkRect(int)
{
  Origin = NullPoint;
  Width = 0;
  Height = 0;
}

MkRect::MkRect(MkPoint &pnt)
{
  Origin = pnt;
  Width = 0;
  Height = 0;
}

MkRect::MkRect(MkPoint &&pnt)
{
  Origin = pnt;
  Width = 0;
  Height = 0;
}

MkRect::MkRect(double x, double y)
{
  Origin.X = x;
  Origin.Y = y;
  Origin.Z = 0;
  Width = 0;
  Height = 0;
}

MkPoints &MkRect::GetIntPoints(MkLine &line)
{
  static MkPoints pnts;
  MkPoint p;
  MkLine l;

  pnts.Clear();
  for (int i = 0; i < 4; i++)
  {
    l = (*this)(i);
    l[0].Z = 0;
    l[1].Z = 0;
    l.SetFiniteness(true);
    if (line && l)
    {
      p = line.GetIntPoint(l);
      pnts.Add(p);
    }
  }
  return pnts;
}

MkPoints &MkRect::GetIntPoints(MkLine &&line)
{
  static MkPoints pnts;
  MkPoint p;
  MkLine l;

  pnts.Clear();
  for (int i = 0; i < 4; i++)
  {
    l = (*this)(i);
    l[0].Z = 0;
    l[1].Z = 0;
    l.SetFiniteness(true);
    if (line && l)
    {
      p = line.GetIntPoint(l);
      pnts.Add(p);
    }
  }
  return pnts;
}

bool MkRect::IsIn(MkPoint &pnt)
{
  return min(Origin.X, Origin.X + Width) < pnt.X && pnt.X < max(Origin.X, Origin.X + Width) && min(Origin.Y, Origin.Y + Height) < pnt.Y && pnt.Y < max(Origin.Y, Origin.Y + Height);
}

bool MkRect::IsIn(MkPoint &&pnt)
{
  return min(Origin.X, Origin.X + Width) < pnt.X && pnt.X < max(Origin.X, Origin.X + Width) && min(Origin.Y, Origin.Y + Height) < pnt.Y && pnt.Y < max(Origin.Y, Origin.Y + Height);
}

bool MkRect::IsInSurface(MkPoint &pnt, double thick)
{
  double d = thick + 100;
  MkLine l;
  l.SetLine(Origin.X, Origin.Y, Origin.X + Width, Origin.Y);
  d = l.CalDist(pnt);
  l.SetLine(Origin.X, Origin.Y, Origin.X, Origin.Y + Height);
  d = min(d, l.CalDist(pnt));
  l.SetLine(Origin.X, Origin.Y + Height, Origin.X + Width, Origin.Y + Height);
  d = min(d, l.CalDist(pnt));
  l.SetLine(Origin.X + Width, Origin.Y, Origin.X + Width, Origin.Y + Height);
  d = min(d, l.CalDist(pnt));
  if (d < thick)
    return true;
  else
    return false;
}

bool MkRect::IsInSurface(MkPoint &&pnt, double thick)
{
  double d = thick + 100;
  MkLine l;
  l.SetLine(Origin.X, Origin.Y, Origin.X + Width, Origin.Y);
  d = l.CalDist(pnt);
  l.SetLine(Origin.X, Origin.Y, Origin.X, Origin.Y + Height);
  d = min(d, l.CalDist(pnt));
  l.SetLine(Origin.X, Origin.Y + Height, Origin.X + Width, Origin.Y + Height);
  d = min(d, l.CalDist(pnt));
  l.SetLine(Origin.X + Width, Origin.Y, Origin.X + Width, Origin.Y + Height);
  d = min(d, l.CalDist(pnt));
  if (d < thick)
    return true;
  else
    return false;
}

bool MkRect::IsInSpace(MkPoint &pnt)
{
  return IsIn(pnt);
}

bool MkRect::IsInSpace(MkPoint &&pnt)
{
  return IsIn(pnt);
}

// TODO: Test whether void GetCross and MkPoints &GetCross version returns the same
void MkRect::GetCross(MkLine &l, MkPoints &p)
{
  MkLine line[4];
  MkPoint pnt[4];
  int i, cnt;
  pnt[0].SetPoint(Origin.X, Origin.Y, Origin.Z);
  pnt[1].SetPoint(Origin.X + Width, Origin.Y, Origin.Z);
  pnt[2].SetPoint(Origin.X + Width, Origin.Y + Height, Origin.Z);
  pnt[3].SetPoint(Origin.X, Origin.Y + Height, Origin.Z);
  line[0].SetLine(pnt[0], pnt[1]);
  line[1].SetLine(pnt[1], pnt[2]);
  line[2].SetLine(pnt[2], pnt[3]);
  line[3].SetLine(pnt[3], pnt[0]);

  cnt = 0;
  for (i = 0; i < 4; i++)
  {
    if (l.IsIntersect(line[i]))
      cnt++;
  }

  p.Initialize(cnt);

  cnt = 0;
  for (i = 0; i < 4; i++)
  {
    if (l.IsIntersect(line[i]))
    {
      p[cnt] = l & line[i];
      cnt++;
    }
  }
}

// TODO: Test whether void GetCross and MkPoints &GetCross version returns the same
void MkRect::GetCross(MkLine &&l, MkPoints &p)
{
  MkLine line[4];
  MkPoint pnt[4];
  int i, cnt;
  pnt[0].SetPoint(Origin.X, Origin.Y, Origin.Z);
  pnt[1].SetPoint(Origin.X + Width, Origin.Y, Origin.Z);
  pnt[2].SetPoint(Origin.X + Width, Origin.Y + Height, Origin.Z);
  pnt[3].SetPoint(Origin.X, Origin.Y + Height, Origin.Z);
  line[0].SetLine(pnt[0], pnt[1]);
  line[1].SetLine(pnt[1], pnt[2]);
  line[2].SetLine(pnt[2], pnt[3]);
  line[3].SetLine(pnt[3], pnt[0]);

  cnt = 0;
  for (i = 0; i < 4; i++)
  {
    if (l.IsIntersect(line[i]))
      cnt++;
  }

  p.Initialize(cnt);

  cnt = 0;
  for (i = 0; i < 4; i++)
  {
    if (l.IsIntersect(line[i]))
    {
      p[cnt] = l & line[i];
      cnt++;
    }
  }
}

// TODO: Test whether void GetCross and MkPoints &GetCross version returns the same
MkPoints &MkRect::GetCross(MkLine &l)
{
  static MkPoints p;
  MkLine line[4];
  MkPoint pnt[4];
  int i, cnt;
  pnt[0].SetPoint(Origin.X, Origin.Y, Origin.Z);
  pnt[1].SetPoint(Origin.X + Width, Origin.Y, Origin.Z);
  pnt[2].SetPoint(Origin.X + Width, Origin.Y + Height, Origin.Z);
  pnt[3].SetPoint(Origin.X, Origin.Y + Height, Origin.Z);
  line[0].SetLine(pnt[0], pnt[1]);
  line[1].SetLine(pnt[1], pnt[2]);
  line[2].SetLine(pnt[2], pnt[3]);
  line[3].SetLine(pnt[3], pnt[0]);

  cnt = 0;
  for (i = 0; i < 4; i++)
  {
    if (l.IsIntersect(line[i]))
      cnt++;
  }

  p.Initialize(cnt);

  cnt = 0;
  for (i = 0; i < 4; i++)
  {
    if (l.IsIntersect(line[i]))
    {
      p[cnt] = l & line[i];
      cnt++;
    }
  }
  return p;
}

// TODO: Test whether void GetCross and MkPoints &GetCross version returns the same
MkPoints &MkRect::GetCross(MkLine &&l)
{
  static MkPoints p;
  MkLine line[4];
  MkPoint pnt[4];
  int i, cnt;
  pnt[0].SetPoint(Origin.X, Origin.Y, Origin.Z);
  pnt[1].SetPoint(Origin.X + Width, Origin.Y, Origin.Z);
  pnt[2].SetPoint(Origin.X + Width, Origin.Y + Height, Origin.Z);
  pnt[3].SetPoint(Origin.X, Origin.Y + Height, Origin.Z);
  line[0].SetLine(pnt[0], pnt[1]);
  line[1].SetLine(pnt[1], pnt[2]);
  line[2].SetLine(pnt[2], pnt[3]);
  line[3].SetLine(pnt[3], pnt[0]);

  cnt = 0;
  for (i = 0; i < 4; i++)
  {
    if (l.IsIntersect(line[i]))
      cnt++;
  }

  p.Initialize(cnt);

  cnt = 0;
  for (i = 0; i < 4; i++)
  {
    if (l.IsIntersect(line[i]))
    {
      p[cnt] = l & line[i];
      cnt++;
    }
  }
  return p;
}

// TODO: MkRect should have four corners as member variables
MkPoint &MkRect::operator[](int i)
{
  static MkPoint p;
  if (i < 0 || i > 4)
    return NullPoint;

  p.SetPoint(Origin.X + Width * (i == 1 || i == 2 ? 1 : 0), Origin.Y + Height * (i == 2 || i == 3 ? 1 : 0), 0);
#ifdef __BCPLUSPLUS__
  p.SetPoint(Origin.X + Width * (i == 1 || i == 2 ? 1 : 0), Origin.Y + Height * (i == 2 || i == 3 ? 1 : 0), Color);
#endif
#if defined(_MSC_VER) && defined(_WINDOWS_)
  p.SetPoint(Origin.X + Width * (i == 1 || i == 2 ? 1 : 0), Origin.Y + Height * (i == 2 || i == 3 ? 1 : 0), 0);
#endif

  return p;
}

// TODO: MkRect should have four edges as member variables
MkLine &MkRect::operator()(int i)
{
  static MkLine l;
  MkPoint sp, ep;
  if (i < 0 || i > 4)
    return NullLine;

  sp = (*this)[i];
  ep = (*this)[(i == 3) ? 0 : i + 1];

  l.SetLine(sp, ep);
  l.SetFiniteness(true);

  return l;
}

#ifdef __BCPLUSPLUS__
void MkRect::Draw(TObject *Sender)
{
  /*   TColor C;
     TPenStyle PS;
     if (String(Sender->ClassName()) == String("MkPaintBox")) {
        MkPaintBox *pb=(MkPaintBox*)Sender;
        C = pb->Canvas->Pen->Color;
        PS = pb->Canvas->Pen->Style;
        pb->Canvas->Pen->Color = Color;
  //      pb->Canvas->Pen->Style = PenStyle;

        for(int i=0;i<4;i++) (*this)(i).Draw(Sender);

        pb->Canvas->Pen->Color = C;
        pb->Canvas->Pen->Style = PS;
     }
  */
}
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
void MkRect::Draw(MkPaint *pb)
{
  MkColor c;
  for (int i = 0; i < 4; i++)
    (*this)(i).Draw(pb);
}
#endif

//---------------------------------------------------------------------------
MkRects::MkRects()
{
  FSize = 0;
  FRect.reset();
}

MkRects::MkRects(int size)
{
  if (size < 0)
  {
    FSize = 0;
    FRect.reset();
    throw Alloc(std::string("MkRects::MkRects(int size)", "size < 0"));
  }

  FSize = size;

  if (FSize == 0)
  {
    FRect.reset();
    return;
  }

  try {
    FRect = boost::make_shared<MkRect[]>(FSize);
  }
  catch(std::bad_alloc &e) {
    FSize = 0;
    FRect.reset();
    throw Alloc(std::string("MkRects::MkRects(int size) - bad_alloc", e.what()));
  }
  catch(...){
    FSize = 0;
    FRect.reset();
    throw Alloc(std::string("MkRects::MkRects(int size) - unknown exception"));
  }
}

MkRects::MkRects(int size, boost::shared_ptr<MkRect[]> rect)
{
  if (size < 0)
  {
    FSize = 0;
    FRect.reset();
    throw Alloc(std::string("MkRects::MkRects(int size, boost::shared_ptr<MkRect[]> rect)", "size < 0"));
  }

  FSize = size;
  if (FSize == 0)
  {
    FRect.reset();
    return;
  }
  try {
    FRect = boost::make_shared<MkRect[]>(FSize);
  }
  catch(std::bad_alloc &e) {
    FSize = 0;
    FRect.reset();
    throw Alloc(std::string("MkRects::MkRects(int size, boost::shared_ptr<MkRect[]> rect) - bad_alloc",e.what()));
  }
  catch(...) {
    FSize = 0;
    FRect.reset();
    throw Alloc(std::string("MkRects::MkRects(int size, boost::shared_ptr<MkRect[]> rect) - unknown exception"));
  }
  
  for (int i = 0; i < FSize; i++)
    FRect[i] = rect[i];
}

MkRects::MkRects(MkRects &rects)
{
  FSize = rects.FSize;
  if (FSize == 0)
  {
    FRect.reset();
    return;
  }
  try {
    FRect = boost::make_shared<MkRect[]>(FSize);
  }
  catch(std::bad_alloc &e) {
    FSize = 0;
    FRect.reset();
    throw Alloc(std::string("MkRects::MkRects(const MkRects &rects) - bad_alloc", e.what()));
  }
  catch(...) {
    FSize = 0;
    FRect.reset();
    throw Alloc(std::string("MkRects::MkRects(const MkRects &rects) - unknown exception"));
  }
  
  for (int i = 0; i < FSize; i++)
    FRect[i] = rects.FRect[i];
}

MkRects::~MkRects()
{
  FSize = 0;
  FRect.reset();
}

bool MkRects::Initialize(int size)
{
  if (size < 0)
  {
    FSize = 0;
    FRect.reset();
    throw Alloc(std::string("MkRects::MkRects(int size)", "size < 0"));
  }

  FSize = size;

  if (FSize == 0)
  {
    FRect.reset();
    return false;
  }

  try {
    FRect = boost::make_shared<MkRect[]>(FSize);
  }
  catch(std::bad_alloc &e) {
    FSize = 0;
    FRect.reset();
    throw Alloc(std::string("MkRects::MkRects(int size) - bad_alloc", e.what()));
  }
  catch(...){
    FSize = 0;
    FRect.reset();
    throw Alloc(std::string("MkRects::MkRects(int size) - unknown exception"));
  }

  return true;
}

bool MkRects::Initialize(int size, boost::shared_ptr <MkRect[]> rect)
{
  if (size < 0)
  {
    FSize = 0;
    FRect.reset();
    throw Alloc(std::string("MkRects::MkRects(int size, boost::shared_ptr<MkRect[]> rect)", "size < 0"));
  }

  FSize = size;
  if (FSize == 0)
  {
    FRect.reset();
    return false;
  }
  try {
    FRect = boost::make_shared<MkRect[]>(FSize);
  }
  catch(std::bad_alloc &e) {
    FSize = 0;
    FRect.reset();
    throw Alloc(std::string("MkRects::MkRects(int size, boost::shared_ptr<MkRect[]> rect) - bad_alloc",e.what()));
  }
  catch(...) {
    FSize = 0;
    FRect.reset();
    throw Alloc(std::string("MkRects::MkRects(int size, boost::shared_ptr<MkRect[]> rect) - unknown exception"));
  }
  
  for (int i = 0; i < FSize; i++)
    FRect[i] = rect[i];

  return true;
}



void MkRects::Clear()
{
  FSize = 0;
  FRect.reset();
}

MkRect &MkRects::operator()(int i)
{
  if (i >= 0 && i < FSize)
    return FRect[i];
  else
    return NullRect;
}

MkRect &MkRects::operator[](int i)
{
  if (i >= 0 && i < FSize)
    return FRect[i];
  else
    return NullRect;
}

MkRects &MkRects::operator=(MkRects &a)
{
  Initialize(a.GetSize());
  for (int i = 0; i < a.GetSize(); i++)
    FRect[i] = a[i];
  return *this;
}

#ifdef __BCPLUSPLUS__
void MkRects::Draw(TObject *Sender)
{
  for (int i = 0; i < FSize; i++)
    FRect[i].Draw(Sender);
}
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
void MkRects::Draw(MkPaint *pb)
{
  for (int i = 0; i < FSize; i++)
    FRect[i].Draw(pb);
}
#endif

//---------------------------------------------------------------------------
