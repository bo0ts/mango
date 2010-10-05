#include "Python.h"
#include "geometry.h"
#include "mangopy.h"

#ifndef PYGEOMETRY_NGON
#define PYGEOMETRY_NGON

typedef struct {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Geometry::NGon *internalObject;
} mpy_NGon;

extern PyTypeObject mpy_NGonType;

#endif // PYGEOMETRY_NGON 
