//---------------------------------------------------------------------------
#ifndef MkMiscH
#define MkMiscH
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define FTOL 1.0e-6
#define EPS 1.0e-4
#define TINY 1.0e-20
// #define PI 3.1415926535

#ifndef M_PI 
#define M_PI 3.14159265358979323846
#endif


// #define MPa2KPa 1.0e3
// #define KPa2MPa 1.0e-3
// #define MPa2Tonf 1.0e2
// #define Tonf2MPa 1.0e-2
// #define KPa2Tonf 1.0e-1
// #define Tonf2KPa 1.0e+1

#define MPa2KPa 1
#define KPa2MPa 1
#define MPa2Tonf 1
#define Tonf2MPa 1
#define KPa2Tonf 1
#define Tonf2KPa 1

#ifndef MAX_VAL
#define MAX_VAL 1.0e+6
#endif

#ifdef MKDEBUG
#define MkDebug printf
#else
#define MkDebug dumprintf
#endif

namespace Mk
{
   extern int Delta;

}

enum VectType
{
   vtRow,
   vtCol,
   vtNone
};
enum MatType
{
   mtNormal,
   mtLUDecomposed,
   mtBackSubstitute,
   mtInverted,
   mtTransposed,
   mtGauss,
   mtRow,
   mtCol
};
enum SolveType
{
   stLUD,
   stGauss,
   stHybrid
};
enum MkSteelType
{
   stHBEAM,
   stIBEAM,
   stCHANNEL,
   stANGLE,
   stSHEETPILE
};

bool is_eq(double i, double j);

#ifndef min
int min(int x, int y);
double min(double x, double y);
#endif
#ifndef max
int max(int x, int y);
double max(double x, double y);
#endif

#if !defined(_MSC_VER) && !defined(_WINDOWS_)
void dull(const std::string __format, ...);
#endif

void dumprintf(const std::string __format, ...);

void swap(int &x, int &y);
void swap(double &x, double &y);
#ifdef __BCPLUSPLUS__
void swap(TColor a, TColor b);
void Swap(TObject *Sender, int i, int j);
#endif

int delta(int a, int b);
bool ExtractFileExt(std::string &ext, const std::string &str); // ext must have a memory
bool TrimLeft(std::string &dest, const std::string src);
bool ToLower(std::string str);
bool ToUpper(std::string str);
// bool ExtractStr(std::string des, int n, const std::string src);

// bool ToOnlyAlpha(std::string &dest, std::string src);
// bool RemoveAnd(std::string &dest, std::string src);

// bool CompSub(std::string str, std::string txt);
// int NumOfParam(std::string str);
// int NumOfParen(std::string str);
// bool ExtractFromParen(std::string str, int n, double &x, double &y); // TODO: figure out what this is doing???

std::string ShortSteelName(std::string str);

bool IsNumber(std::string str);

double ShapeFun1(double x, double l);
double ShapeFun2(double x, double l);
double ShapeFun3(double x, double l);
double ShapeFun4(double x, double l);

double ShapeFunInteg1(double aj, double bj, double l, double lj1, double lj);
double ShapeFunInteg2(double aj, double bj, double l, double lj1, double lj);
double ShapeFunInteg3(double aj, double bj, double l, double lj1, double lj);
double ShapeFunInteg4(double aj, double bj, double l, double lj1, double lj);

struct MkOrient
{
   double DipDir;
   double Dip;
   MkOrient()
   {
      DipDir = 0;
      Dip = 0;
   }
   MkOrient(double dip, double dd)
   {
      Dip = dip;
      DipDir = dd;
   }
   MkOrient &operator=(MkOrient &jn)
   {
      DipDir = jn.DipDir;
      Dip = jn.Dip;
      return *this;
   }
   bool operator==(MkOrient &fo) { return (DipDir == fo.DipDir) && (Dip == fo.Dip); }
};

double sosu1(double a);
double sosu2(double a);
double sosu3(double a);
//---------------------------------------------------------------------------
#endif
