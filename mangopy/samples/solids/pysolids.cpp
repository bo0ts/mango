#include "mangopy.h"
#include "pytetrahedron.h"

// Module definition object
static PyModuleDef solids_module_def = {
    PyModuleDef_HEAD_INIT,
    "Solids",                // Module name
    "Platonic solids",       // Module doc string
    -1,
    NULL, NULL, NULL, NULL, NULL
};


// Module init function
PyMODINIT_FUNC PyInit_Solids(void){
  PyObject* m;
  
  // Create a module. This is standard Python extension code
  m = PyModule_Create(&solids_module_def);
  if (m == NULL){
    return NULL; // Returning NULL indicates a failure and will
                 // cause an exception to be raised in the embedded Python 
                 // interpreter - an error message must be set 
                 // independently, but this is often done by the originally
                 // failing method, in this case PyModule_Create
  }

  // Let Mangopy do some module initialization
  if (MangoPy::initialize_module_environment()){
    return NULL;
  }

  // Dynamically retrieve the Core::Object type-object, so that we may use it
  // to indicate that Solids::Tetrahedron derives from Core::Object
  PyTypeObject *dynamic_mpy_object_type = MangoPy::py_type_object("mangopy.core.object");
  if (dynamic_mpy_object_type == NULL){
    return NULL;
  }

  // Add a new object type to the newly created module
  // The arguments are (<module object>, <pointer to new type>, 
  //                    <pointer to parent type>, <name>)
  // The new type is then registered with Mangopy, so that other extensions
  // may use it as a base type like mangopy.core.object is used here
  mpy_addObjectToModule(m, &mpy_TetrahedronType, dynamic_mpy_object_type, "Tetrahedron");
  MangoPy::register_py_type_object("pysolids.tetrahedron", &mpy_TetrahedronType);

  // Add a constant. This is also standard Python extension code
  // This constant wasn't defined in the c++ header and is included 
  // purely to demonstrate how a constant may be added
  PyModule_AddIntConstant(m, "GOLDEN_RATION", 1.61803399);

  return m;
}
