//---------------------------------------------------------------------------
#ifndef MkShapeH
#define MkShapeH

#include "MkPoint.hpp"

class MkShape
{
private:
     //     virtual void CalArea(){};
public:
#ifdef __BCPLUSPLUS__
     TColor Color;
     TPenStyle PenStyle;
#endif

public:
     MkShape()
     {
          NextShape = NULL;
          PrevShape = NULL;
     };
     ~MkShape();
     MkShape *Next() { return NextShape; };
     MkShape *Prev() { return PrevShape; };

     virtual double GetArea()
     {
          return 0;
     }
     virtual std::string ClassName()
     {
          return std::string("MkShape");
     }

     virtual bool isTriangle()
     {
          return false;
     }
     virtual bool isRect() { return false; }
     virtual bool isCube() { return false; }
     virtual bool isCircle() { return false; }
     virtual bool isSphere() { return false; }
     virtual bool isCylinder() { return false; }

     virtual void operator=(MkShape &ms)
     {
#ifdef __BCPLUSPLUS__
          Color = ms.Color;
          PenStyle = ms.PenStyle;
#endif
          NextShape = ms.NextShape;
          PrevShape = ms.PrevShape;
          return;
     }

     virtual void operator=(MkShape &&ms)
     {
#ifdef __BCPLUSPLUS__
          Color = ms.Color;
          PenStyle = ms.PenStyle;
#endif
          NextShape = ms.NextShape;
          PrevShape = ms.PrevShape;
          return;
     }

     virtual bool operator==(MkShape &ms);
     virtual bool operator==(MkShape &&ms);
     virtual bool operator!=(MkShape &ms);
     virtual bool operator!=(MkShape &&ms);
     virtual bool IsInSurface(MkPoint &pnt, double thick) { return false; }
     virtual bool IsInSurface(MkPoint &&pnt, double thick) { return false; }
     virtual bool IsInSpace(MkPoint &pnt) { return false; }
     virtual bool IsInSpace(MkPoint &&pnt) { return false; }
     //     virtual MkShape operator=(MkShape &ms);
public:
     MkShape *NextShape;
     MkShape *PrevShape;

#ifdef __BCPLUSPLUS__
     virtual void Draw(TObject *)
     {
          MkDebug("Pure virtual function MkShape::Draw() is called\n");
     }
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
     virtual void Draw(MkPaint *)
     {
          MkDebug("Pure virtual function MkShape::Draw() is called\n");
     }
#endif
};

//---------------------------------------------------------------------------
// �� class������ � ������ �޸� �Ҵ絵 �Ͼ�� �ʴ´�.
class MkShapeList
{ // �ͳγ��� �� �κ� : ���̴�, ������ ��
private:
     MkShape *FirstMyShapes;
     MkShape *CurrentMyShapes;
     MkShape *LastMyShapes;
     int NumberOfShape;

public:
     MkShapeList(MkShape *);
     MkShapeList();
     ~MkShapeList();
     bool Add(MkShape *);
     bool Insert(MkShape *);
     bool Delete(MkShape *); // �� ������ ����Ʈ&�޸� ���Ŵ� �ƴ�.
     bool Clear();           // ��� ����Ʈ �Ӹ� �ƴ϶� �޸𸮵� ����
     double GetArea();
     int GetNumberOfShape() { return NumberOfShape; }
     MkShape &operator[](int i);
     MkShapeList &operator=(MkShapeList &sl);

#ifdef __BCPLUSPLUS__
     void Draw(TObject *);
#endif

#if defined(_MSC_VER) && defined(_WINDOWS_)
     void Draw(MkPaint *);
#endif
};
//---------------------------------------------------------------------------
#endif
