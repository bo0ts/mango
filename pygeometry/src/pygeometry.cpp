#include "pygeometry.h"

PyMODINIT_FUNC PyInit_Geometry(void){
  PyObject* m;
  
  m = PyModule_Create(&geometry_module_def);
  if (m == NULL){
    return NULL;
  }

  mpy_addObjectToModule(m, &mpy_ColorfulObjectType, &mpy_ObjectType, "ColorfulObject");
  mpy_addObjectToModule(m, &mpy_SphereType, &mpy_ColorfulObjectType, "Sphere");
  mpy_addObjectToModule(m, &mpy_BoxType, &mpy_ColorfulObjectType, "Box");
  mpy_addObjectToModule(m, &mpy_CylinderType, &mpy_ColorfulObjectType, "Cylinder");
  mpy_addObjectToModule(m, &mpy_ShellType, &mpy_ColorfulObjectType, "Shell");
  mpy_addObjectToModule(m, &mpy_ArrowType, &mpy_ColorfulObjectType, "Arrow");
  mpy_addObjectToModule(m, &mpy_CoordinateSystemType, &mpy_ColorfulObjectType, "CoordinateSystem");
  mpy_addObjectToModule(m, &mpy_VertexArrayType, &mpy_ColorfulObjectType, "VertexArray");
  mpy_addObjectToModule(m, &mpy_CircleType, &mpy_ColorfulObjectType, "Circle");
  mpy_addObjectToModule(m, &mpy_NGonType, &mpy_CircleType, "NGon");
  mpy_addObjectToModule(m, &mpy_RectangleType, &mpy_ColorfulObjectType, "Rectangle");

  // Add Constants
  PyModule_AddIntConstant(m, "FILL", FILL);
  PyModule_AddIntConstant(m, "WIRE", WIRE);
  PyModule_AddIntConstant(m, "WIRE_LOOP", WIRE_LOOP);
 
  return m;
}

