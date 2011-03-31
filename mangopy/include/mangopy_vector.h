#include "mangopy_python.h"

#include "core/vector.h"

#ifndef MANGOPY_CORE_VECTOR
#define MANGOPY_CORE_VECTOR

typedef struct {
    PyObject_HEAD
    Mango::Core::Vector v;
} mpy_Vector;

extern PyTypeObject mpy_VectorType;

mpy_Vector *mpy_Vector_NEW();

int mpy_VectorConverter(PyObject *arg, void *vector_address);
bool mpy_VectorFromArgs(PyObject *arg, Mango::Core::Vector &v);
bool mpy_ThreeDoublesFromArgs(PyObject *arg, double &x, double &y, double &z);

#endif // MANGOPY_CORE_VECTOR

