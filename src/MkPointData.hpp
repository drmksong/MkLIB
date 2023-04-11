//---------------------------------------------------------------------------
#ifndef MkPointDataH
#define MkPointDataH
#include <stdio.h>
#include <cmath>
#include "MkMisc.hpp"
#include "MkPoint.hpp"
#include "MkArray.hpp"
#include "MkMatrix.hpp"
// #include "MkCube.h"
// #include "MkRailWay.h"
// #include "MkFault.h"
// #include "MkPlane.h"
template <class T>
struct MkPointData : MkPoint
{
public:
    T Data;

    MkPointData();
    MkPointData(double x, double y);
    MkPointData(double x, double y, double z);

    MkPointData &operator=(const MkPointData &dp);
    MkPointData &operator=(MkPointData &&dp);
    MkPointData &operator=(const MkPoint &rp);
    MkPointData &operator=(MkPoint &&rp);
    MkPointData &operator=(T data)
    {
        Data = data;
        return *this;
    };
    void operator+=(MkPointData &rp)
    {
        X += rp.X;
        Y += rp.Y;
        Z += rp.Z;
    }
    void operator+=(T data) { Data += data; }
    MkPointData operator*=(MkMatrix4_d &rm);
    friend MkPointData operator+(MkPointData a, MkPointData b)
    {
        MkPointData c;
        c.X = a.X + b.X;
        c.Y = a.Y + b.Y;
        return c;
    }
    bool operator==(const MkPointData &dp);
    bool operator==(MkPointData &&dp);

    bool operator!=(const MkPointData &dp);
    bool operator!=(MkPointData &&dp);
};

template <class T>
class MkPointDatas : public MkAbstract
{
protected:
    boost::shared_ptr<MkPointData<T>[]> FPoint;
    int FSize;
    int FCapacity;

public:
    MkPointDatas(std::vector<MkPointData<T>> &dp);
    MkPointDatas(int size, MkPointData<T> *rps);
    MkPointDatas(int size);
    MkPointDatas()
    {
        FSize = 0;
        FCapacity = 0;
        FPoint = NULL;
    }
    ~MkPointDatas();
    virtual void Initialize(int size);
    virtual void Initialize(int size, MkPointData<T> *);
    int GetSize() { return FSize; };
    int GetNumber() { return FSize; };
    bool Add(MkPointData<T> point);
    //    void  Delete(MkPointData<T> point);
    int Reserve(int Delta);
    int Grow(int Delta);
    //     Shrink(int Delta);
    bool Clear();
    virtual MkPointData<T> &operator[](int);

    MkPointDatas &operator*=(MkMatrix4_d &rm);

    MkPointDatas &Translate(MkPoint rp);
    MkPointDatas &Translate(MkPointData<T> rp);
    MkPointDatas &Translate(double x, double y, double z);
    MkPointDatas &Rotate(double alpha, double beta, double gamma);
    MkPointDatas &Scale(double sx, double sy, double sz);

    MkPointDatas &CopyFrom(MkPointDatas points);
    MkPointDatas &operator=(MkPointDatas &points);
    bool operator==(MkPointDatas &points);
    bool operator!=(MkPointDatas &points);

    std::string ClassName() { return std::string("MkPointDatas"); };

};
template <class T>
extern MkPointData<T> NullPointData;
template <class T>
extern MkPointDatas<T> NullPointDatas;
//---------------------------------------------------------------------------
#endif
