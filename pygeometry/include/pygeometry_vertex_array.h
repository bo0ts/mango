#include "mangopy_python.h"
#include "geometry.h"
#include "mangopy.h"

#ifndef PYGEOMETRY_VERTEXARRAY
#define PYGEOMETRY_VERTEXARRAY

typedef struct {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Geometry::VertexArray *internalObject;
} mpy_VertexArray;

extern PyTypeObject mpy_VertexArrayType;

#endif // PYGEOMETRY_VERTEXARRAY 
