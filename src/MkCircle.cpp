//---------------------------------------------------------------------------
// This module is general purposed simple graphic class to store, draw,
// manipulate object. It is well suited to VCL component, but not restricted.
// It forms the base for the higher level class, such as tunnel component.
//
// Copyright (c) 1999 Myung Kyu Song, ESCO Consultant Co., Ltd.
#include "MkCircle.hpp"

MkCircle NullCircle(0);
MkArc NullArc(0);
//---------------------------------------------------------------------------
MkCircle::MkCircle()
{
    FCP.X = 0;
    FCP.Y = 0;
#ifdef __BCPLUSPLUS__
    Color = clBlack;
#endif
    FRadius = 0;
}

MkCircle::MkCircle(int)
{
    FCP.X = 0;
    FCP.Y = 0;
    FRadius = 0;
}

MkCircle::MkCircle(double cx, double cy, double radius)
{
    FCP.X = cx;
    FCP.Y = cy;
    FRadius = radius;
    CalArea();
}

MkCircle::MkCircle(MkPoint &cp, double radius)
{
    FCP = cp;
    FRadius = radius;
    CalArea();
}

MkCircle::MkCircle(MkPoint &&cp, double radius)
{
    FCP = cp;
    FRadius = radius;
    CalArea();
}

#ifdef __BCPLUSPLUS__
MkCircle::MkCircle(double cx, double cy, double radius, TColor C)
{
    FCP.X = cx;
    FCP.Y = cy;
    FRadius = radius;
    Color = C;
    CalArea();
}

MkCircle::MkCircle(MkPoint cp, double radius, TColor C)
{
    FCP = cp;
    FRadius = radius;
    Color = C;
    CalArea();
}
#endif

void MkCircle::SetCircle(double cx, double cy, double radius)
{
    FCP.X = cx;
    FCP.Y = cy;
    FRadius = radius;
    CalArea();
}

void MkCircle::SetCircle(MkPoint &cp, double radius)
{
    FCP = cp;
    FRadius = radius;
    CalArea();
}

void MkCircle::SetCircle(MkPoint &&cp, double radius)
{
    FCP = cp;
    FRadius = radius;
    CalArea();
}
#ifdef __BCPLUSPLUS__
void MkCircle::SetCircle(double cx, double cy, double radius, TColor C)
{
    FCP.X = cx;
    FCP.Y = cy;
    FRadius = radius;
    Color = C;
    CalArea();
}

void MkCircle::SetCircle(MkPoint cp, double radius, TColor C)
{
    FCP = cp;
    FRadius = radius;
    Color = C;
    CalArea();
}
#endif

void MkCircle::CalArea()
{
    FCircleArea = M_PI * FRadius * FRadius;
}

void MkCircle::SetCenter(double cx, double cy)
{
    FCP.X = cx;
    FCP.Y = cy;
}

void MkCircle::SetCenter(MkPoint &cp)
{
    FCP = cp;
}

void MkCircle::SetCenter(MkPoint &&cp)
{
    FCP = cp;
}

void MkCircle::SetRadius(double radius)
{
    FRadius = radius;
    CalArea();
}

bool MkCircle::IsInSurface(MkPoint &pnt, double thick)
{
    double d;
    d = CalDist(FCP, pnt);
    if (FRadius - thick < d && d < FRadius + thick)
        return true;
    else
        return false;
}

bool MkCircle::IsInSpace(MkPoint &pnt)
{
    double d;
    d = CalDist(FCP, pnt);
    if (d < FRadius)
        return true;
    else
        return false;
}

MkPoint &MkCircle::operator[](int i)
{
    if (i == 0)
        return FCP;
    else
        return NullPoint;
}

MkCircle &MkCircle::operator=(MkCircle &rc)
{
    this->MkShape::operator=((MkShape &)rc);
    FCP.X = rc.FCP.X;
    FCP.Y = rc.FCP.Y;
    FRadius = rc.FRadius;
#ifdef __BCPLUSPLUS__
    Color = rc.Color;
#endif
    CalArea();
    return (*this);
}

bool MkCircle::operator&&(MkLine &rl)
{
    double xn1, yn1, xn2, yn2;
    double d;
    d = fabs(rl.GetA() * FCP.X + rl.GetB() * FCP.Y - rl.GetC()) / sqrt(rl.GetA() * rl.GetA() + rl.GetB() * rl.GetB());

    if (d > FRadius)
        return false;
    double r2 = FRadius * FRadius;
    if (rl.GetB() < FTOL)
    {
        double tmp;
        double B2, A2, C2, AC, Cx2, Cy2;
        B2 = rl.GetB() * rl.GetB();
        C2 = rl.GetC() * rl.GetC();
        A2 = rl.GetA() * rl.GetA();
        Cx2 = FCP.X * FCP.X;
        Cy2 = FCP.Y * FCP.Y;

        AC = (-2 * FCP.X + 2 * FCP.Y * rl.GetA() / rl.GetB() - 2 * rl.GetA() * rl.GetC() / B2);

        tmp = (AC * AC - 4 * (1 + A2 / B2) * (Cx2 + Cy2 - r2 + C2 / B2 - 2 * FCP.Y * rl.GetC() / rl.GetB()));
        if (tmp < 0)
            return false;
        tmp = sqrt(tmp);

        xn1 = (-AC + tmp) / (2 * (1 + A2 / B2));
        yn1 = -rl.GetA() / rl.GetB() * xn1 + rl.GetC() / rl.GetB();
        xn2 = (-AC - tmp) / (2 * (1 + A2 / B2));
        yn2 = -rl.GetA() / rl.GetB() * xn2 + rl.GetC() / rl.GetB();
    }
    else
    {
        xn1 = rl.GetC() / rl.GetA();
        xn2 = rl.GetC() / rl.GetA();
        yn1 = FCP.Y + sqrt(r2 - (xn1 - FCP.X) * (xn1 - FCP.X));
        yn2 = FCP.Y - sqrt(r2 - (xn2 - FCP.X) * (xn2 - FCP.X));
    }

    if (rl.IsIn(xn1, yn1))
    {
        if (rl.IsIn(xn2, yn2))
            return true;
        else
            return true;
    }

    else if (rl.IsIn(xn2, yn2))
        return true;
    else
        return false;
}

MkPoints &MkCircle::operator&(MkLine &rl)
{
    static MkPoints rps;
    double xn1, yn1, xn2, yn2;

    double d;
    d = fabs(rl.GetA() * FCP.X + rl.GetB() * FCP.Y - rl.GetC()) / sqrt(rl.GetA() * rl.GetA() + rl.GetB() * rl.GetB());

    if (d > FRadius)
        return NullPoints;
    double r2 = FRadius * FRadius;
    if (rl.GetB() < FTOL)
    {
        double tmp;
        double B2, A2, C2, AC, Cx2, Cy2;
        B2 = rl.GetB() * rl.GetB();
        C2 = rl.GetC() * rl.GetC();
        A2 = rl.GetA() * rl.GetA();
        Cx2 = FCP.X * FCP.X;
        Cy2 = FCP.Y * FCP.Y;

        AC = (-2 * FCP.X + 2 * FCP.Y * rl.GetA() / rl.GetB() - 2 * rl.GetA() * rl.GetC() / B2);

        tmp = (AC * AC - 4 * (1 + A2 / B2) * (Cx2 + Cy2 - r2 + C2 / B2 - 2 * FCP.Y * rl.GetC() / rl.GetB()));
        if (tmp < 0)
            return NullPoints;
        tmp = sqrt(tmp);

        xn1 = (-AC + tmp) / (2 * (1 + A2 / B2));
        yn1 = -rl.GetA() / rl.GetB() * xn1 + rl.GetC() / rl.GetB();
        xn2 = (-AC - tmp) / (2 * (1 + A2 / B2));
        yn2 = -rl.GetA() / rl.GetB() * xn2 + rl.GetC() / rl.GetB();
    }
    else
    {
        xn1 = rl.GetC() / rl.GetA();
        xn2 = rl.GetC() / rl.GetA();
        yn1 = FCP.Y + sqrt(r2 - (xn1 - FCP.X) * (xn1 - FCP.X));
        yn2 = FCP.Y - sqrt(r2 - (xn2 - FCP.X) * (xn2 - FCP.X));
    }

    if (rl.IsIn(xn1, yn1))
    {

        if (rl.IsIn(xn2, yn2))
        {
            rps.Add(MkPoint(xn1, yn1));
            rps.Add(MkPoint(xn2, yn2));
            return rps;
        }
        else
        {
            rps.Add(MkPoint(xn1, yn1));
            return rps;
        }
    }

    else if (rl.IsIn(xn2, yn2))
    {
        static MkPoints rps(1);
        rps[0] = MkPoint(xn2, yn2);
        return rps;
    }
    else
        return NullPoints;
}

MkPoints &MkCircle::operator&(MkPoint &rp) // �������ϱ�
{
    double a, b, c;
    double xp, yp;
    double x0, y0;
    double A, A2;
    double r, r2;
    double g, g2;

    xp = rp.X - FCP.X;
    yp = rp.Y - FCP.Y;
    x0 = 0;
    y0 = 0;
    r = FRadius;
    r2 = r * r;

    if (MkLine(FCP, rp).GetLength() < FRadius)
        return NullPoints;

    FRealPoints.Initialize(2);
    if (fabs(x0 - xp) < FTOL)
    {
        double dy = yp - y0;
        FRealPoints[0].Y = FRealPoints[1].Y = -r2 / dy + FCP.Y;
        FRealPoints[0].X = x0 + sqrt(r2 - (r2 / dy + y0) * (r2 / dy + y0)) + FCP.X;
        FRealPoints[1].X = x0 + sqrt(r2 - (r2 / dy + y0) * (r2 / dy + y0)) + FCP.X;
    }

    else if (fabs(y0 - yp) < FTOL)
    {
        double dx = xp - x0;
        FRealPoints[0].X = FRealPoints[1].X = -r2 / dx + FCP.X;
        FRealPoints[0].Y = y0 + sqrt(r2 - (r2 / dx + x0) * (r2 / dx + x0)) + FCP.Y;
        FRealPoints[1].Y = y0 + sqrt(r2 - (r2 / dx + x0) * (r2 / dx + x0)) + FCP.Y;
    }
    else
    {
        g = (xp - x0) / (yp - y0);
        g2 = g * g;
        A = r2 / (xp - x0) - y0 / g;
        A2 = A * A;

        a = (1 + g2);
        b = -2 * (x0 + A * g2);
        c = x0 * x0 + A2 * g2 - r2;
        if (b * b - 4 * a * c <= FTOL)
        {
            FRealPoints.Clear();
            return FRealPoints;
        }
        FRealPoints[0].X = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
        FRealPoints[0].Y = -FRealPoints[0].X * g + r2 / (yp - y0);
        FRealPoints[1].X = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
        FRealPoints[1].Y = -FRealPoints[1].X * g + r2 / (yp - y0);
    }
    FRealPoints[0] += FCP;
    FRealPoints[1] += FCP;

    return FRealPoints;
}

bool MkCircle::operator==(MkCircle &c)
{
    return FCP == c.FCP && fabs(FRadius - c.FRadius) < EPS &&
           fabs(FCircleArea - c.FCircleArea) < EPS && FRealPoints == c.FRealPoints;
}

bool MkCircle::operator!=(MkCircle &c)
{
    return !operator==(c);
}

#ifdef __BCPLUSPLUS__
void MkCircle::Draw(TObject *Sender)
{
    TColor C;
    if (String(Sender->ClassName()) == String("MkPaintBox"))
    {
        MkPaintBox *pb = (MkPaintBox *)Sender;
        MkPoint cp = GetCenter();
        C = pb->Canvas->Pen->Color;
        pb->Canvas->Pen->Color = Color;
        pb->Circle2D(cp.X, cp.Y, GetRadius());
        pb->Canvas->Pen->Color = C;
    }
}
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
void MkCircle::Draw(MkPaint *pb)
{
    MkPoint cp;
    cp = GetCenter();
    pb->Circle2D(cp.X, cp.Y, GetRadius());
}
#endif
//---------------------------------------------------------------------------
MkCircles::MkCircles(int size)
{
    //  try {
    if (size <= 0)
    {
        MkDebug("::MkCircles - MkCircles(int size)");
        return;
    }

    FSize = size;
    FCircle = new MkCircle[FSize];
    //  }
    //  catch () {
    //    ShowMessage(AnsiString(E.ClassName())+ E.Message);
    //  }
}

void MkCircles::Initialize(int size)
{
    Clear();
    FSize = size;
    if (FSize == 0)
    {
        FCircle = NULL;
        return;
    }
    FCircle = new MkCircle[FSize];
}

void MkCircles::Clear()
{
    FSize = 0;
    if (FCircle)
        delete[] FCircle;
    FCircle = NULL;
}

MkCircle &MkCircles::operator[](int i)
{
    if (i >= 0 && i < FSize)
        return FCircle[i];
    else
        return NullCircle;
}

MkCircles &MkCircles::operator=(MkCircles &circles)
{
    int i;
    FSize = circles.FSize;
    this->FCircle = new MkCircle[FSize];

    for (i = 0; i < FSize; i++)
        this->FCircle[i] = circles.FCircle[i];

    return *this;
}

#ifdef __BCPLUSPLUS__
void MkCircles::Draw(TObject *Sender)
{
    for (int i = 0; i < FSize; i++)
        FCircle[i].Draw(Sender);
}
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
void MkCircles::Draw(MkPaint *pb)
{
    for (int i = 0; i < FSize; i++)
        FCircle[i].Draw(pb);
}
#endif

//---------------------------------------------------------------------------
MkArc::MkArc(int)
{
    FCP.X = 0;
    FCP.Y = 0;
    FRadius = 0;
}

MkArc::MkArc(double cx, double cy, double radius, double start_ang, double end_ang)
    : MkCircle(cx, cy, radius)
{
    FStartAng = start_ang;
    FEndAng = end_ang;
    CalStartPoint();
    CalEndPoint();
}

MkArc::MkArc(MkPoint &cp, double radius, double start_ang, double end_ang)
    : MkCircle(cp, radius)
{
    FStartAng = start_ang;
    FEndAng = end_ang;
    CalStartPoint();
    CalEndPoint();
}

MkArc::MkArc(MkPoint &&cp, double radius, double start_ang, double end_ang)
    : MkCircle(cp, radius)
{
    FStartAng = start_ang;
    FEndAng = end_ang;
    CalStartPoint();
    CalEndPoint();
}

#ifdef __BCPLUSPLUS__
MkArc::MkArc(double cx, double cy, double radius, double start_ang, double end_ang, TColor C)
    : MkCircle(cx, cy, radius)
{
    FStartAng = start_ang;
    FEndAng = end_ang;
    Color = C;
    CalStartPoint();
    CalEndPoint();
}

MkArc::MkArc(MkPoint cp, double radius, double start_ang, double end_ang, TColor C)
    : MkCircle(cp, radius)
{
    FStartAng = start_ang;
    FEndAng = end_ang;
    Color = C;
    CalStartPoint();
    CalEndPoint();
}
#endif

MkArc::MkArc() : MkCircle()
{
    FStartAng = 0;
    FEndAng = 0;
}

MkArc::MkArc(MkPoint &p1, MkPoint &p2, MkLine &line)
{
    MkLine rl1, rl2;
    MkPoint rp1;

    rl1 = MkLine(p1, p2);
    rl2 = !rl1;
    rp1 = line & rl2;
    int cnt = 0;
    while (rp1 == NullPoint && cnt < 20)
    {
        line.Extend(2);
        rp1 = line & rl2;
        cnt++;
    }
    MkLine rl3 = MkLine(rp1, p1);
    MkLine rl4 = MkLine(rp1, p2);

    double len1 = rl3.GetLength();
    double len2 = rl4.GetLength();
    double theta1 = rl3.GetTheta();
    double theta2 = rl4.GetTheta();

    if (fabs(len1 - len2) < EPS)
        *this = NullArc;
    if (cnt == 20 && rp1 == NullPoint)
        *this = NullArc;
    else
    {
        SetCenter(rp1);
        SetRadius(len1);
        SetStartAng(theta1);
        SetEndAng(theta2);
        CalStartPoint();
        CalEndPoint();
    }
}

MkArc::MkArc(MkPoint &&p1, MkPoint &&p2, MkLine &&line)
{
    MkLine rl1, rl2;
    MkPoint rp1;

    rl1 = MkLine(p1, p2);
    rl2 = !rl1;
    rp1 = line & rl2;
    int cnt = 0;
    while (rp1 == NullPoint && cnt < 20)
    {
        line.Extend(2);
        rp1 = line & rl2;
        cnt++;
    }
    MkLine rl3 = MkLine(rp1, p1);
    MkLine rl4 = MkLine(rp1, p2);

    double len1 = rl3.GetLength();
    double len2 = rl4.GetLength();
    double theta1 = rl3.GetTheta();
    double theta2 = rl4.GetTheta();

    if (fabs(len1 - len2) < EPS)
        *this = NullArc;
    if (cnt == 20 && rp1 == NullPoint)
        *this = NullArc;
    else
    {
        SetCenter(rp1);
        SetRadius(len1);
        SetStartAng(theta1);
        SetEndAng(theta2);
        CalStartPoint();
        CalEndPoint();
    }
}

void MkArc::CalArea() // TODO: Implement it
{
}

void MkArc::CalCrownArea() // TODO: Implement it
{
}

void MkArc::CalTriArea() // TODO: Implement it
{
}

void MkArc::SetCenter(double cx, double cy)
{
    MkCircle::SetCenter(cx, cy);
    CalStartPoint();
    CalEndPoint();
}

void MkArc::SetCenter(MkPoint &cp)
{
    MkCircle::SetCenter(cp);
    CalStartPoint();
    CalEndPoint();
}

void MkArc::SetCenter(MkPoint &&cp)
{
    MkCircle::SetCenter(cp);
    CalStartPoint();
    CalEndPoint();
}

void MkArc::SetRadius(double radius)
{
    MkCircle::SetRadius(radius);
    CalStartPoint();
    CalEndPoint();
}

void MkArc::SetStartAng(double start_ang)
{
    FStartAng = start_ang;
    CalStartPoint();
    CalEndPoint();
}

void MkArc::SetEndAng(double end_ang)
{
    FEndAng = end_ang;
    CalStartPoint();
    CalEndPoint();
}

double MkArc::GetStartAng()
{
    return FStartAng;
}

double MkArc::GetEndAng()
{
    return FEndAng;
}

double MkArc::GetArea()
{
    if (FStartAng > FEndAng)
        FEndAng += 360;
    return MkCircle::GetArea() * fabs(FStartAng - FEndAng) / 360.0;
}

double MkArc::GetTriArea()
{
    MkTriangle rt(GetCenter(), FStartPoint, FEndPoint);
    return rt.GetArea();
}

bool MkArc::isWithInArc(MkPoint rp)
{
    MkLine rl(FCP, rp);
    return ((*this)(0) * rl > 0 && (*this)(1) * rl < 0) && (GetRadius() > rl.GetLength());
}

bool MkArc::isWithInAng(MkPoint rp)
{
    MkLine rl(FCP, rp);
    return ((*this)(0) * rl > 0 && (*this)(1) * rl < 0);
}

double MkArc::CrossProduct()
{
    MkLine rl1((*this)[0], (*this)[1]);
    MkLine rl2((*this)[0], (*this)[2]);
    return rl1 * rl2;
}

double MkArc::GetCrownArea()
{
    return GetArea() - GetTriArea();
}

MkLine &MkArc::operator()(int i)
{
    static MkLine l;
    if (i == 0)
    {
        l = MkLine((*this)[0], (*this)[1]);
        return l;
    }
    else if (i == 1)
    {
        l = MkLine((*this)[0], (*this)[2]);
        return l;
    }
    else
    {
        MkDebug("MkArc::operator() Bad Index");
        return NullLine;
    }
}

MkPoint &MkArc::operator[](int i)
{
    if (i == 0)
        return FCP;
    else if (i == 1)
        return FStartPoint;
    else if (i == 2)
        return FEndPoint;
    else
    {
        MkDebug("MkArc::operator[] Bad Index");
        return NullPoint;
    }
}

void MkArc::CalStartPoint()
{
    MkPoint cp;
    double x, y;

    cp = GetCenter();
    x = GetRadius() * cos(FStartAng * M_PI / 180.0);
    y = GetRadius() * sin(FStartAng * M_PI / 180.0);
    FStartPoint.X = cp.X + x;
    FStartPoint.Y = cp.Y + y;
    return;
}

void MkArc::CalEndPoint()
{
    MkPoint cp;
    double x, y;

    cp = GetCenter();
    x = FRadius * cos(FEndAng * M_PI / 180.0);
    y = FRadius * sin(FEndAng * M_PI / 180.0);
    FEndPoint.X = cp.X + x;
    FEndPoint.Y = cp.Y + y;
    return;
}

void MkArc::CalStartAngle()
{
    MkLine rl((*this)[0], (*this)[1]);
    FStartAng = rl.GetTheta();
    return;
}

void MkArc::CalEndAngle()
{
    MkLine rl((*this)[0], (*this)[2]);
    FEndAng = rl.GetTheta();
    return;
}

void MkArc::ReCalcAng()
{
    CalStartAngle();
    CalEndAngle();
}

void MkArc::ReCalcPoint()
{
    CalStartPoint();
    CalEndPoint();
}

MkArc &MkArc::operator=(MkArc &rc)
{
    this->MkShape::operator=((MkShape &)rc);
    FCP.X = rc.FCP.X;
    FCP.Y = rc.FCP.Y;
    FRadius = rc.FRadius;
#ifdef __BCPLUSPLUS__
    Color = rc.Color;
#endif
    CalArea();
    FStartAng = rc.FStartAng;
    FEndAng = rc.FEndAng;
    CalStartPoint();
    CalEndPoint();
    return (*this);
}

#ifdef __BCPLUSPLUS__
void MkArc::Draw(TObject *Sender)
{
    TColor C;
    if (String(Sender->ClassName()) == String("MkPaintBox"))
    {
        MkPaintBox *pb = (MkPaintBox *)Sender;
        C = pb->Canvas->Pen->Color;
        pb->Canvas->Pen->Color = Color;

        pb->Arc2D((*this)[0].X, (*this)[0].Y, GetRadius(), GetStartAng(), GetEndAng());
        pb->MoveTo3D((*this)[0].X, (*this)[0].Y, 0);
        pb->LineTo3D((*this)[1].X, (*this)[1].Y, 0);
        pb->MoveTo3D((*this)[0].X, (*this)[0].Y, 0);
        pb->LineTo3D((*this)[2].X, (*this)[2].Y, 0);
        pb->Canvas->Pen->Color = C;
    }
}
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
void MkArc::Draw(MkPaint *pb)
{
    pb->Arc2D((*this)[0].X, (*this)[0].Y, GetRadius(), GetStartAng(), GetEndAng());
    pb->MoveTo3D((*this)[0].X, (*this)[0].Y, 0);
    pb->LineTo3D((*this)[1].X, (*this)[1].Y, 0);
    pb->MoveTo3D((*this)[0].X, (*this)[0].Y, 0);
    pb->LineTo3D((*this)[2].X, (*this)[2].Y, 0);
}
#endif

//---------------------------------------------------------------------------
