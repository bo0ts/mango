/*
 Copyright (c) 2011 Amos Joshua
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/
#include <mango/pygeometry/pygeometry.h>

PyMODINIT_FUNC PyInit_Geometry(void){
  PyObject* m;
  
  m = PyModule_Create(&geometry_module_def);
  if (m == NULL){
    return NULL;
  }

  if (MangoPy::initialize_module_environment()){
    return NULL;
  }
  
  PyTypeObject *dynamic_mpy_object_type = MangoPy::py_type_object("mangopy.core.object");

  mpy_addObjectToModule(m, &mpy_ColorfulObjectType, dynamic_mpy_object_type, "ColorfulObject");
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

  MangoPy::register_py_type_object("pygeometry.colorful_object", &mpy_ColorfulObjectType);
  MangoPy::register_py_type_object("pygeometry.sphere", &mpy_SphereType);
  MangoPy::register_py_type_object("pygeometry.box", &mpy_BoxType);
  MangoPy::register_py_type_object("pygeometry.cylinder", &mpy_CylinderType);
  MangoPy::register_py_type_object("pygeometry.shell", &mpy_ShellType);
  MangoPy::register_py_type_object("pygeometry.arrow", &mpy_ArrowType);
  MangoPy::register_py_type_object("pygeometry.coordinate_system", &mpy_CoordinateSystemType);
  MangoPy::register_py_type_object("pygeometry.vertex_array", &mpy_VertexArrayType);
  MangoPy::register_py_type_object("pygeometry.circle", &mpy_CircleType);
  MangoPy::register_py_type_object("pygeometry.ngon", &mpy_NGonType);
  MangoPy::register_py_type_object("pygeometry.rectangle", &mpy_RectangleType);

  // Add Constants
  PyModule_AddIntConstant(m, "FILL", FILL);
  PyModule_AddIntConstant(m, "WIRE", WIRE);
  PyModule_AddIntConstant(m, "WIRE_LOOP", WIRE_LOOP);

 
  return m;
}

