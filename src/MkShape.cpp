//---------------------------------------------------------------------------
// This module is general purposed simple graphic class to store, draw,
// manipulate object. It is well suited to VCL component, but not restricted.
// It forms the base for the higher level class, such as tunnel component.
//
// Copyright (c) 1999 Myung Kyu Song, ESCO Consultant Co., Ltd.#include <vcl.h>
//---------------------------------------------------------------------------
// TODO: need to implement the test code especially the ShapeList class,
//       because I am not sure if the add and delete member function is
//       working properly. 23.04.25
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#ifdef __BCPLUSPLUS__
#pragma package(smart_init)
#endif
//---------------------------------------------------------------------------
#include "MkShape.hpp"
#include "MkLine.hpp"
#include "MkCircle.hpp"
#include "MkCube.hpp"
#include "MkCylinder.hpp"
#include "MkRect.hpp"
#include "MkSphere.hpp"
#include "MkTriangle.hpp"

#ifdef __BCPLUSPLUS__
#include "Graphics.hpp"
#include "MkPaintBox.h"
#endif


bool MkShape::operator==(MkShape &ms)
{
  if (isTriangle() && ms.isTriangle())
  {
    MkTriangle *ta, *tb;
    ta = (MkTriangle *)this;
    tb = (MkTriangle *)&ms;
    return *ta == *tb;
  }
  else if (isRect() && ms.isRect())
  {
    MkRect *ra, *rb;
    ra = (MkRect *)this;
    rb = (MkRect *)&ms;
    return *ra == *rb;
  }
  else if (isCube() && ms.isCube())
  {
    MkCube *ca, *cb;
    ca = (MkCube *)this;
    cb = (MkCube *)&ms;
    return *ca == *cb;
  }
  else if (isCircle() && ms.isCircle())
  {
    MkCircle *ca, *cb;
    ca = (MkCircle *)this;
    cb = (MkCircle *)&ms;
    return *ca == *cb;
  }
  else if (isSphere() && ms.isSphere())
  {
    MkSphere *sa, *sb;
    sa = (MkSphere *)this;
    sb = (MkSphere *)&ms;
    return *sa == *sb;
  }
  else if (isCylinder() && ms.isCylinder())
  {
    MkCylinder *ca, *cb;
    ca = (MkCylinder *)this;
    cb = (MkCylinder *)&ms;
    return *ca == *cb;
  }

  MkDebug("MkShape::operator==() is called.\n");
  return false;
}

bool MkShape::operator==(MkShape &&ms)
{
  if (isTriangle() && ms.isTriangle())
  {
    MkTriangle *ta, *tb;
    ta = (MkTriangle *)this;
    tb = (MkTriangle *)&ms;
    return *ta == *tb;
  }
  else if (isRect() && ms.isRect())
  {
    MkRect *ra, *rb;
    ra = (MkRect *)this;
    rb = (MkRect *)&ms;
    return *ra == *rb;
  }
  else if (isCube() && ms.isCube())
  {
    MkCube *ca, *cb;
    ca = (MkCube *)this;
    cb = (MkCube *)&ms;
    return *ca == *cb;
  }
  else if (isCircle() && ms.isCircle())
  {
    MkCircle *ca, *cb;
    ca = (MkCircle *)this;
    cb = (MkCircle *)&ms;
    return *ca == *cb;
  }
  else if (isSphere() && ms.isSphere())
  {
    MkSphere *sa, *sb;
    sa = (MkSphere *)this;
    sb = (MkSphere *)&ms;
    return *sa == *sb;
  }
  else if (isCylinder() && ms.isCylinder())
  {
    MkCylinder *ca, *cb;
    ca = (MkCylinder *)this;
    cb = (MkCylinder *)&ms;
    return *ca == *cb;
  }

  MkDebug("MkShape::operator==() is called.\n");
  return false;
}

bool MkShape::operator!=(MkShape &ms)
{
  if (isTriangle() && ms.isTriangle())
  {
    MkTriangle *ta, *tb;
    ta = (MkTriangle *)this;
    tb = (MkTriangle *)&ms;
    return *ta != *tb;
  }
  else if (isRect() && ms.isRect())
  {
    MkRect *ra, *rb;
    ra = (MkRect *)this;
    rb = (MkRect *)&ms;
    return *ra != *rb;
  }
  else if (isCube() && ms.isCube())
  {
    MkCube *ca, *cb;
    ca = (MkCube *)this;
    cb = (MkCube *)&ms;
    return *ca != *cb;
  }
  else if (isCircle() && ms.isCircle())
  {
    MkCircle *ca, *cb;
    ca = (MkCircle *)this;
    cb = (MkCircle *)&ms;
    return *ca != *cb;
  }
  else if (isSphere() && ms.isSphere())
  {
    MkSphere *sa, *sb;
    sa = (MkSphere *)this;
    sb = (MkSphere *)&ms;
    return *sa != *sb;
  }
  else if (isCylinder() && ms.isCylinder())
  {
    MkCylinder *ca, *cb;
    ca = (MkCylinder *)this;
    cb = (MkCylinder *)&ms;
    return *ca != *cb;
  }

  MkDebug("MkShape::operator!=() is called.\n");
  return true;
}

bool MkShape::operator!=(MkShape &&ms)
{
  if (isTriangle() && ms.isTriangle())
  {
    MkTriangle *ta, *tb;
    ta = (MkTriangle *)this;
    tb = (MkTriangle *)&ms;
    return *ta != *tb;
  }
  else if (isRect() && ms.isRect())
  {
    MkRect *ra, *rb;
    ra = (MkRect *)this;
    rb = (MkRect *)&ms;
    return *ra != *rb;
  }
  else if (isCube() && ms.isCube())
  {
    MkCube *ca, *cb;
    ca = (MkCube *)this;
    cb = (MkCube *)&ms;
    return *ca != *cb;
  }
  else if (isCircle() && ms.isCircle())
  {
    MkCircle *ca, *cb;
    ca = (MkCircle *)this;
    cb = (MkCircle *)&ms;
    return *ca != *cb;
  }
  else if (isSphere() && ms.isSphere())
  {
    MkSphere *sa, *sb;
    sa = (MkSphere *)this;
    sb = (MkSphere *)&ms;
    return *sa != *sb;
  }
  else if (isCylinder() && ms.isCylinder())
  {
    MkCylinder *ca, *cb;
    ca = (MkCylinder *)this;
    cb = (MkCylinder *)&ms;
    return *ca != *cb;
  }

  MkDebug("MkShape::operator!=() is called.\n");
  return true;
}

MkShapeList::MkShapeList()
{
  FirstMyShapes = NULL;
  CurrentMyShapes = NULL;
  LastMyShapes = NULL;
  NumberOfShape = 0;
}

MkShapeList::MkShapeList(boost::shared_ptr<MkShape> ms)
{
  FirstMyShapes = ms;
  FirstMyShapes->NextShape = NULL;
  FirstMyShapes->PrevShape = NULL;
  CurrentMyShapes = ms;
  CurrentMyShapes->NextShape = NULL;
  CurrentMyShapes->PrevShape = NULL;
  LastMyShapes = ms;
  LastMyShapes->NextShape = NULL;
  LastMyShapes->PrevShape = NULL;

  NumberOfShape = 1;
}

MkShapeList::~MkShapeList()
{
  while (CurrentMyShapes)
    Delete(CurrentMyShapes);
  NumberOfShape = 0;
  FirstMyShapes = NULL;
  CurrentMyShapes = NULL;
  LastMyShapes = NULL;
}

bool MkShapeList::Add(boost::shared_ptr<MkShape> ms)
{
  if (LastMyShapes == NULL)
  {
    FirstMyShapes = ms;
    FirstMyShapes->NextShape = NULL;
    FirstMyShapes->PrevShape = NULL;
    CurrentMyShapes = ms;
    CurrentMyShapes->NextShape = NULL;
    CurrentMyShapes->PrevShape = NULL;
    LastMyShapes = ms;
    LastMyShapes->NextShape = NULL;
    LastMyShapes->PrevShape = NULL;
    NumberOfShape++;
    return true;
  }
  else
    LastMyShapes->NextShape = ms;

  ms->NextShape = NULL;
  ms->PrevShape = LastMyShapes;
  LastMyShapes = ms;
  NumberOfShape++;
  return true;
}

// TODO:
bool MkShapeList::Insert(boost::shared_ptr<MkShape> ms) // Not implemented yet, but it will be used
{                                   // when new object inserted current position.
  return true;
}


bool MkShapeList::Delete(boost::shared_ptr<MkShape> ms)
{
  boost::shared_ptr<MkShape> cur = FirstMyShapes;

  for (int i = 0; i < NumberOfShape; i++, cur = cur->Next())
  {
    if (cur == ms)
      break;
  }
  
  if (cur == ms)
  {
    if (cur->Prev())
    {
      cur->PrevShape->NextShape = cur->Next();
    }
    else
    {
      FirstMyShapes = cur->Next();
      if (FirstMyShapes)
        FirstMyShapes->PrevShape = NULL; // TODO: not sure this is correct, or do we need to call reset() instead?
    }
    if (cur->Next())
      cur->NextShape->PrevShape = cur->Prev();
    else
    {
      LastMyShapes = cur->Prev();
      if (LastMyShapes)
        LastMyShapes->NextShape = NULL; // TODO: not sure this is correct, or do we need to call reset() instead?
    }
    if (cur == CurrentMyShapes)
    {
      if (cur->Prev())
        CurrentMyShapes = cur->Prev();
      else if (cur->Next())
        CurrentMyShapes = cur->Next();
      else
        CurrentMyShapes = NULL;
    }

    ms.reset();
    NumberOfShape--;  // TODO: check this
    return true;
  }
  else
    return false;
}

bool MkShapeList::Clear()
{
  bool flag = true;
  boost::shared_ptr<MkShape> cur = LastMyShapes;

  if (!cur)
    return true;

  while (flag && LastMyShapes != FirstMyShapes)
  {
    flag = Delete(cur);
    cur = LastMyShapes;
  }
  if (flag)
  {
    Delete(FirstMyShapes);
    // it is smart pointer, so it is not necessary
    // FirstMyShapes = NULL; 
    // CurrentMyShapes = NULL;
    // LastMyShapes = NULL;
    NumberOfShape = 0;
    return true;
  }
  else
    return false;
}

double MkShapeList::GetArea()
{
  return 0; // TODO: not implemented yet
}

#ifdef __BCPLUSPLUS__
void MkShapeList::Draw(TObject *Sender)
{
  if (String(Sender->ClassName()) == String("MkPaintBox"))
  {
    MkPaintBox *pb = (MkPaintBox *)Sender;
    for (int i = 0; i < GetNumberOfShape(); i++)
    {
      (*this)[i].Draw(pb);
    }
  }
}
#endif

MkShape &MkShapeList::operator[](int i)
{
  boost::shared_ptr<MkShape> ms;
  if (i > NumberOfShape)
    throw;
  ms = FirstMyShapes;
  for (int j = 0; j < i; j++)
    ms = ms->NextShape;
  return *ms;
}

MkShapeList &MkShapeList::operator=(MkShapeList &sl)
{
  //    MkShape *ms;
  this->~MkShapeList();
  for (int i = 0; i < sl.NumberOfShape; i++)
  {
    if (sl[i].ClassName().compare( std::string("MkLine"))== 0) 
    {
      boost::shared_ptr<MkLine> ms;
      ms = boost::make_shared<MkLine>((MkLine &)sl[i]);
      Add(ms);
    }
    else if (sl[i].ClassName().compare( std::string("MkArc"))== 0) 
    {
      boost::shared_ptr<MkArc> ms;
      ms = boost::make_shared<MkArc>((MkArc &)sl[i]);
      Add(ms);
    }
    else if (sl[i].ClassName().compare( std::string("MkCircle"))== 0) 
    {
      boost::shared_ptr<MkCircle> ms;
      ms = boost::make_shared<MkCircle>((MkCircle &)sl[i]);
      Add(ms);
    }
    else
    {
      MkDebug("Error MkShapeList operator=");
      boost::shared_ptr<MkShape> ms;
      ms = boost::make_shared<MkShape>(sl[i]);
      Add(ms);
    }
  }
  return (*this);
}

//---------------------------------------------------------------------------
