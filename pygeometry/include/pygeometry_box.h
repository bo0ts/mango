#include "mangopy_python.h"
#include "geometry.h"
#include "mangopy.h"

#ifndef PYGEOMETRY_BOX
#define PYGEOMETRY_BOX

typedef struct {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Geometry::Box *internalObject;
} mpy_Box;

extern PyTypeObject mpy_BoxType;

#endif // PYGEOMETRY_BOX 
