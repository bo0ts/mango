#include "Mango/mangopy.h"
#include "tetrahedron.h"
#include "pytetrahedron.h"

using namespace std;
using namespace Mango;

// ---------------------------

int mpy_Tetrahedron_init(mpy_Object *self, PyObject *args, PyObject *kw);

static PyModuleDef solids_module_def = {
    PyModuleDef_HEAD_INIT,
    "Solids",
    "Platonic solids",
    -1,
    NULL, NULL, NULL, NULL, NULL
};





// ---------------------------

PyMODINIT_FUNC PyInit_Solids(void){
  PyObject* m;
  
  m = PyModule_Create(&solids_module_def);
  if (m == NULL){
    return NULL;
  }

  if (MangoPy::initialize_module_environment()){
    return NULL;
  }
  
  PyTypeObject *dynamic_mpy_object_type = MangoPy::py_type_object("mangopy.core.object");
  if (dynamic_mpy_object_type == NULL){
    return NULL;
  }

  mpy_addObjectToModule(m, &mpy_TetrahedronType, dynamic_mpy_object_type, "Tetrahedron");
  MangoPy::register_py_type_object("pysolids.tetrahedron", &mpy_TetrahedronType);

  // Add Constants
  PyModule_AddIntConstant(m, "GOLDEN_RATION", 1.61803399);

  return m;
}
