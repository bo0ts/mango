#include "mangopy_python.h"
#include "mango.h"
#include "mangopy_core.h"
#include "mangopy_pyengine.h"

// # include "core/core.h"

#ifndef MANGOPY_CORE_CAMERA
#define MANGOPY_CORE_CAMERA

typedef struct {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Core::CoreCamera *internalObject;    
} mpy_CoreCamera;

extern PyTypeObject mpy_CoreCameraType;

mpy_CoreCamera *mpy_CoreCamera_NEW();

#endif // MANGOPY_CORE_CAMERA

