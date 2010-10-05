#include "Python.h"
#include "geometry.h"
#include "mangopy.h"

#ifndef PYGEOMETRY_SHELL
#define PYGEOMETRY_SHELL

typedef struct {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Geometry::Shell *internalObject;
} mpy_Shell;

extern PyTypeObject mpy_ShellType;

#endif // PYGEOMETRY_SHELL 
