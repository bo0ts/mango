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

#include <mango/core/core.h>
#include <mango/core/vector.h>
#include <mango/mangopy/mangopy_core.h>
#include <mango/mangopy/mangopy_frame.h>
#include <mango/mangopy/mangopy_vector.h>
#include <mango/mangopy/mangopy_matrix.h>

/*
  dealloc and new
*/

mpy_Frame* PyGlobalFrame;

void mpy_Frame_dealloc(mpy_Frame* self)
{
  Py_XDECREF(self->parentFrame);
  if (self->internalObject != Mango::GlobalFrame){
    delete self->internalObject;
  }
  Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject *mpy_Frame_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  mpy_Frame *self;

  self = (mpy_Frame *)type->tp_alloc(type, 0);
  if (self != NULL) {
    self->internalObject = new Mango::Core::Frame();
    if (self->internalObject == NULL){
      Py_DECREF(self);
      PyErr_SetString(PyExc_RuntimeError, "MangoPy Runtime: Failed to create an object of type Mango::Core::Frame");
      return NULL;
    }
    self->parentFrame = NULL;
  }
  return (PyObject *)self;
}

mpy_Frame *mpy_Frame_NEW(){
  mpy_Frame *object;
  object = PyObject_NEW(mpy_Frame, &mpy_FrameType);
  object->parentFrame = NULL;
  object->internalObject = NULL;
  return object;
}

int mpy_Frame_init(mpy_Frame *self, PyObject *args, PyObject *kw)
{
  if (self->parentFrame == NULL){
    Py_INCREF(PyGlobalFrame);
    self->parentFrame = PyGlobalFrame;
  }
  return 0;
}

bool mpy_Frame_initialized(mpy_Frame *self){
  if ((self->parentFrame) == NULL && (self != PyGlobalFrame)){
    PyErr_SetString(PyExc_RuntimeError, "Object frame not initialized, you may have overridden __init__ in a derived class and forgotten to call __init__ on the parent");
    return false;
  }
  return true;
}

/*
  Method Definitions
*/
/* Set Functions */
PyObject *mpy_Frame_setOrientationAxes(mpy_Frame *self, PyObject* args){
  VERIFY_FRAME_INITIALIZED(self);

  // Call Parameters
  Mango::Vector u1, u2, u3;
  PyObject *py_u1, *py_u2, *py_u3;
  // Parse arguments
  if (!PyArg_ParseTuple(args, "OOO", &py_u1, &py_u2, &py_u3)){
    return NULL;
  }
  if (!mpy_VectorFromArgs(py_u1, u1) || !mpy_VectorFromArgs(py_u2, u2) || !mpy_VectorFromArgs(py_u3, u3)){
    return NULL;
  }
  
  // Call Function
  try{
    self->internalObject->setOrientationAxes(u1, u2, u3);
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }
  
  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_Frame_setOrientation(mpy_Frame* self, PyObject *args)
{
  VERIFY_FRAME_INITIALIZED(self);

  // Call Parameters
  double alpha;
  double beta;
  double gamma;

  // Parse arguments
  if (!PyArg_ParseTuple(args, "ddd", &alpha, &beta, &gamma)){
    return NULL;
  }

  try{
    self->internalObject->setOrientation(alpha, beta, gamma);
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }

  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_Frame_setParentFrame(mpy_Frame* self, PyObject *args)
{
  if (self == PyGlobalFrame){
    PyErr_SetString(PyExc_RuntimeError, "Cannot set a parent for the global frame");
    return NULL;
  }

  VERIFY_FRAME_INITIALIZED(self);

  // Call Parameters
  mpy_Frame *newParent;

  // Parse arguments
  if (!PyArg_ParseTuple(args, "O", &newParent) || !PyObject_TypeCheck((PyObject *)newParent, &mpy_FrameType)){
    PyErr_SetString(PyExc_TypeError, "Expected an instance of class Core.Frame");
    return NULL;
  }
  
  try{
    self->internalObject->setParentFrame(newParent->internalObject);
    Py_DECREF(self->parentFrame);
    Py_INCREF(newParent);
    self->parentFrame = newParent;
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}


PyObject *mpy_Frame_rotate(mpy_Frame* self, PyObject *args)
{
  VERIFY_FRAME_INITIALIZED(self);

  // Call Parameters
  double alpha;
  double beta;
  double gamma;

  // Parse arguments
  beta = 0;
  gamma = 0;
  if (!PyArg_ParseTuple(args, "d|dd", &alpha, &beta, &gamma)){
    return NULL;
  }

  try{
    self->internalObject->rotate(alpha, beta, gamma);
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }

  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_Frame_translate(mpy_Frame *self, PyObject* args){
  VERIFY_FRAME_INITIALIZED(self);

  // Call Parameters
  Mango::Vector dpos;

  // Parse arguments
  if (!mpy_VectorFromArgs(args, dpos)){
    return NULL;
  }

  // Call Function
  try{
    self->internalObject->translate(dpos);
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_Frame_rotationFromParent(mpy_Frame *self, PyObject* args){
  VERIFY_FRAME_INITIALIZED(self);

  // Call Parameters
  mpy_Matrix *R = mpy_Matrix_NEW();

  // Call Function
  try{
    R->M = self->internalObject->rotationFromParent();
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  return Py_BuildValue("O", (PyObject *)R);
}

PyObject *mpy_Frame_rotationToParent(mpy_Frame *self, PyObject* args){
  VERIFY_FRAME_INITIALIZED(self);

  // Call Parameters
  mpy_Matrix *R = mpy_Matrix_NEW();

  // Parse arguments
  if (!PyArg_ParseTuple(args, "O!", &mpy_MatrixType, &R)){
    return NULL;
  }

  // Call Function
  try{
    R->M = self->internalObject->rotationToParent();
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  return Py_BuildValue("O", (PyObject *)R);
}

PyObject *mpy_Frame_transformToParent(mpy_Frame *self, PyObject* args){
  VERIFY_FRAME_INITIALIZED(self);

  // Call Parameters
  Mango::Core::Vector v, w;

  // Parse arguments
  if (!mpy_VectorFromArgs(args, v)){
    return NULL;
  }

  // Call Function
  try{
    w = self->internalObject->transformToParent(v);
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  mpy_Vector *transformed_v = mpy_Vector_NEW();
  transformed_v->v = w;
  Py_XINCREF(transformed_v);    
  return Py_BuildValue("O", (PyObject *)transformed_v);
}

PyObject *mpy_Frame_transformToAncestor(mpy_Frame *self, PyObject* args){
  VERIFY_FRAME_INITIALIZED(self);

  // Call Parameters
  Mango::Vector v, w;
  mpy_Frame *py_ancestor;

  // Parse arguments
  if (!PyArg_ParseTuple(args, "O&O!", mpy_VectorConverter, static_cast<void *>(&v), &mpy_FrameType, &py_ancestor)){
    return NULL;
  }

  // Call Function
  try{
    w = self->internalObject->transformToAncestor(v, py_ancestor->internalObject);
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  mpy_Vector *transformed_v = mpy_Vector_NEW();
  transformed_v->v = w;
  Py_XINCREF(transformed_v);    
  return Py_BuildValue("O", (PyObject *)transformed_v);
}

PyObject *mpy_Frame_transformFromParent(mpy_Frame *self, PyObject* args){
  VERIFY_FRAME_INITIALIZED(self);

  // Call Parameters
  Mango::Vector v, w;

  // Parse arguments
  if (!mpy_VectorFromArgs(args, v)){
    return NULL;
  }

  // Call Function
  try{
    w = self->internalObject->transformFromParent(v);
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  mpy_Vector *transformed_v = mpy_Vector_NEW();
  transformed_v->v = w;
  Py_XINCREF(transformed_v);    
  return Py_BuildValue("O", (PyObject *)transformed_v);
}

PyObject *mpy_Frame_transformFromAncestor(mpy_Frame *self, PyObject* args){
  VERIFY_FRAME_INITIALIZED(self);

  // Call Parameters
  Mango::Vector v, w;
  mpy_Frame *py_ancestor;

  // Parse arguments
  if (!PyArg_ParseTuple(args, "O&O!", mpy_VectorConverter, static_cast<void *>(&v), &mpy_FrameType, &py_ancestor)){
    return NULL;
  }

  // Call Function
  try{
    w = self->internalObject->transformFromAncestor(v, py_ancestor->internalObject);
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  mpy_Vector *transformed_v = mpy_Vector_NEW();
  transformed_v->v = w;
  Py_XINCREF(transformed_v);    
  return Py_BuildValue("O", (PyObject *)transformed_v);
}

PyObject *mpy_Frame_orientationFor(mpy_Frame *self, PyObject* args){
  VERIFY_FRAME_INITIALIZED(self);

  // Call Parameters
  Mango::Vector v;
  GLfloat alpha, beta;

  // Parse arguments
  if (!mpy_VectorFromArgs(args, v)){
    return NULL;
  }

  // Call Function
  try{
    self->internalObject->orientationFor(v, alpha, beta);
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  return Py_BuildValue("dd", (double)alpha, (double)beta);
}

PyObject *mpy_Frame_pointTo(mpy_Frame *self, PyObject* args){
  VERIFY_FRAME_INITIALIZED(self);

  // Call Parameters
  Mango::Vector v;

  // Parse arguments
  if (!mpy_VectorFromArgs(args, v)){
    return NULL;
  }

  // Call Function
  try{
    self->internalObject->pointTo(v);
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_Frame_transform(mpy_Frame *self, PyObject* args){
  VERIFY_FRAME_INITIALIZED(self);

  bool transform_parent;
  PyObject *py_transform_parent;

  // Parse arguments
  py_transform_parent = Py_True;
  if (!PyArg_ParseTuple(args, "|O", &py_transform_parent) || !PyBool_Check(py_transform_parent)){
    PyErr_SetString(PyExc_TypeError, "Expected True or False");
    return NULL;
  }

  // Call Function
  try{
    transform_parent = (PyObject_IsTrue(py_transform_parent) == 1);
    self->internalObject->transform(transform_parent);
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }

  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_Frame_reverseTransform(mpy_Frame *self, PyObject* args){
  VERIFY_FRAME_INITIALIZED(self);

  bool transform_parent;
  PyObject *py_transform_parent;

  // Parse arguments
  py_transform_parent = Py_True;
  if (!PyArg_ParseTuple(args, "|O", &py_transform_parent) || !PyBool_Check(py_transform_parent)){
    PyErr_SetString(PyExc_TypeError, "Expected True or False");
    return NULL;
  }

  // Call Function
  try{
    transform_parent = (PyObject_IsTrue(py_transform_parent) == 1);
    self->internalObject->reverseTransform(transform_parent);
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }

  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}

/* Get Functions */
PyObject *mpy_Frame_orientationAxes(mpy_Frame *self, PyObject* args){
  VERIFY_FRAME_INITIALIZED(self);
  
  // Function Return Values
  mpy_Vector *u1, *u2, *u3;

  // Parse arguments

  // Call Function
  u1 = mpy_Vector_NEW();
  u2 = mpy_Vector_NEW();
  u3 = mpy_Vector_NEW();
  try{
    self->internalObject->orientationAxes(u1->v, u2->v, u3->v);
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  return Py_BuildValue("OOO", u1, u2, u3);
}

PyObject *mpy_Frame_orientation(mpy_Frame* self, PyObject *args)
{
  VERIFY_FRAME_INITIALIZED(self);

  // Return Value
  GLfloat alpha;
  GLfloat beta;
  GLfloat gamma;

  // Call Function
  try{
    self->internalObject->orientation(alpha, beta, gamma);
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }

  return Py_BuildValue("ddd", alpha, beta, gamma);
}


PyObject *mpy_Frame_parentFrame(mpy_Frame* self, PyObject *args)
{ 
  if (self->parentFrame == NULL){
    Py_INCREF(Py_None);
    return Py_None;
  }
  else{
    Py_INCREF(self->parentFrame);
    return Py_BuildValue("O", (PyObject *)(self->parentFrame));
  }
}

PyObject *mpy_Frame_hasFrameAsAncestor(mpy_Frame* self, PyObject *args)
{
  VERIFY_FRAME_INITIALIZED(self);

  // Function Return Values
  bool is_ancestor;

  // Call Parameters
  mpy_Frame *suspectParent;

  // Parse arguments
  if (!PyArg_ParseTuple(args, "O", &suspectParent) || !PyObject_TypeCheck((PyObject *)suspectParent, &mpy_FrameType)){
    PyErr_SetString(PyExc_TypeError, "Expected an instance of class Core.Frame");
    return NULL;
  }
  
  try{
    is_ancestor = self->internalObject->hasFrameAsAncestor(suspectParent->internalObject);
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
  
  // Return result
  if (is_ancestor){
    Py_INCREF(Py_True);
    return Py_True;
  }
  else{
    Py_INCREF(Py_False);
    return Py_False;
  }
}


PyObject *mpy_Frame_get_position(mpy_Frame* self,  void *closure)
{
  VERIFY_FRAME_INITIALIZED(self);

  // C Attribute
  mpy_Vector *py_pos;

  // Retrieve attribute
  py_pos = mpy_Vector_NEW();
  try{
    py_pos->v = self->internalObject->position;
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result  
  return Py_BuildValue("O", py_pos);
}

int mpy_Frame_set_position(mpy_Frame* self, PyObject *value, void *closure)
{
  if (!mpy_Frame_initialized(self))
    return -1;

  // Call Parameters
  Mango::Vector pos;
  
  if (!mpy_VectorFromArgs(value, pos)){
    return -1;
  }
  
  // Call Function
  try{
    self->internalObject->position = pos;
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    pythonExceptionFromCException(e);
    return -1;
  }
  
  // Return result
  return 0;
}


PyObject *mpy_Frame_get_alpha(mpy_Frame* self,  void *closure)
{
  VERIFY_FRAME_INITIALIZED(self);

  // C Attribute
  GLfloat alpha;

  // Retrieve Attribute
  alpha = self->internalObject->alpha;

  // Return result
  return Py_BuildValue("d", (double)alpha);
}

int mpy_Frame_set_alpha(mpy_Frame* self, PyObject *value, void *closure)
{
  if (!mpy_Frame_initialized(self))
    return -1;


  // C Attribute
  double alpha;   

  // Parse Value
  if (PyNumber_Check(value) != 1){
    return -1;
  }
  alpha = PyFloat_AsDouble(value);
  
  // Assign 
  self->internalObject->alpha = alpha;
  
  // Return 
  return 0;
}

PyObject *mpy_Frame_get_beta(mpy_Frame* self,  void *closure)
{
  VERIFY_FRAME_INITIALIZED(self);

  // C Attribute
  GLfloat beta;

  // Retrieve Attribute
  beta = self->internalObject->beta;

  // Return result
  return Py_BuildValue("d", (double)beta);
}

int mpy_Frame_set_beta(mpy_Frame* self, PyObject *value, void *closure)
{
  if (!mpy_Frame_initialized(self))
    return -1;

  // C Attribute
  double beta;   

  // Parse Value
  if (PyNumber_Check(value) != 1){
    return -1;
  }
  beta = PyFloat_AsDouble(value);
  
  // Assign 
  self->internalObject->beta = beta;
  
  // Return 
  return 0;
}

PyObject *mpy_Frame_get_gamma(mpy_Frame* self,  void *closure)
{
  VERIFY_FRAME_INITIALIZED(self);

  // C Attribute
  GLfloat gamma;

  // Retrieve Attribute
  gamma = self->internalObject->gamma;

  // Return result
  return Py_BuildValue("d", (double)gamma);
}

int mpy_Frame_set_gamma(mpy_Frame* self, PyObject *value, void *closure)
{
  if (!mpy_Frame_initialized(self))
    return -1;

  // C Attribute
  double gamma;   

  // Parse Value
  if (PyNumber_Check(value) != 1){
    return -1;
  }
  gamma = PyFloat_AsDouble(value);
  
  // Assign 
  self->internalObject->gamma = gamma;
  
  // Return 
  return 0;
}


/*
  Method Table
*/

static PyGetSetDef mpy_Frame_GetSetMethods[] = {
  {const_cast<char *>("position"), 
   (getter)mpy_Frame_get_position, (setter)mpy_Frame_set_position,
   const_cast<char *>(""),
   NULL},
  {const_cast<char *>("alpha"), 
   (getter)mpy_Frame_get_alpha, (setter)mpy_Frame_set_alpha,
   const_cast<char *>(""),
   NULL},
  {const_cast<char *>("beta"), 
   (getter)mpy_Frame_get_beta, (setter)mpy_Frame_set_beta,
   const_cast<char *>(""),
   NULL},
  {const_cast<char *>("gamma"), 
   (getter)mpy_Frame_get_gamma, (setter)mpy_Frame_set_gamma,
   const_cast<char *>(""),
   NULL},

  {NULL}  /* Sentinel */
};




PyMethodDef mpy_Frame_methods[] = {
  // Set
  {const_cast<char *>("setOrientationAxes"), (PyCFunction)mpy_Frame_setOrientationAxes, METH_VARARGS,
   const_cast<char *>("")
  },
  {const_cast<char *>("setOrientation"), (PyCFunction)mpy_Frame_setOrientation, METH_VARARGS,
   const_cast<char *>("")
  },
  {const_cast<char *>("setParentFrame"), (PyCFunction)mpy_Frame_setParentFrame, METH_VARARGS,
   const_cast<char *>("")
  },
  {const_cast<char *>("rotate"), (PyCFunction)mpy_Frame_rotate, METH_VARARGS,
   const_cast<char *>("")
  },
  {const_cast<char *>("translate"), (PyCFunction)mpy_Frame_translate, METH_VARARGS,
   const_cast<char *>("")
  },

  {const_cast<char *>("rotationToParent"), (PyCFunction)mpy_Frame_rotationToParent, METH_NOARGS,
   const_cast<char *>("")
  },
  {const_cast<char *>("rotationFromParent"), (PyCFunction)mpy_Frame_rotationFromParent, METH_NOARGS,
   const_cast<char *>("")
  },
  {const_cast<char *>("transformToParent"), (PyCFunction)mpy_Frame_transformToParent, METH_VARARGS,
   const_cast<char *>("")
  },
  {const_cast<char *>("transformToAncestor"), (PyCFunction)mpy_Frame_transformToAncestor, METH_VARARGS,
   const_cast<char *>("")
  },
  {const_cast<char *>("transformFromParent"), (PyCFunction)mpy_Frame_transformFromParent, METH_VARARGS,
   const_cast<char *>("")
  },
  {const_cast<char *>("transformFromAncestor"), (PyCFunction)mpy_Frame_transformFromAncestor, METH_VARARGS,
   const_cast<char *>("")
  },

  {const_cast<char *>("transform"), (PyCFunction)mpy_Frame_transform, METH_VARARGS,
   const_cast<char *>("")
  },
  {const_cast<char *>("reverseTransform"), (PyCFunction)mpy_Frame_reverseTransform, METH_VARARGS,
   const_cast<char *>("")
  },
  {const_cast<char *>("orientationFor"), (PyCFunction)mpy_Frame_orientationFor, METH_VARARGS,
   const_cast<char *>("")
  },
  {const_cast<char *>("pointTo"), (PyCFunction)mpy_Frame_pointTo, METH_VARARGS,
   const_cast<char *>("")
  },
  
  // Get
  {const_cast<char *>("orientation"), (PyCFunction)mpy_Frame_orientation, METH_NOARGS,
   const_cast<char *>("")
  },
  {const_cast<char *>("orientationAxes"), (PyCFunction)mpy_Frame_orientationAxes, METH_NOARGS,
   const_cast<char *>("")
  },
  {const_cast<char *>("parentFrame"), (PyCFunction)mpy_Frame_parentFrame, METH_NOARGS,
   const_cast<char *>("")
  },
  {const_cast<char *>("hasFrameAsAncestor"), (PyCFunction)mpy_Frame_hasFrameAsAncestor, METH_VARARGS,
   const_cast<char *>("")
  },
  
  {NULL}  /* Sentinel */
};

PyTypeObject mpy_FrameType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "Frame",             /* tp_name */
  sizeof(mpy_Frame),      /* tp_basicsize */
  0,                         /* tp_itemsize */
  (destructor)mpy_Frame_dealloc, /* tp_dealloc */
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
  "Core.Frame",           /* tp_doc */
  0,		               /* tp_traverse */
  0,		               /* tp_clear */
  0,              /* tp_richcompare */
  0,		               /* tp_weaklistoffset */
  0,		               /* tp_iter */
  0,		               /* tp_iternext */
  mpy_Frame_methods,         /* tp_methods */
  0,             /* tp_members */
  mpy_Frame_GetSetMethods,   /* tp_getset */
  0,                         /* tp_base */
  0,                         /* tp_dict */
  0,                         /* tp_descr_get */
  0,                         /* tp_descr_set */
  0,                         /* tp_dictoffset */
  (initproc)mpy_Frame_init,      /* tp_init */
  0,                         /* tp_alloc */
  mpy_Frame_new,                 /* tp_new */
};

