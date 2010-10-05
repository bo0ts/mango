#include "Python.h"
#include "mango.h"
#include "mangopy_core.h"
#include "mangopy_pyengine.h"

#include "core/input.h"

#ifndef MANGOPY_CORE_KEYBOARD
#define MANGOPY_CORE_KEYBOARD

typedef struct {
    PyObject_HEAD
    Mango::Core::CoreKeyboard *internalObject;    
} mpy_CoreKeyboard;

extern PyTypeObject mpy_CoreKeyboardType;

mpy_CoreKeyboard *mpy_CoreKeyboard_NEW();

#endif // MANGOPY_CORE_KEYBOARD
