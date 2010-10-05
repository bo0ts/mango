#include "Python.h"
#include <vector>
#include "mango.h"
#include "mangopy_vector.h"
#include "mangopy_input_event.h"
#include "mangopy_pyengine.h"


#ifndef MANGOPY_CORE
#define MANGOPY_CORE
#include "mangopy_matrix.h"
#include "mangopy_frame.h"

#define EVT_CORE 1
#define EVT_SCRIPTED 2
#define EVT_BOTH (EVT_CORE | EVT_SCRIPTED)


typedef struct {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Core::Object *internalObject;
} mpy_Object;


PyObject *pythonExceptionFromCException(Mango::Core::Error &e);
PyObject *mpy_addObjectToModule(PyObject *module, PyTypeObject *object, PyTypeObject *base_class, const char *name, bool force_generic_new = false);


#endif // MANGOPY_CORE
