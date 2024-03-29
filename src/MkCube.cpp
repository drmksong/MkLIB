//---------------------------------------------------------------------------
#include "MkCube.hpp"

MkCube NullCube(NullPoint);

MkCube::MkCube()
{
   FCenter = MkPoint(0, 0);
   Psi = 0;   // degree
   Theta = 0; // degree
   XLength = 0;
   YLength = 0;
   ZLength = 0;
}

MkCube::MkCube(MkPoint &rp)
{
   FCenter = rp;
   Psi = 0;   // degree
   Theta = 0; // degree
   XLength = 0;
   YLength = 0;
   ZLength = 0;
}

bool MkCube::IsIn(MkPoint &rp)
{
   MkPoint pnt = rp;

   pnt.X -= FCenter.X;
   pnt.Y -= FCenter.Y;
   pnt.Z -= FCenter.Z;

   pnt.Rotate(0, 0, -Theta); // Ȯ�ο�.
   pnt.Rotate(0, Psi, 0);    // Ȯ�ο�.

   if (pnt.X < XLength / 2 + 0.0001 && pnt.X > -XLength / 2 - 0.0001 &&
       pnt.Y < YLength / 2 + 0.0001 && pnt.Y > -YLength / 2 - 0.0001 &&
       pnt.Z < ZLength / 2 + 0.0001 && pnt.Z > -ZLength / 2 - 0.0001)
      return true;
   else
      return false;
}
bool MkCube::IsIn(MkPoint &&rp)
{
   MkPoint pnt = rp;

   pnt.X -= FCenter.X;
   pnt.Y -= FCenter.Y;
   pnt.Z -= FCenter.Z;

   pnt.Rotate(0, 0, -Theta); // Ȯ�ο�.
   pnt.Rotate(0, Psi, 0);    // Ȯ�ο�.

   if (pnt.X < XLength / 2 + 0.0001 && pnt.X > -XLength / 2 - 0.0001 &&
       pnt.Y < YLength / 2 + 0.0001 && pnt.Y > -YLength / 2 - 0.0001 &&
       pnt.Z < ZLength / 2 + 0.0001 && pnt.Z > -ZLength / 2 - 0.0001)
      return true;
   else
      return false;
}

bool MkCube::IsInSurface(MkPoint &rp, double thick)
{
   MkPoint pnt = rp;

   pnt.X -= FCenter.X;
   pnt.Y -= FCenter.Y;
   pnt.Z -= FCenter.Z;

   pnt.Rotate(0, 0, -Theta); // Ȯ�ο�.
   pnt.Rotate(0, Psi, 0);    // Ȯ�ο�.

   if ((pnt.X < XLength / 2 + thick && pnt.X > XLength / 2 - thick) ||
       (pnt.X < -XLength / 2 + thick && pnt.X > -XLength / 2 - thick) ||
       (pnt.Y < YLength / 2 + thick && pnt.Y > YLength / 2 - thick) ||
       (pnt.Y < -YLength / 2 + thick && pnt.Y > -YLength / 2 - thick) ||
       (pnt.Z < ZLength / 2 + thick && pnt.Z > ZLength / 2 - thick) ||
       (pnt.Z < -ZLength / 2 + thick && pnt.Z > -ZLength / 2 - thick))
      return true;
   else
      return false;
}

bool MkCube::IsInSurface(MkPoint &&rp, double thick)
{
   MkPoint pnt = rp;

   pnt.X -= FCenter.X;
   pnt.Y -= FCenter.Y;
   pnt.Z -= FCenter.Z;

   pnt.Rotate(0, 0, -Theta); // Ȯ�ο�.
   pnt.Rotate(0, Psi, 0);    // Ȯ�ο�.

   if ((pnt.X < XLength / 2 + thick && pnt.X > XLength / 2 - thick) ||
       (pnt.X < -XLength / 2 + thick && pnt.X > -XLength / 2 - thick) ||
       (pnt.Y < YLength / 2 + thick && pnt.Y > YLength / 2 - thick) ||
       (pnt.Y < -YLength / 2 + thick && pnt.Y > -YLength / 2 - thick) ||
       (pnt.Z < ZLength / 2 + thick && pnt.Z > ZLength / 2 - thick) ||
       (pnt.Z < -ZLength / 2 + thick && pnt.Z > -ZLength / 2 - thick))
      return true;
   else
      return false;
}

bool MkCube::IsInSpace(MkPoint &pnt)
{
   return IsIn(pnt);
}

bool MkCube::IsInSpace(MkPoint &&pnt)
{
   return IsIn(pnt);
}


MkPoint MkCube::GetNormPoint(MkPoint &rp)
{
   MkPoint pnt = rp;

   pnt.X -= FCenter.X;
   pnt.Y -= FCenter.Y;
   pnt.Z -= FCenter.Z;

   pnt.Rotate(0, 0, -Theta); // Ȯ�ο�.
   pnt.Rotate(0, Psi, 0);    // Ȯ�ο�.

   return pnt;
}

MkPoint MkCube::GetNormPoint(MkPoint &&rp)
{
   MkPoint pnt = rp;

   pnt.X -= FCenter.X;
   pnt.Y -= FCenter.Y;
   pnt.Z -= FCenter.Z;

   pnt.Rotate(0, 0, -Theta); // Ȯ�ο�.
   pnt.Rotate(0, Psi, 0);    // Ȯ�ο�.

   return pnt;
}
double MkCube::GetNorm(MkPoint &rp)
{
   MkPoint pnt = GetNormPoint(rp);
   double x, y, z, max;
   x = fabs(pnt.X) / XLength * 2;
   y = fabs(pnt.Y) / YLength * 2;
   z = fabs(pnt.Z) / ZLength * 2;
   max = x > y ? x : y;
   max = max > z ? max : z;
   return max;
}

double MkCube::GetNorm(MkPoint &&rp)
{
   MkPoint pnt = GetNormPoint(rp);
   double x, y, z, max;
   x = fabs(pnt.X) / XLength * 2;
   y = fabs(pnt.Y) / YLength * 2;
   z = fabs(pnt.Z) / ZLength * 2;
   max = x > y ? x : y;
   max = max > z ? max : z;
   return max;
}

//-------------
//|3   2|7   6|
//|     |     |
//|0   1|4   5|
//-------------
MkPoint MkCube::operator[](int i)
{
   double x, y, z;
   x = FCenter.X + i % 4 == 0 || i % 4 == 3 ? -XLength / 2 : XLength / 2;
   y = FCenter.Y + i % 4 == 0 || i % 4 == 1 ? -YLength / 2 : YLength / 2;
   z = FCenter.Z + i < 4 ? -ZLength / 2 : ZLength / 2;

   MkPoint p(x, y, z);
   p.Rotate(0, -Psi, 0);
   p.Rotate(0, 0, Theta);
   return p;
}

bool MkCube::operator==(MkCube &rc)
{
   return FCenter == rc.FCenter && fabs(Psi - rc.Psi) < EPS && fabs(Theta - rc.Theta) < EPS &&
          fabs(XLength - rc.XLength) < EPS && fabs(YLength - rc.YLength) < EPS && fabs(ZLength - rc.ZLength) < EPS;
}

bool MkCube::operator!=(MkCube &rc)
{
   return !operator==(rc);
}

#ifdef __BCPLUSPLUS__
void MkCube::Draw(TObject *Sender)
{
   /*   TColor C;
      TPenStyle PS;
      if (String(Sender->ClassName()) == String("MkPaintBox")) {
         MkPaintBox *pb=(MkPaintBox*)Sender;
         C = pb->Canvas->Pen->Color;
         PS = pb->Canvas->Pen->Style;
         pb->Canvas->Pen->Color = Color;
   //      pb->Canvas->Pen->Style = PenStyle;

         pb->MoveTo3D((*this)[0].X,(*this)[0].Y,(*this)[0].Z);
         pb->LineTo3D((*this)[1].X,(*this)[1].Y,(*this)[1].Z);
         pb->LineTo3D((*this)[2].X,(*this)[2].Y,(*this)[2].Z);
         pb->LineTo3D((*this)[3].X,(*this)[3].Y,(*this)[3].Z);
         pb->LineTo3D((*this)[4].X,(*this)[4].Y,(*this)[4].Z);
         pb->LineTo3D((*this)[5].X,(*this)[5].Y,(*this)[5].Z);
         pb->LineTo3D((*this)[6].X,(*this)[6].Y,(*this)[6].Z);
         pb->LineTo3D((*this)[7].X,(*this)[7].Y,(*this)[7].Z);
         pb->LineTo3D((*this)[3].X,(*this)[3].Y,(*this)[3].Z);
         pb->MoveTo3D((*this)[1].X,(*this)[1].Y,(*this)[1].Z);
         pb->LineTo3D((*this)[5].X,(*this)[5].Y,(*this)[5].Z);
         pb->MoveTo3D((*this)[2].X,(*this)[2].Y,(*this)[2].Z);
         pb->LineTo3D((*this)[6].X,(*this)[6].Y,(*this)[6].Z);

         pb->Canvas->Pen->Color = C;
         pb->Canvas->Pen->Style = PS;
      }
   */
}
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
void MkCube::Draw(MkPaint *pb)
{
   pb->MoveTo3D((*this)[0].X, (*this)[0].Y, (*this)[0].Z);
   pb->LineTo3D((*this)[1].X, (*this)[1].Y, (*this)[1].Z);
   pb->LineTo3D((*this)[2].X, (*this)[2].Y, (*this)[2].Z);
   pb->LineTo3D((*this)[3].X, (*this)[3].Y, (*this)[3].Z);
   pb->LineTo3D((*this)[4].X, (*this)[4].Y, (*this)[4].Z);
   pb->LineTo3D((*this)[5].X, (*this)[5].Y, (*this)[5].Z);
   pb->LineTo3D((*this)[6].X, (*this)[6].Y, (*this)[6].Z);
   pb->LineTo3D((*this)[7].X, (*this)[7].Y, (*this)[7].Z);
   pb->LineTo3D((*this)[3].X, (*this)[3].Y, (*this)[3].Z);
   pb->MoveTo3D((*this)[1].X, (*this)[1].Y, (*this)[1].Z);
   pb->LineTo3D((*this)[5].X, (*this)[5].Y, (*this)[5].Z);
   pb->MoveTo3D((*this)[2].X, (*this)[2].Y, (*this)[2].Z);
   pb->LineTo3D((*this)[6].X, (*this)[6].Y, (*this)[6].Z);
}
#endif

//---------------------------------------------------------------------------
MkCubes::MkCubes()
{
   FSize = 0;
   FCube.reset();
}

MkCubes::MkCubes(int size)
{
   if (size <= 0)
   {
      FSize = 0;
      FCube.reset();
   }
   FSize = size;
   try
   {
      FCube = boost::make_shared<MkCube[]>(FSize);
   }

   catch (std::bad_alloc &a)
   {
      MkDebug("MkCubes::MkCubes bad_alloc thrown!!!\n");
      throw Alloc(a.what());
   }
}

MkCubes::MkCubes(int size, boost::shared_ptr<MkCube[]>cubes) 
{
   if (size <= 0) {
      FSize = 0;
      FCube.reset();
   }
   FSize = size;
   try {
      FCube = boost::make_shared<MkCube[]>(FSize);
   }
   catch (std::bad_alloc &a) {
      MkDebug("MkCubes::MkCubes bad_alloc thrown!!!\n");
      throw Alloc(a.what());
   }
   for (int i = 0; i < FSize; i++)
      FCube[i] = cubes[i];
}

MkCubes::MkCubes(MkCubes &rc)
{
   FSize = rc.FSize;

   try
   {
      FCube = boost::make_shared<MkCube[]> (FSize);
   }
   catch (std::bad_alloc &a)
   {
      MkDebug("MkCubes::MkCubes bad_alloc thrown!!!\n");
      throw Alloc(a.what());
   }
   
   for (int i = 0; i < FSize; i++)
      FCube[i] = rc.FCube[i];
}

MkCubes::~MkCubes()
{
   FSize = 0;
   FCube.reset();
}

bool MkCubes::Initialize(int size)
{
   if (size <= 0)
   {
      FSize = 0;
      FCube.reset();
      return false;
   }

   FSize = size;
   try 
   {
      FCube = boost::make_shared<MkCube[]>  (FSize);
   }
   
   catch (std::bad_alloc &a)
   {
      MkDebug("MkCubes::MkCubes bad_alloc thrown!!!\n");
      throw Alloc(a.what());
   }
   return true;
}

bool MkCubes::Initialize(int size, boost::shared_ptr<MkCube[]> fault)
{
   if (size <= 0)
   {
      FSize = 0;
      FCube.reset();
      return false;
   }

   FSize = size;
   try
   {
      FCube = boost::make_shared<MkCube[]> (FSize);
   }
   catch (std::bad_alloc &a)
   {
      MkDebug("MkCubes::MkCubes bad_alloc thrown!!!\n");
      throw Alloc(a.what());
   }
   
   for (int i = 0; i < FSize; i++)
      FCube[i] = fault[i];

   return true;
}

void MkCubes::Clear()
{
   FSize = 0;
   FCube.reset();
}

MkCube &MkCubes::operator()(int i)
{
   if (i >= 0 && i < FSize)
      return FCube[i];
   else
      return NullCube;
}

MkCube &MkCubes::operator[](int i)
{
   if (i >= 0 && i < FSize)
      return FCube[i];
   else
      return NullCube;
}

MkCubes &MkCubes::operator=(MkCubes &a)
{
   Initialize(a.GetSize());
   for (int i = 0; i < a.GetSize(); i++)
      FCube[i] = a[i];
   return *this;
}

#ifdef __BCPLUSPLUS__
void MkCubes::Draw(TObject *Sender)
{
   for (int i = 0; i < FSize; i++)
      FCube[i].Draw(Sender);
}
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
void MkCubes::Draw(MkPaint *pb)
{
   for (int i = 0; i < FSize; i++)
      FCube[i].Draw(pb);
}
#endif

//---------------------------------------------------------------------------
