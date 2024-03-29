//---------------------------------------------------------------------------
#include "MkMisc.hpp"

namespace Mk
{
  int Delta = 10;
}

bool is_eq(double i, double j)
{
  return (fabs(i - j) < FTOL) ? true : false;
}

#ifndef min
int min(int x, int y)
{
  return (x >= y) ? y : x;
}

double min(double x, double y)
{
  return (x >= y) ? y : x;
}
#endif

#ifndef max
int max(int x, int y)
{
  return (x >= y) ? x : y;
}
double max(double x, double y)
{
  return (x >= y) ? x : y;
}
#endif

#if !defined(_MSC_VER) && !defined(_WINDOWS_)
void dull(const std::string __format, ...)
{
  printf("dull is called\n");
  return;
}
#endif

void dumprintf(const std::string __format, ...)
{
  return;
}

void swap(int &a, int &b)
{
  int tmp;
  tmp = a;
  a = b;
  b = tmp;
  return;
}

void swap(double &a, double &b)
{
  double tmp;
  tmp = a;
  a = b;
  b = tmp;
  return;
}

int delta(int a, int b)
{
  return (a == b) ? 1 : 0;
}

bool ExtractFileExt(std::string &ext, const std::string &str)
{
  auto pos = str.find('.');
  auto e = str.substr(pos);

  ext = std::move(e);

  // sprintf(s, "Extension of %s is %s\n", str.c_str(), ext.c_str());
  std::string s;
  s = "Extension of ";
  s += str + std::string("is ") + ext;
  // s = std::string("Extension of ") + str + std::string("is ") + ext + std::endl;

  MkDebug("%s",s.c_str());
  if (ext.size() != 0)
    return true;
  else
    return false;
}

bool ExtractFileExt(std::string &&ext, const std::string &&str)
{
  auto pos = str.find('.');
  auto e = str.substr(pos);

  ext = std::move(e);

  // sprintf(s, "Extension of %s is %s\n", str.c_str(), ext.c_str());
  std::string s;
  s = "Extension of ";
  s += str + std::string("is ") + ext;
  // s = std::string("Extension of ") + str + std::string("is ") + ext + std::endl;

  MkDebug("%s",s.c_str());
  if (ext.size() != 0)
    return true;
  else
    return false;
}

bool TrimLeft(std::string &dest, const std::string src)
{
  if (src.size() == 0)
    return false;

  const std::string WHITESPACE = " \n\r\t\f\v";

  size_t start = src.find_first_not_of(WHITESPACE);
  dest = (start == std::string::npos) ? std::move("") : std::move(src.substr(start));

  if (dest.size() != 0)
    return true;
  else
    return false;
}

// bool ExtractStr(std::string des, int n, const std::string src)
// {
//   std::string s, e;
//   int len, c = 0;

//   *des = '\0';
//   s = e = src;
//   while (n > c && e)
//   {
//     s = e;
//     TrimLeft(e, s);
//     len = strlen(e);
//     s = e;
//     e = strchr(s, ' ');
//     c++;
//   }

//   if (!e)
//     return false;

//   TrimLeft(e, e);
//   strcpy(des, e);
//   e = strchr(des, ' ');

//   if (e == NULL)
//     return false;
//   else if (*e == '\0')
//     return false;
//   else if (*e == ' ')
//     *e = '\0';
//   return true;
// }

bool ToLower(std::string str)
{
  char c;

  if (str.size() <= 0)
    return false;

  for (int i = 0; i < str.size() && str[i]; i++)
  {
    c = str[i];
    str[i] = tolower(c);
  }

  return true;
}

bool ToUpper(std::string str)
{
  char c;

  if (str.size() <= 0)
    return false;

  for (int i = 0; i < str.size() && str[i]; i++)
  {
    c = str[i];
    str[i] = toupper(c);
  }

  return true;
}

// bool ToOnlyAlpha(std::string &dest, std::string src)
// {
//   return false;
// }
// bool RemoveAnd(std::string &dest, std::string src)
// {
//   return false;
// }

// bool CompSub(std::string str, std::string txt)
// {
//   std::string a, *b;
//   int len;

//   if (!strlen(str))
//     return false;
//   if (!strlen(txt))
//     return false;

//   len = strlen(str);
//   len = min(len, strlen(txt));

//   a = new char[len + 1];
//   if (!a)
//     return false;
//   b = new char[len + 1];
//   if (!b)
//   {
//     delete a;
//     return false;
//   }

//   strncpy(a, str, len);
//   strncpy(b, txt, len);

//   ToLower(a);
//   ToLower(b);

//   return !strcmp(a, b);

//   delete a;
//   delete b;
// }

// int NumOfParam(std::string str)
// {
//   int n = 0;
//   std::string s, *e;
//   int len;

//   s = e = str;
//   while (e)
//   {
//     s = e;
//     TrimLeft(e, s);
//     len = strlen(e);
//     s = e;
//     e = strchr(s, ' ');
//     n++;
//   }
//   return n;
// }

// int NumOfParen(std::string str)
// {
//   int i, nl = 0, nr = 0;
//   for (i = 0; i < str.size(); i++)
//   {
//     if (str[i] == '(')
//       nl++;
//     if (str[i] == ')')
//       nr++;
//   }
//   if (nl == nr)
//     return nl;
//   else
//     return -1;
// }

// bool ExtractFromParen(std::string str, int n, double &x, double &y)
// {
//   std::string sp, ep;
//   int i, j = 0, nl = 0, nr = 0;

//   x = 0;
//   y = 0;

//   for (i = 0; i < str.size(); i++)
//   {
//     if (str[i] == '(')
//     {
//       if (n == nl)
//         sp = str + i + 1;
//       nl++;
//     }
//     if (str[i] == ')')
//     {
//       if (n == nr)
//       {
//         while (str[i - j] != ' ' && str[i - j] != ',')
//           j++;
//         if (str[i - j] == ' ' || str[i - j] == ',')
//           ep = str + i - j;
//       }
//       nr++;
//     }

//   }
//   if (sp.size() == 0 || ep.size() == 0)
//     return false;

//   sscanf(sp.c_str(), "%f ", &x);
//   sscanf(ep.c_str(), "%f ", &y);
//   return true;
// }

std::string ShortSteelName(std::string str)
{
  int i, pos, len;
  static char res[256];
  // need to be implemented
  return res;
}

bool IsNumber(std::string str)
{
  if (!str.size())
    return false;

  if (!str.compare("-"))
    return false;

  for (char const &c : str)
  {
    if (std::isdigit(c) == 0)
      return false;
  }
  return true;
}

// bool IsNumber(std::string str)
// {
//   if (!strlen(str))
//     return false;
//   !str.compare("-") if (!strcmp(str, "-")) return false;
//   for (int i = 0; i < strlen(str); i++)
//   {
//     if (!isdigit(str[i]) && str[i] != '-' && str[i] != '.')
//       return false;
//   }
//   return true;
// }

double ShapeFun1(double x, double l)
{
  double p;
  if (fabs(l) < EPS)
    return 0;
  p = x / l;
  return 1 - (3 - 2 * p) * p * p;
}

double ShapeFun2(double x, double l)
{
  double p;
  if (fabs(l) < EPS)
    return 0;
  p = x / l;
  return -x * (1 - p) * (1 - p);
}

double ShapeFun3(double x, double l)
{
  double p;
  if (fabs(l) < EPS)
    return 0;
  p = x / l;
  return (3 - 2 * p) * p * p;
}

double ShapeFun4(double x, double l)
{
  double p;
  if (fabs(l) < EPS)
    return 0;
  p = x / l;
  return x * p * (1 - p);
}

double ShapeFunInteg1(double aj, double bj, double l, double lj1, double lj)
{
  double lj1_2, lj1_3, lj1_4, lj1_5, lj_2, lj_3, lj_4, lj_5, l_2, l_3;
  if (fabs(l) < EPS)
    return 0;
  if (lj1 < lj)
    swap(lj1, lj);

  lj1_2 = lj1 * lj1;
  lj1_3 = lj1_2 * lj1;
  lj1_4 = lj1_2 * lj1_2;
  lj1_5 = lj1_4 * lj1;
  lj_2 = lj * lj;
  lj_3 = lj_2 * lj;
  lj_4 = lj_2 * lj_2;
  lj_5 = lj_4 * lj;
  l_2 = l * l;
  l_3 = l_2 * l;

  return aj * ((lj1_2 - lj_2) / 2 - 3 * (lj1_4 - lj_4) / 4 / l_2 + 2 * (lj1_5 - lj_5) / 5 / l_3) + bj * ((lj1 - lj) - (lj1_3 - lj_3) / l_2 + (lj1_4 - lj_4) / 2 / l_3);
}

double ShapeFunInteg2(double aj, double bj, double l, double lj1, double lj)
{
  double lj1_2, lj1_3, lj1_4, lj1_5, lj_2, lj_3, lj_4, lj_5, l_2, l_3;
  if (fabs(l) < EPS)
    return 0;
  if (lj1 < lj)
    swap(lj1, lj);

  lj1_2 = lj1 * lj1;
  lj1_3 = lj1_2 * lj1;
  lj1_4 = lj1_2 * lj1_2;
  lj1_5 = lj1_4 * lj1;
  lj_2 = lj * lj;
  lj_3 = lj_2 * lj;
  lj_4 = lj_2 * lj_2;
  lj_5 = lj_4 * lj;
  l_2 = l * l;
  l_3 = l_2 * l;

  return aj * (-(lj1_3 - lj_3) / 3 + (lj1_4 - lj_4) / 2 / l - (lj1_5 - lj_5) / 5 / l_2) + bj * (-(lj1_2 - lj_2) / 2 + 2 * (lj1_3 - lj_3) / 3 / l - (lj1_4 - lj_4) / 4 / l_2);
}

double ShapeFunInteg3(double aj, double bj, double l, double lj1, double lj)
{
  double lj1_2, lj1_3, lj1_4, lj1_5, lj_2, lj_3, lj_4, lj_5, l_2, l_3;
  if (fabs(l) < EPS)
    return 0;
  if (lj1 < lj)
    swap(lj1, lj);

  lj1_2 = lj1 * lj1;
  lj1_3 = lj1_2 * lj1;
  lj1_4 = lj1_2 * lj1_2;
  lj1_5 = lj1_4 * lj1;
  lj_2 = lj * lj;
  lj_3 = lj_2 * lj;
  lj_4 = lj_2 * lj_2;
  lj_5 = lj_4 * lj;
  l_2 = l * l;
  l_3 = l_2 * l;

  return aj * (3 * (lj1_4 - lj_4) / 4 / l_2 - 2 * (lj1_5 - lj_5) / 5 / l_3) + bj * ((lj1_3 - lj_3) / l_2 - (lj1_4 - lj_4) / 2 / l_3);
}

double ShapeFunInteg4(double aj, double bj, double l, double lj1, double lj)
{
  double lj1_2, lj1_3, lj1_4, lj1_5, lj_2, lj_3, lj_4, lj_5, l_2, l_3;
  if (fabs(l) < EPS)
    return 0;
  if (lj1 < lj)
    swap(lj1, lj);

  lj1_2 = lj1 * lj1;
  lj1_3 = lj1_2 * lj1;
  lj1_4 = lj1_2 * lj1_2;
  lj1_5 = lj1_4 * lj1;
  lj_2 = lj * lj;
  lj_3 = lj_2 * lj;
  lj_4 = lj_2 * lj_2;
  lj_5 = lj_4 * lj;
  l_2 = l * l;
  l_3 = l_2 * l;

  return aj * ((lj1_4 - lj_4) / 4 / l - (lj1_5 - lj_5) / 5 / l_2) + bj * ((lj1_3 - lj_3) / 3 / l - (lj1_4 - lj_4) / 4 / l_2);
}

double sosu1(double a)
{
  double b, n, m;

  m = a * 10.0;
  b = modf(m, &n);

  if (b >= 0.4999)
    n = n + 1.0;

  return n / 10.0;
}

double sosu2(double a)
{
  double b, n, m;

  m = a * 100.0;
  b = modf(m, &n);

  if (b >= 0.4999)
    n = n + 1.0;

  return n / 100.0;
}

double sosu3(double a)
{
  double b, n, m;

  m = a * 1000.0;
  b = modf(m, &n);

  if (b >= 0.4999)
    n = n + 1.0;

  return n / 1000.0;
}

double blength(double tlen, double alen)
{
  double b;

  b = tlen - alen;
  if (alen > b)
    ;
  else
  {
    for (int i = 1;; i++)
    {
      b = (tlen - 2.0 * alen) / i;
      if (alen > b)
        break;
    }
  }

  return b;
}

//---------------------------------------------------------------------------
