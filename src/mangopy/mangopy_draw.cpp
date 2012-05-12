/*
 Copyright (c) 2011, 2012 Amos Joshua
 
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
#include <mango/mangopy/mangopy_draw.h>
#include <mango/mangopy/mangopy_core.h>

// Begin/End

PyObject *mpy_Draw_line(PyObject *, PyObject* args){
  // Call Parameters
  PyObject *py_v1, *py_v2;
  Mango::Core::Vector v1, v2;
  
  // Parse arguments
  if (!PyArg_ParseTuple(args, "OO", &py_v1, &py_v2)){
    return NULL;
  }

  if (!mpy_VectorFromArgs(py_v1, v1) || !mpy_VectorFromArgs(py_v2, v2)){
    PyErr_SetString(PyExc_TypeError, "Expected two Vectors, or two tuples containing two or three doubles each");
    return NULL;
  }
  
  // Call function
  Mango::Draw::line(v1, v2);
  
  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}


PyObject *mpy_Draw_rectangle(PyObject *, PyObject* args){
  // Call Parameters
  PyObject *py_v1, *py_v2;
  Mango::Core::Vector v1, v2;
  PyObject *py_filled = Py_False;
  bool filled; 

  // Parse arguments
  if (!PyArg_ParseTuple(args, "OO|O", &py_v1, &py_v2, &py_filled)){
    return NULL;
  }

  if (!mpy_VectorFromArgs(py_v1, v1) || !mpy_VectorFromArgs(py_v2, v2) || !PyBool_Check(py_filled)){
    PyErr_SetString(PyExc_TypeError, "Expected two Vectors (or two tuples containing two or three doubles each) and an optional boolean");
    return NULL;
  }
  
  filled  = (PyObject_IsTrue(py_filled) == 1);

  // Call function
  Mango::Draw::rectangle(v1, v2, filled);
  
  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_Draw_circle(PyObject *, PyObject* args){
  // Call Parameters
  PyObject *py_v1;
  Mango::Core::Vector v1;
  PyObject *py_filled = Py_False;
  bool filled; 
  double r;
  int sides = 48;

  // Parse arguments
  if (!PyArg_ParseTuple(args, "Od|Oi", &py_v1, &r, &py_filled, &sides)){
    return NULL;
  }

  if (!mpy_VectorFromArgs(py_v1, v1) || !PyBool_Check(py_filled)){
    PyErr_SetString(PyExc_TypeError, "Expected two Vectors (or two tuples containing two or three doubles each), a double and an optional boolean");
    return NULL;
  }
  
  filled  = (PyObject_IsTrue(py_filled) == 1);

  // Call function
  Mango::Draw::circle(v1, r, filled, sides);
  
  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_Draw_text(PyObject *, PyObject* args){
  // Call Parameters
  PyObject *py_v1;
  Mango::Core::Vector v1;
  char *str;
  double scale, character_spacing;

  // Parse arguments
  scale = 1.0;
  character_spacing = 0.1;
  if (!PyArg_ParseTuple(args, "Os|dd", &py_v1, &str, &scale, &character_spacing)){
    return NULL;
  }

  if (!mpy_VectorFromArgs(py_v1, v1)){
    PyErr_SetString(PyExc_TypeError, "Expected first argument to be a Vector (or a tuple containing two or three doubles)");
    return NULL;
  }

  // Call function
  Mango::Draw::text(v1[0], v1[1], str, scale, character_spacing);
  
  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_Draw_textDimensions(PyObject *, PyObject* args){
  // Call Parameters
  char *str;
  double scale, character_spacing;
  GLfloat width, min_height, max_height;

  // Parse arguments
  scale = 1.0;
  character_spacing = 0.1;
  if (!PyArg_ParseTuple(args, "s|dd", &str, &scale, &character_spacing)){
    return NULL;
  }

  // Call function
  Mango::Draw::textDimensions(str, &width, &min_height, &max_height, scale, character_spacing);
  
  // Return result
  return Py_BuildValue("ddd", width, min_height, max_height);
}


static PyMethodDef MangoPyDrawMethods[] = {
  // Begin/end
  {"line",  mpy_Draw_line, METH_VARARGS,
   ""},
  {"rectangle",  mpy_Draw_rectangle, METH_VARARGS,
   ""},
  {"circle",  mpy_Draw_circle, METH_VARARGS,
   ""},
  {"text",  mpy_Draw_text, METH_VARARGS,
   ""},
  {"textDimensions",  mpy_Draw_textDimensions, METH_VARARGS,
   ""},

  {NULL, NULL, 0, NULL}        /* Sentinel */
};



static PyModuleDef draw_module_def = {
    PyModuleDef_HEAD_INIT,
    "Draw",
    "Mango draw",
    -1,
    MangoPyDrawMethods, NULL, NULL, NULL, NULL
};


PyMODINIT_FUNC
PyInit_Draw(void){
  PyObject* m;
  
  m = PyModule_Create(&draw_module_def);
  if (m == NULL){
    return NULL;
  }
 
  return m;
}

