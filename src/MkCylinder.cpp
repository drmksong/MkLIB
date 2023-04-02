//---------------------------------------------------------------------------
#include "MkCylinder.hpp"

MkCylinder NullCylinder(0, 0, 0, 0);
//---------------------------------------------------------------------------
#ifdef __BCPLUSPLUS__
#pragma package(smart_init)
#endif
//---------------------------------------------------------------------------
MkCylinder::MkCylinder()
{
    FCP.X = 0;
    FCP.Y = 0;
    FCP.Z = 0;
#ifdef __BCPLUSPLUS__
    Color = clBlack;
#endif
    FRadius = 0;
    needUpdate = true;
    SurfDivision = 4;
}

MkCylinder::MkCylinder(double cx, double cy, double cz, double radius)
{
    FCP.X = cx;
    FCP.Y = cy;
    FCP.Z = cz;

    FRadius = radius;
    needUpdate = true;
    SurfDivision = 4;
}

MkCylinder::MkCylinder(MkPoint &cp, double radius)
{
    FCP = cp;
    FRadius = radius;
    needUpdate = true;
    SurfDivision = 4;
}

MkCylinder::MkCylinder(MkPoint &&cp, double radius)
{
    FCP = cp;
    FRadius = radius;
    needUpdate = true;
    SurfDivision = 4;
}

#ifdef __BCPLUSPLUS__
MkCylinder::MkCylinder(double cx, double cy, double cz, double radius, TColor C)
{
    FCP.X = cx;
    FCP.Y = cy;
    FCP.Z = cz;

    FRadius = radius;
    Color = C;
    needUpdate = true;
    SurfDivision = 4;
}

MkCylinder::MkCylinder(MkPoint cp, double radius, TColor C)
{
    FCP = cp;
    FRadius = radius;
    Color = C;
    needUpdate = true;
    SurfDivision = 4;
}
#endif

void MkCylinder::SetCylinder(double cx, double cy, double cz, double radius)
{
    FCP.X = cx;
    FCP.Y = cy;
    FCP.Z = cz;

    FRadius = radius;
    needUpdate = true;
}

void MkCylinder::SetCylinder(MkPoint &cp, double radius)
{
    FCP = cp;
    FRadius = radius;
    needUpdate = true;
}

void MkCylinder::SetCylinder(MkPoint &&cp, double radius)
{
    FCP = cp;
    FRadius = radius;
    needUpdate = true;
}
#ifdef __BCPLUSPLUS__
void MkCylinder::SetCylinder(double cx, double cy, double cz, double radius, TColor C)
{
    FCP.X = cx;
    FCP.Y = cy;
    FCP.Z = cz;

    FRadius = radius;
    Color = C;
    needUpdate = true;
}

void MkCylinder::SetCylinder(MkPoint cp, double radius, TColor C)
{
    FCP = cp;
    FRadius = radius;
    Color = C;
    needUpdate = true;
}
#endif

void MkCylinder::SetCenter(double cx, double cy, double cz)
{
    FCP.X = cx;
    FCP.Y = cy;
    FCP.Z = cz;
    needUpdate = true;
}

void MkCylinder::SetCenter(MkPoint &cp)
{
    FCP = cp;
    needUpdate = true;
}

void MkCylinder::SetCenter(MkPoint &&cp)
{
    FCP = cp;
    needUpdate = true;
}

void MkCylinder::SetRadius(double radius)
{
    FRadius = radius;
    needUpdate = true;
}

void MkCylinder::SetOrient(MkPoint &orient)
{
    double len;

    Fl = orient.X;
    Fm = orient.Y;
    Fn = orient.Z;

    len = sqrt(Fl * Fl + Fm * Fm + Fn * Fn);

    Fl /= len;
    Fm /= len;
    Fn /= len;
    needUpdate = true;
}

void MkCylinder::SetOrient(MkPoint &&orient)
{
    double len;

    Fl = orient.X;
    Fm = orient.Y;
    Fn = orient.Z;

    len = sqrt(Fl * Fl + Fm * Fm + Fn * Fn);

    Fl /= len;
    Fm /= len;
    Fn /= len;
    needUpdate = true;
}

void MkCylinder::SetOrient(double l, double m, double n)
{
    double len;

    Fl = l;
    Fm = m;
    Fn = n;

    len = sqrt(Fl * Fl + Fm * Fm + Fn * Fn);

    Fl /= len;
    Fm /= len;
    Fn /= len;
    needUpdate = true;
}

bool MkCylinder::IsInSurface(MkPoint &pnt, double thick)
{
    double dist = GetDist(pnt);
    return (FRadius - thick < dist && dist < FRadius + thick);
}

bool MkCylinder::IsInSurface(MkPoint &&pnt, double thick)
{
    double dist = GetDist(pnt);
    return (FRadius - thick < dist && dist < FRadius + thick);
}

bool MkCylinder::IsInSpace(MkPoint &pnt)
{
    return GetDist(pnt) < FRadius;
}

bool MkCylinder::IsInSpace(MkPoint &&pnt)
{
    return GetDist(pnt) < FRadius;
}

MkPoint& MkCylinder::GetCenter()
{
    return FCP;
}

double MkCylinder::GetRadius()
{
    return FRadius;
}

double MkCylinder::GetDist(MkPoint &pnt)
{
    double len;
    double l, m, n; // cross vector
    double x, y, z; // point
    len = sqrt(Fl * Fl + Fm * Fm + Fn * Fn);
    assert(len - 1.0 < 0.001);
    x = pnt.X - FCP.X;
    y = pnt.Y - FCP.Y;
    z = pnt.Z - FCP.Z;

    l = Fm * z - y * Fn;
    m = Fn * x - z * Fl;
    n = Fl * y - x * Fm;

    return sqrt(l * l + m * m + n * n);
}

double MkCylinder::GetDist(MkPoint &&pnt)
{
    double len;
    double l, m, n; // cross vector
    double x, y, z; // point
    len = sqrt(Fl * Fl + Fm * Fm + Fn * Fn);
    assert(len - 1.0 < 0.001);
    x = pnt.X - FCP.X;
    y = pnt.Y - FCP.Y;
    z = pnt.Z - FCP.Z;

    l = Fm * z - y * Fn;
    m = Fn * x - z * Fl;
    n = Fl * y - x * Fm;

    return sqrt(l * l + m * m + n * n);
}

MkPoint &MkCylinder::operator[](int i)
{
    if (i == 0)
        return FCP;
    else
        return NullPoint;
}

MkCylinder &MkCylinder::operator=(MkCylinder &rc)
{
    MkShape::operator=((MkShape &)rc);
    FCP = rc.FCP;
    FRadius = rc.FRadius;
#ifdef __BCPLUSPLUS__
    Color = rc.Color;
#endif
    return (*this);
}

MkCylinder &MkCylinder::operator=(MkCylinder &&rc)
{
    MkShape::operator=((MkShape &)rc);
    FCP = rc.FCP;
    FRadius = rc.FRadius;
#ifdef __BCPLUSPLUS__
    Color = rc.Color;
#endif
    return (*this);
}

bool MkCylinder::operator&&(MkLine &rl)
{
    return false;
}

bool MkCylinder::operator&&(MkLine &&rl)
{
    return false;
}

MkPoints &MkCylinder::operator&(MkLine &rl)
{
    // calc FPoints;
    return FPoints;
}

MkPoints &MkCylinder::operator&(MkLine &&rl)
{
    // calc FPoints;
    return FPoints;
}

bool MkCylinder::operator==(MkCylinder &rs)
{
    return FCP == rs.FCP && fabs(FRadius - rs.FRadius) < EPS && fabs(FLength - rs.FLength) < EPS && fabs(Fl - rs.Fl) < EPS &&
           fabs(Fm - rs.Fm) < EPS && fabs(Fn - rs.Fn) < EPS && fabs(Psi - rs.Psi) < EPS && fabs(Theta - rs.Theta) && FPoints == rs.FPoints;
}

bool MkCylinder::operator==(MkCylinder &&rs)
{
    return FCP == rs.FCP && fabs(FRadius - rs.FRadius) < EPS && fabs(FLength - rs.FLength) < EPS && fabs(Fl - rs.Fl) < EPS &&
           fabs(Fm - rs.Fm) < EPS && fabs(Fn - rs.Fn) < EPS && fabs(Psi - rs.Psi) < EPS && fabs(Theta - rs.Theta) && FPoints == rs.FPoints;
}

bool MkCylinder::operator!=(MkCylinder &rs)
{
    return !operator==(rs);
}

bool MkCylinder::operator!=(MkCylinder &&rs)
{
    return !operator==(rs);
}

bool MkCylinder::IsIntersect(MkLine &rl)
{
    return *this && rl;
}
bool MkCylinder::IsIntersect(MkLine &&rl)
{
    return *this && rl;
}

MkPoints &MkCylinder::CalcIntPnts(MkLine &rl)
{
    return *this & rl;
}

MkPoints &MkCylinder::CalcIntPnts(MkLine &&rl)
{
    return *this & rl;
}

void MkCylinder::GetIntParam(MkLine &rl, double &t1, double &t2)
{
}

void MkCylinder::GetIntParam(MkLine &&rl, double &t1, double &t2)
{
}

void MkCylinder::RotateSpace(MkPoint &rp)
{
    rp -= FCP;
    rp.Rotate(0, Psi, 0);   // rotate in y-axis
    rp.Rotate(Theta, 0, 0); // rotate in z-axis --- check it out
}

void MkCylinder::RotateSpace(MkPoint &&rp)
{
    rp -= FCP;
    rp.Rotate(0, Psi, 0);   // rotate in y-axis
    rp.Rotate(Theta, 0, 0); // rotate in z-axis --- check it out
}

void MkCylinder::RotateSpace(MkLine &rl)
{
    rl -= FCP;
    rl.Rotate(0, Psi, 0);
    rl.Rotate(Theta, 0, 0);
}

void MkCylinder::RotateSpace(MkLine &&rl)
{
    rl -= FCP;
    rl.Rotate(0, Psi, 0);
    rl.Rotate(Theta, 0, 0);
}

void MkCylinder::RotateSpace(MkPlane &rp)
{
}

void MkCylinder::RotateSpace(MkPlane &&rp)
{
}

void MkCylinder::RotateSpace(MkJointPlane &jp)
{
}

void MkCylinder::RotateSpace(MkJointPlane &&jp)
{
}

void MkCylinder::RotateSpace(MkPennyJoint &pj)
{
}

void MkCylinder::RotateSpace(MkPennyJoint &&pj)
{
}

void MkCylinder::UnRotateSpace(MkPoint &rp)
{
}

void MkCylinder::UnRotateSpace(MkPoint &&rp)
{
}

void MkCylinder::UnRotateSpace(MkLine &rl)
{
}

void MkCylinder::UnRotateSpace(MkLine &&rl)
{
}

void MkCylinder::UnRotateSpace(MkPlane &rp)
{
}

void MkCylinder::UnRotateSpace(MkPlane &&rp)
{
}
void MkCylinder::UnRotateSpace(MkJointPlane &jp)
{
}

void MkCylinder::UnRotateSpace(MkJointPlane &&jp)
{
}
void MkCylinder::UnRotateSpace(MkPennyJoint &pj)
{
}
void MkCylinder::UnRotateSpace(MkPennyJoint &&pj)
{
}

bool MkCylinder::UpdateSurf()
{
    int ldiv, cdiv;
    double len;
    cdiv = int(4 * pow(2, SurfDivision));
    len = 2 * 3.141592 * FRadius / cdiv;
    ldiv = int(FLength / len);
    if (ldiv < 2)
        ldiv = 2;

    needUpdate = false;
    return true;
}

#ifdef __BCPLUSPLUS__
void MkCylinder::Draw(TObject *Sender)
{
    if (needUpdate)
        UpdateSurf();
    Surf.Draw(Sender);
}
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
void MkCylinder::Draw(MkPaint *pb)
{
    if (needUpdate)
        UpdateSurf();
    Surf.Draw(pb);
}
#endif

//---------------------------------------------------------------------------
MkCylinders::MkCylinders(int size)
{
    if (size <= 0)
    {
        MkDebug("::MkCylinders - MkCylinders(int size)");
        FCylinder.reset();
        return;
    }

    FSize = size;
    try {
        FCylinder = boost::make_shared<MkCylinder[]>(FSize);
    }
    catch (std::bad_alloc &a) {
        MkDebug("MkCylinders::MkCylinders(int size) bad_alloc thrown!!!\n");
        throw Alloc(a.what());
    }
}

MkCylinders::MkCylinders(int size, boost::shared_ptr<MkCylinder[]> cylinders)
{
    if (size <= 0)
    {
        MkDebug("::MkCylinders - MkCylinders(int size, boost::shared_ptr<MkCylinder[]> cylinders)");
        FCylinder.reset();
        return;
    }

    FSize = size;
    try {
        FCylinder = boost::make_shared<MkCylinder[]>(FSize);
    }
    catch (std::bad_alloc &a) {
        MkDebug("MkCylinders::MkCylinders(int size, boost::shared_ptr<MkCylinder[]> cylinders) bad_alloc thrown!!!\n");
        throw Alloc(a.what());
    }

    for (int i = 0; i < FSize; i++)
        FCylinder[i] = cylinders[i];
}

MkCylinders::MkCylinders(MkCylinders &cylinders)
{
    FSize = cylinders.FSize;
    try {
        FCylinder = boost::make_shared<MkCylinder[]>(FSize);
    }
    catch (std::bad_alloc &a) {
        MkDebug("MkCylinders::MkCylinders(MkCylinders &cylinders) bad_alloc thrown!!!\n");
        throw Alloc(a.what());
    }

    for (int i = 0; i < FSize; i++)
        FCylinder[i] = cylinders.FCylinder[i];
}

void MkCylinders::Initialize(int size)
{
    if (size <= 0)
    {
        MkDebug("::MkCylinders - Initialize(int size)");
        FCylinder.reset();
        return;
    }

    FSize = size;
    try {
        FCylinder = boost::make_shared<MkCylinder[]>(FSize);
    }
    catch (std::bad_alloc &a) {
        MkDebug("MkCylinders::Initialize(int size) bad_alloc thrown!!!\n");
        throw Alloc(a.what());
    }
}

void MkCylinders::Clear()
{
    FSize = 0;
    FCylinder.reset();
}

MkCylinder &MkCylinders::operator[](int i)
{
    if (i >= 0 && i < FSize)
        return FCylinder[i];
    else
        return NullCylinder;
}

MkCylinders &MkCylinders::operator=(MkCylinders &cylinders)
{
    if (this == &cylinders)
        return *this;

    FSize = cylinders.FSize;
    try {
        FCylinder = boost::make_shared<MkCylinder[]>(FSize);
    }
    catch (std::bad_alloc &a) {
        MkDebug("MkCylinders::operator=(MkCylinders &cylinders) bad_alloc thrown!!!\n");
        throw Alloc(a.what());
    }

    for (int i = 0; i < FSize; i++)
        FCylinder[i] = cylinders.FCylinder[i];

    return *this;
}

#ifdef __BCPLUSPLUS__
void MkCylinders::Draw(TObject *Sender)
{
    for (int i = 0; i < FSize; i++)
        FCylinder[i].Draw(Sender);
}
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
void MkCylinders::Draw(MkPaint *pb)
{
    for (int i = 0; i < FSize; i++)
        FCylinder[i].Draw(pb);
}
#endif

//---------------------------------------------------------------------------
