#include "Mango/mangopy.h"
#include "tetrahedron.h" 

#ifndef MPY_SOLIDS_PYTETRAHEDRON
#define MPY_SOLIDS_PYTETRAHEDRON

typedef struct {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Solids::Tetrahedron *internalObject;
} mpy_Tetrahedron;

extern PyTypeObject mpy_TetrahedronType;
PyObject *mpy_Tetrahedron_setHeight(mpy_Tetrahedron* self, PyObject *args);
PyObject *mpy_Tetrahedron_height(mpy_Tetrahedron* self, PyObject *args);

#endif // MPY_SOLIDS_PYTETRAHEDRON
