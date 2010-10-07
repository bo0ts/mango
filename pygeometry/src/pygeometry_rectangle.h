#include "mangopy_python.h"
#include "geometry.h"
#include "mangopy.h"

#ifndef PYGEOMETRY_RECTANGLE
#define PYGEOMETRY_RECTANGLE

typedef struct {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Geometry::Rectangle *internalObject;
} mpy_Rectangle;

extern PyTypeObject mpy_RectangleType;

#endif // PYGEOMETRY_RECTANGLE 
