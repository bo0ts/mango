#include "Python.h"
#include "mango.h"
#include "mangopy_core.h"
#include "mangopy_pyengine.h"

#include "core/input.h"

#ifndef MANGOPY_CORE_MOUSE
#define MANGOPY_CORE_MOUSE

typedef struct {
    PyObject_HEAD
    Mango::Core::CoreMouse *internalObject;    
} mpy_CoreMouse;

extern PyTypeObject mpy_CoreMouseType;

mpy_CoreMouse *mpy_CoreMouse_NEW();

#endif // MANGOPY_CORE_MOUSE

