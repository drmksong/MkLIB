//---------------------------------------------------------------------------
// This module is general purposed simple graphic class to store, draw,
// manipulate object. It is well suited to VCL component, but not restricted.
// It forms the base for the higher level class, such as tunnel component.
//
// Copyright (c) 1999-2000 Myung Kyu Song, ESCO Consultant Co., Ltd.

#include "MkPointData.hpp"

template <class T>
MkPointData<T> NullPointData(0, 0, 0);
template <class T>
MkPointDatas<T> NullPointDatas(0);

template <class T>
MkPointData<T>::MkPointData()
    : MkPoint()
{
    Data = 0;
};

template <class T>
MkPointData<T>::MkPointData(double x, double y)
    : MkPoint(x, y)
{
    Data = 0;
};

template <class T>
MkPointData<T>::MkPointData(double x, double y, double z)
    : MkPoint(x, y, z)
{
    Data = 0;
};

template <class T>
MkPointData<T> &MkPointData<T>::operator=(const MkPoint &dp)
{
    X = dp.X;
    Y = dp.Y;
    Z = dp.Z;
    Data = 0;
    return (*this);
}

template <class T>
MkPointData<T> &MkPointData<T>::operator=(MkPoint &&rp)
{
    X = rp.X;
    Y = rp.Y;
    Z = rp.Z;
    Data = 0;
    return (*this);
}

template <class T>
MkPointData<T> &MkPointData<T>::operator=(const MkPointData<T> &rp)
{
    X = rp.X;
    Y = rp.Y;
    Z = rp.Z;
    Data = rp.Data;
    return (*this);
}

template <class T>
MkPointData<T> &MkPointData<T>::operator=(MkPointData<T> &&rp)
{
    X = rp.X;
    Y = rp.Y;
    Z = rp.Z;
    Data = rp.Data;
    return (*this);
}

template <class T>
bool MkPointData<T>::operator==(const MkPointData<T> &rp)
{
    return (fabs(X - rp.X) < FTOL) &&
           (fabs(Y - rp.Y) < FTOL) &&
           (fabs(Z - rp.Z) < FTOL) &&
           (fabs(Data - rp.Data) < FTOL);
}

template <class T>
bool MkPointData<T>::operator==(MkPointData<T> &&rp)
{
    return (fabs(X - rp.X) < FTOL) &&
           (fabs(Y - rp.Y) < FTOL) &&
           (fabs(Z - rp.Z) < FTOL) &&
           (fabs(Data - rp.Data) < FTOL);
}

template <class T>
bool MkPointData<T>::operator!=(const MkPointData<T> &rp)
{
    return (fabs(X - rp.X) > FTOL) ||
           (fabs(Y - rp.Y) > FTOL) ||
           (fabs(Z - rp.Z) > FTOL) ||
           (fabs(Data - rp.Data) > FTOL);
}

template <class T>
bool MkPointData<T>::operator!=(MkPointData<T> &&rp)
{
    return (fabs(X - rp.X) > FTOL) ||
           (fabs(Y - rp.Y) > FTOL) ||
           (fabs(Z - rp.Z) > FTOL) ||
           (fabs(Data - rp.Data) > FTOL);
}

template <class T>
MkPointData<T> MkPointData<T>::operator*=(MkMatrix4_d &rm)
{
    MkPointData<T> rp;

    rp.X = X * rm(0, 0) + Y * rm(0, 1) + Z * rm(0, 2);
    rp.Y = X * rm(1, 0) + Y * rm(1, 1) + Z * rm(1, 2);
    rp.Z = X * rm(2, 0) + Y * rm(2, 1) + Z * rm(2, 2);
    return rp;
}

//------------------------------------------------------
// Use this, rather than *rps version...should eventually delete rps version
template <class T>
MkPointDatas<T>::MkPointDatas(std::vector<MkPointData<T>> &dp)
{
    FSize = dp.size();
    FCapacity = FSize + Mk::Delta;

    try
    {
        FPoint.reset(new MkPointData[FCapacity]);
    }
    catch (std::bad_alloc &a)
    {
        MkDebug("MkPointDatas<T>::MkPointDatas<T> bad_alloc thrown!!!\n");
        throw Alloc(a.what());
    }

    for (int i = 0; i < FSize; i++)
    {
        FPoint[i] = dp[i];
    }
    for (int i = FSize; i < FCapacity; i++)
    {
        FPoint[i] = NullPointData<T>;
    }
}
template <class T>
MkPointDatas<T>::MkPointDatas(int size, MkPointData<T> *rps)
{

    if (size < 0)
    {
        printf("::MkPointDatas - MkPointDatas(int size)\n");
        return;
    }

    FSize = size;
    FCapacity = FSize + Mk::Delta;

    try
    {
        FPoint.reset(new MkPointData[FSize]);
    }
    catch (std::bad_alloc &a)
    {
        MkDebug("MkPointDatas<T>::MkPointDatas bad_alloc thrown!!!\n");
        throw Alloc(a.what());
    }

    for (int i = 0; i < FSize; i++)
    {
        FPoint[i] = rps[i];
    }

    for (int i = FSize; i < FCapacity; i++)
    {
        FPoint[i] = NullPointData<T>;
    }
}
template <class T>
MkPointDatas<T>::MkPointDatas(int size)
{
    if (size < 0)
    {
        printf("::MkPointDatas - MkPointDatas(int size)\n");
        return;
    }

    FSize = size;
    FCapacity = FSize + Mk::Delta;

    try
    {
        FPoint.reset(new MkPointData[FSize]);
    }
    catch (std::bad_alloc &a)
    {
        MkDebug("MkPointDatas<T>::MkPointDatas bad_alloc thrown!!!\n");
        throw Alloc(a.what());
    }

    for (int i = 0; i < FCapacity; i++)
    {
        FPoint[i] = NullPointData<T>;
    }
}
template <class T>
MkPointDatas<T>::~MkPointDatas()
{
    FCapacity = FSize = 0;
    FPoint.reset();
}
template <class T>
void MkPointDatas<T>::Initialize(int size)
{
    if (size < 0)
    {
        printf("::MkPointDatas - Initialize(int size)\n");
        return;
    }

    FSize = size;
    FCapacity = FSize + Mk::Delta;

    try
    {
        FPoint.reset(new MkPointData[FSize]);
    }
    catch (std::bad_alloc &a)
    {
        MkDebug("MkPointDatas<T>::Initialize bad_alloc thrown!!!\n");
        throw Alloc(a.what());
    }

    for (int i = 0; i < FCapacity; i++)
    {
        FPoint[i] = NullPointData<T>;
    }
}
template <class T>
void MkPointDatas<T>::Initialize(int size, MkPointData<T> *rps)
{

    if (size < 0)
    {
        printf("::MkPointDatas - MkPointDatas(int size)\n");
        return;
    }

    FSize = size;
    FCapacity = FSize + Mk::Delta;

    try
    {
        FPoint.reset(new MkPointData[FSize]);
    }
    catch (std::bad_alloc &a)
    {
        MkDebug("MkPointDatas<T>::MkPointDatas bad_alloc thrown!!!\n");
        throw Alloc(a.what());
    }

    for (int i = 0; i < FSize; i++)
    {
        FPoint[i] = rps[i];
    }

    for (int i = FSize; i < FCapacity; i++)
    {
        FPoint[i] = NullPointData<T>;
    }
}
template <class T>
int MkPointDatas<T>::Reserve(int delta)
{
    return Grow(delta);
}
template <class T>
int MkPointDatas<T>::Grow(int delta)
{
    int i;
    boost::shared_ptr<MkPointData<T>[]> rp;

    if (delta <= 0)
        throw std::length_error("MkPointDatas<T>::Reserve delta is less than or equal to zero\n");

    try
    {
        rp.reset(new MkPointData[FCapacity + delta]);
    }
    catch (std::bad_alloc &a)
    {
        MkDebug("MkPointData<T>::Grow std::bad_alloc thrown");
        throw Alloc(a.what());
    }

    for (i = 0; i < FSize; i++)
        rp[i] = FPoint[i];
    for (i = FSize; i < FCapacity + delta; i++)
        rp[i] = NullPointData<T>;

    FPoint = rp; // it doesn't leak memory as it is smart pointers (shared_ptr)
    FCapacity = FCapacity + delta;
    return FCapacity;
}
template <class T>
bool MkPointDatas<T>::Add(MkPointData<T> point)
{
    printf("MkPointData<T>:: size %d and capacity %d \n", FSize, FCapacity);
    if (FSize + 2 < FCapacity)
    {
        try
        {
            Grow(Mk::Delta);
        }
        catch (Alloc &a)
        {
            MkDebug("MkPointDatas<T>::Add single point, Alloc thrown while attempt Grow()");
            throw Alloc(a.what());
        }
    }

    FSize++;
    FPoint[FSize - 1] = point;
    return true;
}
template <class T>
bool MkPointDatas<T>::Clear()
{

    FCapacity = FSize = 0;
    FPoint.reset();
    return true;
}
template <class T>
MkPointData<T> &MkPointDatas<T>::operator[](int i)
{
    if (i >= FSize)
    {
        throw std::length_error("MkPointDatas<T>::[] index out of bounds");
    }

    if (i >= 0 && i < FSize)
        return FPoint[i];
    else
        return NullPointData<T>;
}
template <class T>
MkPointDatas<T> &MkPointDatas<T>::CopyFrom(MkPointDatas<T> points)
{
    int i;

    Clear();
    FSize = points.FSize;
    FCapacity = points.FCapacity;
    try
    {
        FPoint.reset(new MkPointData[FCapacity]);
    }
    catch (std::bad_alloc &a)
    {
        MkDebug("MkPointDatas<T>::CopyFrom throw std::bad_alloc while reserving memory for copying points\n");
        throw Alloc(a.what());
    }
    for (i = 0; i < FSize; i++)
        FPoint[i] = points.FPoint[i];

    for (i = FSize; i < FCapacity; i++)
        FPoint[i] = NullPointData<T>;

    return *this;
}
template <class T>
MkPointDatas<T> &MkPointDatas<T>::operator=(MkPointDatas<T> &points)
{
    int i;

    Clear();
    FSize = points.FSize;
    FCapacity = points.FCapacity;
    try
    {
        FPoint.reset(new MkPointData[FCapacity]);
    }
    catch (std::bad_alloc &a)
    {
        MkDebug("MkPointDatas<T>::operator=() throw std::bad_alloc while reserving memory for copying points\n");
        throw Alloc(a.what());
    }
    for (i = 0; i < FSize; i++)
        FPoint[i] = points.FPoint[i];

    for (i = FSize; i < FCapacity; i++)
        FPoint[i] = NullPointData<T>;

    return *this;
}
template <class T>
bool MkPointDatas<T>::operator==(MkPointDatas<T> &points)
{
    if (FSize != points.FSize)
        return false;

    for (int i = 0; i < FSize; i++)
        if (FPoint[i] != points.FPoint[i])
            return false;

    return true;
}
template <class T>
bool MkPointDatas<T>::operator!=(MkPointDatas<T> &points)
{
    if (FSize != points.FSize)
        return true;

    for (int i = 0; i < FSize; i++)
        if (FPoint[i] != points.FPoint[i])
            return true;

    return false;
}
template <class T>
MkPointDatas<T> &MkPointDatas<T>::operator*=(MkMatrix4_d &rm)
{
    for (int i = 0; i < FSize; i++)
        FPoint[i] = FPoint[i] * rm;
    return *this;
}
template <class T>
MkPointDatas<T> &MkPointDatas<T>::Translate(MkPoint rp)
{
    for (int i = 0; i < FSize; i++)
        FPoint[i].Translate(rp);
    return *this;
}
template <class T>
MkPointDatas<T> &MkPointDatas<T>::Translate(MkPointData<T> rp)
{
    for (int i = 0; i < FSize; i++)
        FPoint[i].Translate(rp);
    return *this;
}
template <class T>
MkPointDatas<T> &MkPointDatas<T>::Translate(double x, double y, double z)
{
    for (int i = 0; i < FSize; i++)
        FPoint[i].Translate(x, y, z);
    return *this;
}
template <class T>
MkPointDatas<T> &MkPointDatas<T>::Rotate(double alpha, double beta, double gamma)
{
    for (int i = 0; i < FSize; i++)
        FPoint[i].Rotate(alpha, beta, gamma);
    return *this;
}
template <class T>
MkPointDatas<T> &MkPointDatas<T>::Scale(double sx, double sy, double sz)
{
    for (int i = 0; i < FSize; i++)
        FPoint[i].Scale(sx, sy, sz);
    return *this;
}
//---------------------------------------------------------------------------
