#include "Python.h"
#include "geometry.h"
#include "mangopy.h"

#ifndef PYGEOMETRY_COLORFUL_OBJECT
#define PYGEOMETRY_COLORFUL_OBJECT

typedef struct {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Geometry::ColorfulObject *internalObject;
} mpy_ColorfulObject;

extern PyTypeObject mpy_ColorfulObjectType;

#endif // PYGEOMETRY_COLORFUL_OBJECT
