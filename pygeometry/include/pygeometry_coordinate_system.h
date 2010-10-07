#include "mangopy_python.h"
#include "geometry.h"
#include "mangopy.h"

#ifndef PYGEOMETRY_COORDINATESYSTEM
#define PYGEOMETRY_COORDINATESYSTEM

typedef struct {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Geometry::CoordinateSystem *internalObject;
} mpy_CoordinateSystem;

extern PyTypeObject mpy_CoordinateSystemType;

#endif // PYGEOMETRY_COORDINATESYSTEM 
