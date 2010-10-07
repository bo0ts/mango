#include "mangopy_python.h"
#include "geometry.h"
#include "mangopy.h"

#ifndef PYGEOMETRY_ARROW
#define PYGEOMETRY_ARROW

typedef struct {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Geometry::Arrow *internalObject;
} mpy_Arrow;

extern PyTypeObject mpy_ArrowType;

#endif // PYGEOMETRY_ARROW 
