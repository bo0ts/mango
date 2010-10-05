#include "Python.h"
#include "structmember.h"
#include "mango.h"
#include "mangopy_core.h"

#ifndef MANGOPY_CORE_MATRIX
#define MANGOPY_CORE_MATRIX

typedef struct {
    PyObject_HEAD
    Mango::Core::Matrix M;
} mpy_Matrix;

extern PyTypeObject mpy_MatrixType;

mpy_Matrix *mpy_Matrix_NEW();

#endif // MANGOPY_CORE_MATRIX

