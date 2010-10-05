#include "Python.h"
#include "mango.h"
#include "mangopy_core.h"
#include "mangopy_pyengine.h"

#include "core/triangle.h"

#ifndef MANGOPY_CORE_TRIANGLE
#define MANGOPY_CORE_TRIANGLE

typedef struct {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Core::Triangle *internalObject;    
} mpy_Triangle;

extern PyTypeObject mpy_TriangleType;

#endif // MANGOPY_CORE_TRIANGLE

