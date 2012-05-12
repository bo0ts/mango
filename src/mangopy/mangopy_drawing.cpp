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
#include <mango/mangopy/mangopy_drawing.h>
#include <mango/mangopy/mangopy_core.h>

// Begin/End

PyObject *mpy_Drawing_glBegin(PyObject *, PyObject* args){
  // Call Parameters
  int style;
  
  // Parse arguments
  if (!PyArg_ParseTuple(args, "i", &style)){
    return NULL;
  }
  
  // Call function
  glBegin(style);
  
  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_Drawing_glEnd(PyObject *, PyObject* args){
  // Call Parameters
  
  // Parse arguments
  
  // Call function
  glEnd();
  
  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}


// Vertex

PyObject *mpy_Drawing_glVertex(PyObject *, PyObject* args){
  // Call Parameters
  Mango::Core::Vector v;
  
  // Parse arguments
  if (!mpy_VectorFromArgs(args, v)){
    return NULL;
  }
  
  // Call function
  glVertex3d(v[0], v[1], v[2]);
  
  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_Drawing_glNormal(PyObject *, PyObject* args){
  // Call Parameters
  double x, y, z;
  
  // Parse arguments
  if (!mpy_ThreeDoublesFromArgs(args, x, y, z)){
    return NULL;
  }
  
  // Call function
  glNormal3d(x, y, z);
  
  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}

// Color
PyObject *mpy_Drawing_glColor(PyObject *, PyObject* args){
  // Call Parameters
  double r, g, b;
  
  // Parse arguments
  if (!mpy_ThreeDoublesFromArgs(args, r, g, b)){
    PyErr_SetString(PyExc_TypeError, "expected three doubles or a tuple containing three doubles");
    return NULL;
  }
  
  // Call function
  glColor3d(r, g, b);
  
  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}

// Transform
PyObject *mpy_Drawing_glTranslate(PyObject *, PyObject* args){
  // Call Parameters
  Mango::Core::Vector v;
  
  // Parse arguments
  if (!mpy_VectorFromArgs(args, v)){    
    return NULL;
  }
  
  // Call function
  glTranslated(v[0], v[1], v[2]);
  
  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_Drawing_glRotate(PyObject *, PyObject* args){
  // Call Parameters
  PyObject *py_axis;
  Mango::Core::Vector axis = Mango::Core::Vector(0, 0, 1);
  double angle;

  int arg_size = PyTuple_Size(args);
  if (arg_size == 1){
    if (!PyArg_ParseTuple(args, "d", &angle)){
      PyErr_SetString(PyExc_TypeError, "expected an angle or an angle and a vector");
      return NULL;
    }
  }
  else if (arg_size == 2){
    if (!PyArg_ParseTuple(args, "dO", &angle, &py_axis) || (!PyObject_TypeCheck(py_axis, &mpy_VectorType) && !PyTuple_Check(py_axis)) || !mpy_VectorFromArgs(py_axis, axis)){
      PyErr_SetString(PyExc_TypeError, "expected an angle or an angle and a vector");
      return NULL;
    }
    //axis = ((mpy_Vector *)py_axis)->v;
  }
  else{
    PyErr_SetString(PyExc_TypeError, "expected an angle or an angle and a vector");
    return NULL;
  }
  
  // Call function
  glRotated(angle, axis[0], axis[1], axis[2]);
  
  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_Drawing_glScale(PyObject *, PyObject* args){
  // Call Parameters
  double x, y, z;
  
  // Parse arguments
  if (!mpy_ThreeDoublesFromArgs(args, x, y, z)){
    return NULL;
  }
  
  // Call function
  glScaled(x, y, z);
  
  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}





static PyMethodDef MangoPyDrawingMethods[] = {
  // Begin/end
  {"glBegin",  mpy_Drawing_glBegin, METH_VARARGS,
   ""},
  {"glEnd",  mpy_Drawing_glEnd, METH_NOARGS,
   ""},

  // Vertex
  {"glVertex",  mpy_Drawing_glVertex, METH_VARARGS,
   ""},
  {"glNormal",  mpy_Drawing_glNormal, METH_VARARGS,
   ""},

  // Color
  {"glColor",  mpy_Drawing_glColor, METH_VARARGS,
   ""},

  // Transform
  {"glTranslate", mpy_Drawing_glTranslate, METH_VARARGS,
   ""},
  {"glRotate", mpy_Drawing_glRotate, METH_VARARGS,
   ""},
  {"glScale", mpy_Drawing_glScale, METH_VARARGS,
   ""},

  {NULL, NULL, 0, NULL}        /* Sentinel */
};



static PyModuleDef drawing_module_def = {
    PyModuleDef_HEAD_INIT,
    "Drawing",
    "Mango drawing",
    -1,
    MangoPyDrawingMethods, NULL, NULL, NULL, NULL
};


PyMODINIT_FUNC
PyInit_Drawing(void){
  PyObject* m;
  
  m = PyModule_Create(&drawing_module_def);
  if (m == NULL){
    return NULL;
  }
  
  PyModule_AddIntConstant(m, "GL_POINTS", GL_POINTS);
  PyModule_AddIntConstant(m, "GL_LINES", GL_LINES); 
  PyModule_AddIntConstant(m, "GL_LINE_LOOP", GL_LINE_LOOP);
  PyModule_AddIntConstant(m, "GL_LINE_STRIP", GL_LINE_STRIP);                           
  PyModule_AddIntConstant(m, "GL_TRIANGLES", GL_TRIANGLES);                            
  PyModule_AddIntConstant(m, "GL_TRIANGLE_STRIP", GL_TRIANGLE_STRIP);                       
  PyModule_AddIntConstant(m, "GL_TRIANGLE_FAN", GL_TRIANGLE_FAN);                         
  PyModule_AddIntConstant(m, "GL_QUADS", GL_QUADS);                                
  PyModule_AddIntConstant(m, "GL_QUAD_STRIP", GL_QUAD_STRIP);
  PyModule_AddIntConstant(m, "GL_POLYGON", GL_POLYGON);

  return m;
}


