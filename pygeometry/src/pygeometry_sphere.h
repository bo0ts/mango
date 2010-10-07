#include "mangopy_python.h"
#include "geometry.h"
#include "mangopy.h"

#ifndef PYGEOMETRY_SPHERE
#define PYGEOMETRY_SPHERE

typedef struct {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Geometry::Sphere *internalObject;
} mpy_Sphere;

extern PyTypeObject mpy_SphereType;

#endif // PYGEOMETRY_SPHERE
