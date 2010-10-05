#include "Python.h"
#include "geometry.h"
#include "mangopy.h"

#ifndef PYGEOMETRY_CYLINDER
#define PYGEOMETRY_CYLINDER

typedef struct {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Geometry::Cylinder *internalObject;
} mpy_Cylinder;

extern PyTypeObject mpy_CylinderType;

#endif // PYGEOMETRY_CYLINDER 
