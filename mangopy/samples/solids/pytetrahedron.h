#include "mangopy.h"
#include "tetrahedron.h" 

#ifndef MPY_SOLIDS_PYTETRAHEDRON
#define MPY_SOLIDS_PYTETRAHEDRON


// Tetrahedron struct definition. Only the  name of the struct and the type 
// of internalObject may vary. internalObject  must be a pointer to a class 
// derived from Core::Object.
typedef struct {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Solids::Tetrahedron *internalObject;
} mpy_Tetrahedron;

// Expose the type defition object and methods for manipulating 
// Python-wrapped Tetrahedron objects in C++
extern PyTypeObject mpy_TetrahedronType;
PyObject *mpy_Tetrahedron_setHeight(mpy_Tetrahedron* self, PyObject *args);
PyObject *mpy_Tetrahedron_height(mpy_Tetrahedron* self, PyObject *args);

#endif // MPY_SOLIDS_PYTETRAHEDRON
