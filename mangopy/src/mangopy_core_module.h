#include "mangopy_python.h"
#include <vector>
#include "mango.h"
#include "mangopy_vector.h"
#include "mangopy_input_event.h"
#include "mangopy_pyengine.h"

#ifndef MANGOPY_CORE_MODULE
#define MANGOPY_CORE_MODULE

extern PyTypeObject mpy_ObjectType;
int mpy_Object_init(mpy_Object *self, PyObject *args, PyObject *kw);



static PyModuleDef core_module_def = {
    PyModuleDef_HEAD_INIT,
    "Core",
    "Mango core",
    -1,
    NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC PyInit_Core(void);


#endif // MANGOPY_CORE_MODULE
