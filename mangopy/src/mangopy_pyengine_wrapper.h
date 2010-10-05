#ifndef MPY_PYENGINE_WRAPPER
#define MPY_PYENGINE_WRAPPER

#include "mangopy.h"


typedef struct {
    PyObject_HEAD
    //PyEngine *internalObject;
    Mango::Core::CoreEngine *internalObject;
} mpy_PyEngine;

extern PyTypeObject mpy_PyEngineType;
mpy_PyEngine *mpy_PyEngine_NEW();

#endif // MPY_PYENGINE_WRAPPER 
