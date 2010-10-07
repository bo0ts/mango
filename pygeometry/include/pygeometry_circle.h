#include "mangopy_python.h"
#include "geometry.h"
#include "mangopy.h"

#ifndef PYGEOMETRY_CIRCLE
#define PYGEOMETRY_CIRCLE

typedef struct {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Geometry::Circle *internalObject;
} mpy_Circle;

extern PyTypeObject mpy_CircleType;

#endif // PYGEOMETRY_CIRCLE 
