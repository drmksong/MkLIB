//---------------------------------------------------------------------------
// This module is general purposed simple graphic class to store, draw,
// manipulate object. It is well suited to VCL component, but not restricted.
// It forms the base for the higher level class, such as tunnel component.
//
// Copyright (c) 1999 Myung Kyu Song, ESCO Consultant Co., Ltd.

// #pragma hdrstop

#include "MkTriangle.hpp"

#ifdef __BCPLUSPLUS__
#include <vcl.h>
#include "Dialogs.hpp"
#include "MkPaintBox.h"
#endif

#ifdef __BCPLUSPLUS__
#pragma package(smart_init)
#endif

MkTriangle NullTriangle(0);

MkTriangle::MkTriangle()
{
    StartPoint = NullPoint;
    MidPoint = NullPoint;
    EndPoint = NullPoint;
    FArea = 0;
}

MkTriangle::MkTriangle(int)
{
    StartPoint = NullPoint;
    MidPoint = NullPoint;
    EndPoint = NullPoint;
    FArea = 0;
}

MkTriangle::MkTriangle(MkPoint &sp, MkPoint &mp, MkPoint &ep)
{
    StartPoint = sp;
    MidPoint = mp;
    EndPoint = ep;
    CalArea();
}

MkTriangle::MkTriangle(MkPoint &&sp, MkPoint &&mp, MkPoint &&ep)
{
    StartPoint = sp;
    MidPoint = mp;
    EndPoint = ep;
    CalArea();
}

MkTriangle::~MkTriangle() {}

void MkTriangle::Reset(MkPoint &&sp, MkPoint &&mp, MkPoint &&ep)
{
    StartPoint = sp;
    MidPoint = mp;
    EndPoint = ep;
    CalArea();
}

void MkTriangle::Reset(MkPoint &sp, MkPoint &mp, MkPoint &ep)
{
    StartPoint = sp;
    MidPoint = mp;
    EndPoint = ep;
    CalArea();
}

void MkTriangle::Reset(MkPoint rps[3])
{
    StartPoint = rps[0];
    MidPoint = rps[1];
    EndPoint = rps[2];
    CalArea();
}

void MkTriangle::Translate(MkPoint &rp)
{
    StartPoint += rp;
    MidPoint += rp;
    EndPoint += rp;
    //   CalGrad();
    //   CalArea();
}

void MkTriangle::Translate(MkPoint &&rp)
{
    StartPoint += rp;
    MidPoint += rp;
    EndPoint += rp;
    //   CalGrad();
    //   CalArea();
}

void MkTriangle::Translate(double x, double y, double z)
{
    MkPoint rp(x, y, z);
    Translate(rp);
}

void MkTriangle::CalArea()
{
    CalArea2D();
    CalArea3D();
}

void MkTriangle::CalArea2D()
{
    double a, b, c, s;

    a = sqrt(pow(StartPoint.X - MidPoint.X, 2) + pow(StartPoint.Y - MidPoint.Y, 2));
    b = sqrt(pow(EndPoint.X - MidPoint.X, 2) + pow(EndPoint.Y - MidPoint.Y, 2));
    c = sqrt(pow(StartPoint.X - EndPoint.X, 2) + pow(StartPoint.Y - EndPoint.Y, 2));

    s = (a + b + c) / 2;

    if (s > a)
    {
        if (s > b)
        {
            if (s > c)
            {
                FArea = sqrt(s * (s - a) * (s - b) * (s - c));
            }
        }
    }
    else
        FArea = 0;
}

// ref: https://math.stackexchange.com/questions/128991/how-to-calculate-the-area-of-a-3d-triangle
// v1 = vector(StartPoint, MidPoint)
// v2 = vector(StartPoint, EndPoint)
// u = v1 x v2
// u =(y1z2−y2z1)i−(x1z2−x2z1)j+(x1y2−x2y1)k
// area = |u|/2 = sqrt((y1z2−y2z1)^2+(x1z2−x2z1)^2+(x1y2−x2y1)^2)/2

void MkTriangle::CalArea3D() // TODO: implement this !!!
{
    MkVector<double> v1, v2, u;
    MkLine l1, l2;
    l1.SetLine(StartPoint, MidPoint);
    l2.SetLine(StartPoint, EndPoint);
    v1 = l1.GetVector()*l1.GetLength();
    v2 = l2.GetVector()*l2.GetLength();
    
    v1.Cross(v2, u); // u = v1 x v2
    FArea3D = u.GetLength() / 2;
}

void MkTriangle::CalGrad()
{
    A[0] = MidPoint.X * EndPoint.Y - EndPoint.X * MidPoint.Y;
    A[1] = EndPoint.X * StartPoint.Y - StartPoint.X * EndPoint.Y;
    A[2] = StartPoint.X * MidPoint.Y - MidPoint.X * StartPoint.Y;
    B[0] = MidPoint.Y - EndPoint.Y;
    B[1] = EndPoint.Y - StartPoint.Y;
    B[2] = StartPoint.Y - MidPoint.Y;
    C[0] = EndPoint.X - MidPoint.X;
    C[1] = StartPoint.X - EndPoint.X;
    C[2] = MidPoint.X - StartPoint.X;
    AR2 = MidPoint.X * EndPoint.Y + EndPoint.X * StartPoint.Y + StartPoint.X * MidPoint.Y - MidPoint.X * StartPoint.Y - EndPoint.X * MidPoint.Y - StartPoint.X * EndPoint.Y;
    GradX = (B[0] * StartPoint.Z + B[1] * MidPoint.Z + B[2] * EndPoint.Z) / AR2;
    GradY = (C[0] * StartPoint.Z + C[1] * MidPoint.Z + C[2] * EndPoint.Z) / AR2;
}

void MkTriangle::CalRadius()
{
    double delta, psi, X, Y, L;
    MkMatrix4_d mat;
    MkVector<double> norm, v;
    MkVector<double> v1, v2;
    MkPoint pnt[3], p, p2, ip;
    MkLine l[2];

    norm = GetNormal();
    norm.Normalize();

    v1 = FirstLine().GetVector();
    v1.Normalize();
    v2 = SecondLine().GetVector();
    v2.Normalize();

    norm.Cross(v1, v);
    p = FirstLine().GetMiddlePoint();
    p2.SetPoint(p.X + v[0], p.Y + v[1], p.Z + v[2]);
    l[0].SetLine(p, p2);

    norm.Cross(v2, v);
    p = SecondLine().GetMiddlePoint();
    p2.SetPoint(p.X + v[0], p.Y + v[1], p.Z + v[2]);
    l[1].SetLine(p, p2);

    ip = l[0] & l[1];

    double len1, len2;
    len1 = CalDist(StartPoint, ip);
    len2 = CalDist(EndPoint, ip);

    if (fabs(len1 - len2) < EPS)
        FRadius = len1;
    else
        FRadius = (len1 + len2) / 2;
}

void MkTriangle::CalNormal()
{
    MkVector<double> v1, v2;
    v1 = FirstLine().GetVector();
    v1.Normalize();
    v2 = SecondLine().GetVector();
    v2.Normalize();

    v1.Cross(v2, FNormal);
    FNormal.Normalize();
}

double MkTriangle::GetXGrad()
{
    CalGrad();
    return GradX;
}

double MkTriangle::GetYGrad()
{
    CalGrad();
    return GradY;
}

MkVector<double> &MkTriangle::GetNormal()
{
    CalNormal();
    return FNormal;
}

double MkTriangle::GetRadius()
{
    CalRadius();
    return FRadius;
}

MkPoint &MkTriangle::operator[](int i)
{
    if (i == 0)
        return StartPoint;
    else if (i == 1)
        return MidPoint;
    else if (i == 2)
        return EndPoint;
    else
    {
        MkDebug("MkTriangle::operator[] Bad Index");
        return NullPoint;
    }
}

MkLine &MkTriangle::operator()(int i)
{
    if (i == 0)
        return FirstLine();
    else if (i == 1)
        return SecondLine();
    else if (i == 2)
        return LastLine();
    else
    {
        MkDebug("MkTriangle::operator() Bad Index");
        return NullLine;
    }
}

double MkTriangle::operator()(double x, double y)
{
    CalGrad();
    double result = 0;
    result = A[0] * StartPoint.Z + A[1] * MidPoint.Z + A[2] * EndPoint.Z;
    result += (B[0] * StartPoint.Z + B[1] * MidPoint.Z + B[2] * EndPoint.Z) * x;
    result += (C[0] * StartPoint.Z + C[1] * MidPoint.Z + C[2] * EndPoint.Z) * y;
    result /= AR2;

    return result;
}

MkLine &MkTriangle::FirstLine()
{
    static MkLine fl;
    fl.SetLine(StartPoint, MidPoint);
    return fl;
}

MkLine &MkTriangle::SecondLine()
{
    static MkLine sl;
    sl.SetLine(MidPoint, EndPoint);

    return sl;
}

MkLine &MkTriangle::LastLine()
{
    static MkLine ll;
    ll.SetLine(EndPoint, StartPoint);
    return ll;
}

bool MkTriangle::operator&&(MkTriangle &rt)
{
    bool flag = false;
    for (int i = 0; i < 3 && !flag; i++)
        for (int j = 0; j < 3 && !flag; j++)
            flag = flag || ((*this)(i) && rt(j));
    return flag;
}

bool MkTriangle::operator&&(MkTriangle &&rt)
{
    bool flag = false;
    for (int i = 0; i < 3 && !flag; i++)
        for (int j = 0; j < 3 && !flag; j++)
            flag = flag || ((*this)(i) && rt(j));
    return flag;
}

bool MkTriangle::operator==(MkTriangle &rt)
{
    bool flag = true;
    for (int i = 0; i < 3 && flag; i++)
        flag = flag && ((*this)[i] == rt[i]);
    return flag;
}

bool MkTriangle::operator==(MkTriangle &&rt)
{
    bool flag = true;
    for (int i = 0; i < 3 && flag; i++)
        flag = flag && ((*this)[i] == rt[i]);
    return flag;
}

bool MkTriangle::operator!=(MkTriangle &rt)
{
    bool flag = true;
    for (int i = 0; i < 3 && flag; i++)
        flag = flag && ((*this)[i] != rt[i]);
    return flag;
}

bool MkTriangle::operator!=(MkTriangle &&rt)
{
    bool flag = true;
    for (int i = 0; i < 3 && flag; i++)
        flag = flag && ((*this)[i] != rt[i]);
    return flag;
}

MkTriangle &MkTriangle::operator=(MkTriangle &rt)
{
    StartPoint = rt.StartPoint;
    MidPoint = rt.MidPoint;
    EndPoint = rt.EndPoint;
#ifdef __BCPLUSPLUS__
    Color = rt.Color;
#endif
    CalArea();
    return (*this);
}

MkTriangle &MkTriangle::operator=(MkTriangle &&rt)
{
    StartPoint = rt.StartPoint;
    MidPoint = rt.MidPoint;
    EndPoint = rt.EndPoint;
#ifdef __BCPLUSPLUS__
    Color = rt.Color;
#endif
    CalArea();
    return (*this);
}

bool MkTriangle::isIntersect(MkTriangle &rt)
{
    return *this && rt;
}

bool MkTriangle::isIntersect(MkTriangle &&rt)
{
    return *this && rt;
}

bool MkTriangle::isIn(double x, double y)
{
    bool flag = true;
    MkPoint rp(x, y);
    for (int i = 0; i < 3; i++)
    {
        flag = flag && (*this)(i)*rp;
    }
    return flag;
}

bool MkTriangle::isIn(MkPoint &rp)
{
    bool flag = true;
    for (int i = 0; i < 3; i++)
    {
        flag = flag && (*this)(i)*rp;
    }
    return flag;
}

bool MkTriangle::isIn(MkPoint &&rp)
{
    bool flag = true;
    for (int i = 0; i < 3; i++)
    {
        flag = flag && (*this)(i)*rp;
    }
    return flag;
}

bool MkTriangle::isInside(MkPoint &rp)
{
    MkLine l[2];
    MkVector<double> norm, vec, v[2];
    if (isIn(rp))
        return true;
    norm = GetNormal();

    l[0].SetLine(rp, StartPoint);
    l[1].SetLine(rp, MidPoint);

    v[0] = l[0].GetVector();
    v[1] = l[1].GetVector();

    v[0].Cross(v[1], vec);

    return norm == vec;
}

bool MkTriangle::isInside(MkPoint &&rp)
{
    MkLine l[2];
    MkVector<double> norm, vec, v[2];
    if (isIn(rp))
        return true;
    norm = GetNormal();

    l[0].SetLine(rp, StartPoint);
    l[1].SetLine(rp, MidPoint);

    v[0] = l[0].GetVector();
    v[1] = l[1].GetVector();

    v[0].Cross(v[1], vec);

    return norm == vec;
}

bool MkTriangle::isValid()
{
    return (*this)(0) * (*this)(1) > 0 ? true : false;
}

double MkTriangle::CrossProduct()
{
    return (*this)(0) * (*this)(1);
}

#ifdef __BCPLUSPLUS__
/*void MkTriangle::Draw(TObject *Sender)
{
    TColor C;
    if (String(Sender->ClassName()) == String("MkPaintBox")) {
       MkPaintBox *pb=(MkPaintBox*)Sender;

       C = pb->Canvas->Pen->Color;
       pb->Canvas->Pen->Color = Color;

       FirstLine().Draw(pb);
       SecondLine().Draw(pb);
       LastLine().Draw(pb);

       pb->Canvas->Pen->Color = C;
    }
} */
#endif

#ifdef __BCPLUSPLUS__
void MkTriangle::Draw(TObject *Sender)
{
    for (int i = 0; i < 3; i++)
        (*this)(i).Draw(Sender);
}
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
void MkTriangle::Draw(MkPaint *pb)
{
    for (int i = 0; i < 3; i++)
        (*this)(i).Draw(pb);
}
#endif
//---------------------------------------------------------------------------
MkTriangles::MkTriangles(int size)
{

    if (size <= 0)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();
        throw Alloc(std::string("MkTriangles::MkTriangles(int size)-size <= 0"));
    }

    FSizeOfArray = FSize = size;

    try
    {
        FTriangle = boost::make_shared<MkTriangle[]>(FSize);
    }
    catch (std::bad_alloc)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();
        throw Alloc(std::string("MkTriangles::MkTriangles(int size)-bad_alloc"));
    }
    catch (...)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();
        throw Alloc(std::string("MkTriangles::MkTriangles(int size)-unknown exception"));
    }
}

MkTriangles::MkTriangles(int size, boost::shared_ptr<MkTriangle[]> tri)
{
    if (size <= 0)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();
        throw Alloc(std::string("MkTriangles::MkTriangles(int size)-size <= 0"));
    }

    FSizeOfArray = FSize = size;

    try
    {
        FTriangle = boost::make_shared<MkTriangle[]>(FSize);
    }
    catch (std::bad_alloc)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();
        throw Alloc(std::string("MkTriangles::MkTriangles(int size)-bad_alloc"));
    }
    catch (...)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();
        throw Alloc(std::string("MkTriangles::MkTriangles(int size)-unknown exception"));
    }

    for (int i = 0; i < FSize; i++)
        FTriangle[i] = tri[i];
}

MkTriangles::MkTriangles(MkTriangles &tri)
{
    FSizeOfArray = FSize = tri.FSize;
    try
    {
        FTriangle = boost::make_shared<MkTriangle[]>(FSize);
    }
    catch (std::bad_alloc)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();
        throw Alloc(std::string("MkTriangles::MkTriangles(int size)-bad_alloc"));
    }
    catch (...)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();
        throw Alloc(std::string("MkTriangles::MkTriangles(int size)-unknown exception"));
    }

    for (int i = 0; i < FSize; i++)
        FTriangle[i] = tri.FTriangle[i];
}

bool MkTriangles::Initialize(int size)
{
    if (size <= 0)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();
        throw Alloc(std::string("MkTriangles::Initialize(int size)-size <= 0"));
    }

    FSizeOfArray = FSize = size;

    try
    {
        FTriangle = boost::make_shared<MkTriangle[]>(FSize);
    }
    catch (std::bad_alloc)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();
        throw Alloc(std::string("MkTriangles::Initialize(int size)-bad_alloc"));
    }
    catch (...)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();
        throw Alloc(std::string("MkTriangles::Initialize(int size)-unknown exception"));
    }
    return true;
}

bool MkTriangles::Initialize(int size, boost::shared_ptr<MkTriangle[]> tri)
{
    if (size <= 0)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();
        throw Alloc(std::string("MkTriangles::Initialize(int size)-size <= 0"));
    }

    FSizeOfArray = FSize = size;

    try
    {
        FTriangle = boost::make_shared<MkTriangle[]>(FSize);
    }
    catch (std::bad_alloc)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();
        throw Alloc(std::string("MkTriangles::Initialize(int size)-bad_alloc"));
    }
    catch (...)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();
        throw Alloc(std::string("MkTriangles::Initialize(int size)-unknown exception"));
    }

    for (int i = 0; i < FSize; i++)
        FTriangle[i] = tri[i];

    return true;
}

bool MkTriangles::Initialize(MkTriangles &tri)
{
    FSizeOfArray = FSize = tri.FSize;
    try
    {
        FTriangle = boost::make_shared<MkTriangle[]>(FSize);
    }
    catch (std::bad_alloc)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();
        throw Alloc(std::string("MkTriangles::Initialize(int size)-bad_alloc"));
    }
    catch (...)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();
        throw Alloc(std::string("MkTriangles::Initialize(int size)-unknown exception"));
    }

    for (int i = 0; i < FSize; i++)
        FTriangle[i] = tri.FTriangle[i];

    return true;
}

void MkTriangles::Clear()
{
    FSizeOfArray = FSize = 0;
    FTriangle.reset();
}

int MkTriangles::Grow(int delta)
{
    int i;
    boost::shared_ptr<MkTriangle[]> tri;

    try
    {
        tri = boost::make_shared<MkTriangle[]>(FSizeOfArray + delta);
    }
    catch (std::bad_alloc)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();

        return FSizeOfArray;
    }
    catch (...)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();

        return FSizeOfArray;
    }

    for (i = 0; i < FSize; i++)
        tri[i] = FTriangle[i];
    for (i = FSize; i < FSizeOfArray + delta; i++)
        tri[i] = NullTriangle;

    FTriangle = tri;
    FSizeOfArray = FSizeOfArray + delta;
    return FSizeOfArray;
}

int MkTriangles::Shrink(int delta)
{
    int i;
    boost::shared_ptr<MkTriangle[]> tri;

    try
    {
        tri = boost::make_shared<MkTriangle[]>(FSizeOfArray - delta);
    }
    catch (std::bad_alloc)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();

        return FSizeOfArray;
    }
    catch (...)
    {
        FSizeOfArray = FSize = 0;
        FTriangle.reset();

        return FSizeOfArray;
    }

    for (i = 0; i < FSize; i++)
        tri[i] = FTriangle[i];
    for (i = FSize; i < FSizeOfArray - delta; i++)
        tri[i] = NullTriangle;

    FTriangle = tri;
    FSizeOfArray = FSizeOfArray - delta;
    return FSizeOfArray;
}

bool MkTriangles::Add(MkTriangle &point)
{
    if (FSize == FSizeOfArray)
        Grow(FSize - FSizeOfArray + 10);
    if (FSize == FSizeOfArray)
        return false;

    FSize++;
    FTriangle[FSize - 1] = point;
    return true;
}

bool MkTriangles::Add(MkTriangle &&point)
{
    if (FSize == FSizeOfArray)
        Grow(FSize - FSizeOfArray + 10);
    if (FSize == FSizeOfArray)
        return false;

    FSize++;
    FTriangle[FSize - 1] = point;
    return true;
}

bool MkTriangles::Delete(MkTriangle &point)
{
    int i;
    for (i = 0; i < FSize; i++)
    {
        if (FTriangle[i] == point)
            break;
    }
    if (i == FSize)
        return false;
    if (FTriangle[i] == point)
    {
        for (int j = i; j < FSize - 1; j++)
            FTriangle[j] = FTriangle[j + 1];
    }
    FSize--;
    FTriangle[FSize] = NullTriangle;
    return true;
}

bool MkTriangles::Delete(MkTriangle &&point)
{
    int i;
    for (i = 0; i < FSize; i++)
    {
        if (FTriangle[i] == point)
            break;
    }
    if (i == FSize)
        return false;
    if (FTriangle[i] == point)
    {
        for (int j = i; j < FSize - 1; j++)
            FTriangle[j] = FTriangle[j + 1];
    }
    FSize--;
    FTriangle[FSize] = NullTriangle;
    return true;
}

int MkTriangles::SaveUCD(char *filename)
{
    FILE *fp;
    int i, j;
    fp = fopen(filename, "w");
    if (!fp)
        return -1; // File creation error
    fprintf(fp, "%d %d %d %d %d\n", FSize * 3, FSize, 1, 0, 0);
    for (i = 0; i < FSize; i++)
        for (j = 0; j < 3; j++)
            fprintf(fp, "%5d %10.5f %10.5f %10.5f\n", i * 3 + j + 1,
                    FTriangle[i][j].X, FTriangle[i][j].Y, FTriangle[i][j].Z);
    for (i = 0; i < FSize; i++)
        fprintf(fp, "%5d 1 tri %5d %5d %5d\n", i + 1, i * 3 + 1, i * 3 + 2, i * 3 + 3);
    fprintf(fp, "1 1\n");
    fprintf(fp, "None, degree \n");
    for (i = 0; i < FSize; i++)
        for (j = 0; j < 3; j++)
            fprintf(fp, "%5d %10d\n", i * 3 + j + 1, 1);
    // fprintf(fp, "%5d %10.5f\n", i * 3 + j + 1, 1);

    fclose(fp);
    return 0;
}

int MkTriangles::SaveLID(char *filename)
{
    FILE *fp;
    int i, j;
    fp = fopen(filename, "w");
    if (!fp)
        return -1; // File creation error

    fprintf(fp, "%d\n", FSize);

    for (i = 0; i < FSize; i++)
    {
        for (j = 0; j < 3; j++)
            fprintf(fp, "%9.3f %9.3f %9.3f ",
                    FTriangle[i][j].X, FTriangle[i][j].Y, FTriangle[i][j].Z);
        fprintf(fp, "%9.3f %9.3f %9.3f\n",
                FTriangle[i][2].X, FTriangle[i][2].Y, FTriangle[i][2].Z);
    }

    fclose(fp);
    return 0;
}

MkTriangle &MkTriangles::operator[](int i)
{
    if (FSizeOfArray == 0)
        return NullTriangle;
    if (i >= FSize && i < FSizeOfArray)
        FSize = i + 1;

    if (i >= 0 && i < FSize)
        return FTriangle[i];
    else
        return NullTriangle;
}

MkTriangles &MkTriangles::operator=(MkTriangles &Triangles)
{
    int i;
    FSize = Triangles.FSize;
    FSizeOfArray = Triangles.FSizeOfArray;
    this->FTriangle = boost::make_shared<MkTriangle[]>(FSizeOfArray);

    for (i = 0; i < FSize; i++)
        this->FTriangle[i] = Triangles.FTriangle[i];
    for (i = FSize; i < FSizeOfArray; i++)
        this->FTriangle[i] = NullTriangle;

    return *this;
}

#ifdef __BCPLUSPLUS__
void MkTriangles::Draw(TObject *Sender)
{
    for (int i = 0; i < FSize; i++)
        FTriangle[i].Draw(Sender);
}
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
void MkTriangles::Draw(MkPaint *pb)
{
    for (int i = 0; i < FSize; i++)
        FTriangle[i].Draw(pb);
}
#endif

//---------------------------------------------------------------------------
