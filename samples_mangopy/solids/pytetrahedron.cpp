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
#include "pytetrahedron.h"

// Dealloc and new

void mpy_Tetrahedron_dealloc(mpy_Tetrahedron* self)
{
  delete self->internalObject;
  Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject *mpy_Tetrahedron_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  mpy_Tetrahedron *self;

  self = (mpy_Tetrahedron *)type->tp_alloc(type, 0);
  if (self != NULL) {
    self->internalObject = new Mango::Solids::Tetrahedron();
    if (self->internalObject == NULL){
      Py_DECREF(self);
      PyErr_SetString(PyExc_RuntimeError, "MangoPy Runtime: Failed to create an object of type Solids::Tetrahedron");
      return NULL;
    }
    self->parentFrame = NULL;
  }
  return (PyObject *)self;
}


//   Setters

PyObject *mpy_Tetrahedron_setHeight(mpy_Tetrahedron* self, PyObject *args)
{
  // Call Parameters
  double h;

  // Parse arguments
  if (!PyArg_ParseTuple(args, "d", &h)){
    return NULL;
  }

  try{
    self->internalObject->setHeight(h);
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }

  Py_INCREF(Py_None);
  return Py_None;
}

// Getters

PyObject *mpy_Tetrahedron_height(mpy_Tetrahedron* self, PyObject *args)
{
  // Return Value
  double h;

  // Call Function
  try{
    h = (float)self->internalObject->height();
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }

  return Py_BuildValue("d", h);
}



/*
  Method Table
*/

PyMethodDef mpy_Tetrahedron_methods[] = {
  
  // Set
  {"setHeight", (PyCFunction)mpy_Tetrahedron_setHeight, METH_VARARGS,
   "Set the height of a Solids::Tetrahedron"
  },
  // Get
  {"height", (PyCFunction)mpy_Tetrahedron_height, METH_NOARGS,
   "Get the height of a Solids::Tetrahedron"
  },

  {NULL}  /* Sentinel */
};

PyTypeObject mpy_TetrahedronType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "Solids.Tetrahedron",             /* tp_name */
  sizeof(mpy_Tetrahedron),      /* tp_basicsize */
  0,                         /* tp_itemsize */
  (destructor)mpy_Tetrahedron_dealloc, /* tp_dealloc */
  0,                         /* tp_print */
  0,                         /* tp_getattr */
  0,                         /* tp_setattr */
  0,                         /* tp_reserved */
  0,                         /* tp_repr */
  0,                         /* tp_as_number */
  0,                         /* tp_as_sequence */
  0,                         /* tp_as_mapping */
  0,                         /* tp_hash  */
  0,                         /* tp_call */
  0,                         /* tp_str */
  0,                         /* tp_getattro */
  0,                         /* tp_setattro */
  0,                         /* tp_as_buffer */
  Py_TPFLAGS_DEFAULT |
  Py_TPFLAGS_BASETYPE,   /* tp_flags */
  "Solids.Tetrahedron",           /* tp_doc */
  0,		               /* tp_traverse */
  0,		               /* tp_clear */
  0,              /* tp_richcompare */
  0,		               /* tp_weaklistoffset */
  0,		               /* tp_iter */
  0,		               /* tp_iternext */
  mpy_Tetrahedron_methods,             /* tp_methods */
  0,             /* tp_members */
  0,                         /* tp_getset */
  0,                         /* tp_base */
  0,                         /* tp_dict */
  0,                         /* tp_descr_get */
  0,                         /* tp_descr_set */
  0,                         /* tp_dictoffset */
  0,//(initproc)mpy_Tetrahedron_init,      /* tp_init */
  0,                         /* tp_alloc */
  mpy_Tetrahedron_new,                 /* tp_new */
};
// ---------------------------
