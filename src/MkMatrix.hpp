//---------------------------------------------------------------------------
#ifndef MkMatrixH
#define MkMatrixH

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "MkArray.hpp"
#include "MkMisc.hpp"
// #include "MkSparseMatrix.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

template <class T>
class MkMatrix4
{
private:
    T FMatrix[4][4];
    int FI, FJ;

public:
    MkMatrix4();
    void Identity();
    void LoadIdentity() { Identity(); }
    void Clear();
    void Translate(T x, T y, T z);
    void Rotate(T alpha, T beta, T gamma);
    void RotateInX(T alpha);
    void RotateInY(T beta);
    void RotateInZ(T gamma);
    void RotateInA(T theta, T l, T m, T n);
    void Scale(T sx, T sy, T sz);
    MkMatrix4<T> &operator=(const MkMatrix4<T> &);
    MkMatrix4<T> &operator=(MkMatrix4<T> &&);

    T &operator()(int i, int j)
    {
        static T Zero;
        Zero = 0;
        if (i < 4 && i >= 0 && j < 4 && j >= 0)
            return FMatrix[i][j];
        else
            return Zero;
    }
    MkMatrix4<T> &operator*=(T f);
    MkMatrix4<T> &operator*=(MkMatrix4<T> &);
    MkMatrix4<T> &operator+=(T f);
    MkMatrix4<T> &operator+=(MkMatrix4<T> &);
    MkMatrix4<T> &operator-=(T f);
    MkMatrix4<T> &operator-=(MkMatrix4<T> &);

    friend MkMatrix4<T> &operator*(MkMatrix4<T> &rm, T f)
    {
        static MkMatrix4<T> rm_t;
        rm_t.Clear();

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                rm_t.FMatrix[i][j] = rm.FMatrix[i][j] * f;

        return rm_t;
    }

    friend MkMatrix4<T> &operator*(MkMatrix4<T> &rm, MkMatrix4<T> &rm2)
    {
        static MkMatrix4<T> rm_t;
        rm_t.Clear();

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                {
                    rm_t.FMatrix[i][j] += rm.FMatrix[i][k] * rm2.FMatrix[k][j];
                }

        return rm_t;
    }

    friend MkMatrix4<T> &operator+(MkMatrix4<T> &rm, T f)
    {
        static MkMatrix4<T> rm_t;
        rm_t.Clear();

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                rm_t.FMatrix[i][j] = rm.FMatrix[i][j] + f;

        return rm_t;
    }

    friend MkMatrix4<T> &operator+(MkMatrix4<T> &rm, MkMatrix4<T> &rm2)
    {
        static MkMatrix4<T> rm_t;
        rm_t.Clear();

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                rm_t.FMatrix[i][j] = rm.FMatrix[i][j] + rm2.FMatrix[i][j];

        return rm_t;
    }

    friend MkMatrix4<T> &operator-(MkMatrix4<T> &rm, T f)
    {
        static MkMatrix4<T> rm_t;
        rm_t.Clear();

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                rm_t.FMatrix[i][j] = rm.FMatrix[i][j] - f;

        return rm_t;
    }

    friend MkMatrix4<T> &operator-(MkMatrix4<T> &rm, MkMatrix4<T> &rm2)
    {
        static MkMatrix4<T> rm_t;
        rm_t.Clear();

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                rm_t.FMatrix[i][j] = rm.FMatrix[i][j] - rm2.FMatrix[i][j];

        return rm_t;
    }

    void Out(char *);
};

typedef MkMatrix4<double> MkMatrix4_d;

template <class T>
class MkVector : public MkAbstract
{ // for matrix calculation
private:
    MkArray<T> FVector; // only onedimesional
    int FSize;
    VectType FVectType;

public:
    MkVector();
    MkVector(int);
    MkVector(int, VectType);
    MkVector(const MkArray<T> &);
    MkVector(MkArray<T> &&);
    MkVector(T, T, T);
    ~MkVector();
    void SetVector(int);
    void SetVector(T, T, T);
    void Initialize(int i) { SetVector(i); };
    void SetVectType(VectType vt) { FVectType = vt; }
    void Clear(); // free all the memory and reset.
    void Unify();
    void Normalize() { Unify(); }

    T Dot(MkVector<T> &);
    void Cross(MkVector<T> &v2, MkVector<T> &target); // target = *this & v2 , peculier syntax...isn't it?
    // MkVector<T> &Cross(MkVector<T> &v2); // target = *this & v2 , much clear...isn't it?

    int GetFI() { return FSize; }
    int GetSize() { return FSize; }
    MkArray<T> &GetDouble() { return FVector; }
    MkArray<T> &Get() { return FVector; }

    T GetLength()
    {
        T sum = 0;
        for (int i = 0; i < FSize; i++)
            sum += FVector(i) * FVector(i);
        // return sum > 0 ? sqrt(sum) / FSize : 0; // TODO: check why it is divided by FSize and what is the impact if omitted, sure it is a bug...
        return sum > 0 ? sqrt(sum) : 0;        
    }

    T &operator()(int i);
    T &operator[](int i);
    MkVector<T> &operator=(const MkVector<T> &);
    MkVector<T> &operator=(MkVector<T> &&);
    bool operator==(MkVector<T> &);
    bool operator!=(MkVector<T> &);

    friend T operator*(MkVector<T> &v, MkVector<T> &v2) { return v.Dot(v2); };
    //    friend MkVector<T> & operator&(MkVector<T> &v, MkVector<T> &v2){return v.Cross(v2);}  // it is wrong...-.-

    MkVector<T> &operator+=(MkVector<T> &);
    MkVector<T> &operator-=(MkVector<T> &);
    MkVector<T> &operator*=(T a);
    MkVector<T> &operator/=(T a);
    MkVector<T> &operator+=(T a);
    MkVector<T> &operator-=(T a);

    friend MkVector<T> &operator+(MkVector<T> &v, MkVector<T> &v2)
    {
        static MkVector<T> v_t;
        const static MkVector<T> NullVector(0);
        if (v.FSize != v2.FSize)
            return NullVector;
        v_t.Initialize(v.FSize);
        for (int i = 0; i < v.FSize; i++)
            v_t.FVector(i) = v.FVector(i) + v2.FVector(i);
        return v_t;
    }
    friend MkVector<T> &operator-(MkVector<T> &v, MkVector<T> &v2)
    {
        static MkVector<T> v_t;
        const static MkVector<T> NullVector(0);
        if (v.FSize != v2.FSize)
            return NullVector;
        v_t.Initialize(v.FSize);
        for (int i = 0; i < v.FSize; i++)
            v_t.FVector(i) = v.FVector(i) + v2.FVector(i);
        return v_t;
    }
    friend MkVector<T> &operator*(MkVector<T> &v, T a)
    {
        static MkVector<T> v_t;

        v_t = v;
        for (int i = 0; i < v.FSize; i++)
            v_t.FVector(i) *= a;
        return v_t;
    }
    friend MkVector<T> &operator/(MkVector<T> &v, T a)
    {
        static MkVector<T> v_t;

        v_t = v;
        for (int i = 0; i < v.FSize; i++)
            v_t.FVector(i) /= a;
        return v_t;
    }
    friend MkVector<T> &operator+(MkVector<T> &v, T a)
    {
        static MkVector<T> v_t;
        v_t.Initialize(v.FSize);
        for (int i = 0; i < v.FSize; i++)
            v_t.FVector(i) = v.FVector(i) + a;
        return v_t;
    }
    friend MkVector<T> &operator-(MkVector<T> &v, T a)
    {
        static MkVector<T> v_t;
        v_t.Initialize(v.FSize);
        for (int i = 0; i < v.FSize; i++)
            v_t.FVector(i) = v.FVector(i) - a;
        return v_t;
    }

    void Out(char *);
};

// warning : MkMatrix instance will always be changed after some operator function
//           is applied. Therefore one must backup the original matrix for other
//           use. Moreover do not use operator such as ! or ~ more than twice,
//           because the accumulation of arithmetic error will alter the matrix.

//
//  A00 A01 A02 ... A0n
//  A10 A11 A12 ... A1n
//   .   .   .  ...  .
//  Am0 Am1 Am2 ... Amn
//
// class MkSparseMatrix;

template <class T>
class MkMatrix : public MkAbstract
{
private:
    MkArray<T> FMatrix;
    MkArray<int> FIndex; // row permutation effected by the partial pivoting
    int FD;              // + or - depend on whether the number of row interchanges was even or odd.
    int FI, FJ;
    MatType FMatType;

public:
    MkMatrix();
    MkMatrix(int, int);
    MkMatrix(const MkMatrix<T> &);
    MkMatrix(MkMatrix<T> &&);
    //  MkMatrix(MkSparseMatrix &);
    MkMatrix(const MkArray<T> &);
    MkMatrix(MkArray<T> &&);
    ~MkMatrix();
    void SetMatrix(int, int);
    void Initialize(int i, int j) { SetMatrix(i, j); }
    void Identify(); // valid only if FI == FJ
    void LoadIdentity() { Identify(); }
    void Clear(); // free all the memory and reset.
    bool Transpose();
    bool Invert();
    bool LUDecompose();
    bool LUBackSubstitute(MkVector<T> &);
    bool GaussSeidel(MkVector<T> &, MkVector<T> &);
    bool GaussSeidelDouble(MkVector<T> &, MkVector<T> &);
    bool isSingular();
    bool Solve(MkVector<T> &);
    bool Solve(MkVector<T> &, SolveType solve_type);

    int GetFI() { return FI; }
    int GetFJ() { return FJ; }
    MkArray<int> &GetIndex() { return FIndex; }
    MatType GetMatType() { return FMatType; }

    MkMatrix<T> &GetTranspose();
    MkMatrix<T> &GetInvert();

    MkMatrix<T> &operator!(); // GetInverse
    MkMatrix<T> &operator~(); // GetTranspos

    friend MkMatrix<T> &operator!(MkMatrix<T> &m) // GetInverse
    {
        static MkMatrix<T> m_t;
        m_t = m;
        return m_t.GetInvert();
    }

    friend MkMatrix<T> &operator~(MkMatrix<T> &m) // GetTranspos
    {
        static MkMatrix<T> m_t;
        m_t = m;
        return m_t.GetTranspose();
    }
    MkMatrix<T> &operator*=(MkMatrix<T> &);
    MkVector<T> &operator*=(MkVector<T> &);
    friend MkMatrix<T> &operator*(MkMatrix<T> &m, MkMatrix<T> &m2)
    {
        const static MkMatrix<T> NullMatrix(0);
        static MkMatrix<T> m_t;
        if (m.FJ != m2.FI)
            return NullMatrix;
        m_t.Initialize(m.FI, m2.FJ);
        T sum;
        for (int i = 0; i < m.FI; i++)
        {
            for (int j = 0; j < m2.FJ; j++)
            {
                sum = 0;
                for (int k = 0; k < m.FJ; k++)
                    sum += m.FMatrix(i, k) * m2.FMatrix(k, j);
                m_t(i, j) = sum;
            }
        }
        return m_t;
    }
    friend MkVector<T> &operator*(MkMatrix<T> &m, MkVector<T> &v)
    {
        static MkVector<T> NullVector(0);
        static MkVector<T> v_t;
        if (m.FJ != v.GetFI())
            return NullVector;
        v_t.Initialize(m.FI);
        T sum;
        for (int i = 0; i < m.FI; i++)
        {
            sum = 0;
            for (int j = 0; j < m.FJ; j++)
                sum += m.FMatrix(i, j) * v(j);
            v_t(i) = sum;
        }
        return v_t;
    }

    MkMatrix<T> &operator=(const MkMatrix<T> &);
    T &operator()(int i, int j);

    void Out(char *);
};

//---------------------------------------------------------------------------
#endif
