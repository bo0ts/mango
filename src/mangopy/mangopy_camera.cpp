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
#include <mango/mangopy/mangopy_camera.h>

/*
    dealloc and new
                    */
void mpy_CoreCamera_dealloc(mpy_CoreCamera* self)
{
  // Don't delete the internal object. In the current mangopy implementation, the only instance of an mpy_CoreCamera points to
  // an instance of CoreCamera that is allocated and deleted in mangopy_on_glut main(), so there is no need to delete it
  //delete self->internalObject;
  Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject *mpy_CoreCamera_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  mpy_CoreCamera *self;
  
  self = (mpy_CoreCamera *)type->tp_alloc(type, 0);
  if (self != NULL) {
    self->internalObject = new Mango::Core::CoreCamera();
    if (self->internalObject == NULL){
      Py_DECREF(self);
      PyErr_SetString(PyExc_RuntimeError, "MangoPy Runtime: Failed to create an object of type Mango::Core::CoreCamera");
      return NULL;
    }
    self->parentFrame = NULL;
  }
  return (PyObject *)self;
}


// NOTE: this returns the skeleton python object, it does not create an internalObject of type Mango::Core::CoreCamera!
mpy_CoreCamera *mpy_CoreCamera_NEW(){
  mpy_CoreCamera *newCoreCamera;
  newCoreCamera = reinterpret_cast<mpy_CoreCamera *>(PyObject_NEW(mpy_CoreCamera, &mpy_CoreCameraType));
  newCoreCamera->parentFrame = NULL;
  newCoreCamera->internalObject = NULL;
  return newCoreCamera;
}

/*
    Method Definitions
                        */


PyObject *mpy_CoreCamera_setMode(mpy_CoreCamera *self, PyObject* args){
    // Call Parameters
    int mode;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "i", &mode)){
        return NULL;
    }

    // Return Value

    // Call Function
    try{
        self->internalObject->setMode(mode);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *mpy_CoreCamera_setScaleFactors(mpy_CoreCamera *self, PyObject* args){
    // Call Parameters
    double sx, sy, sz;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "ddd", &sx, &sy, &sz)){
        return NULL;
    }

    // Return Value

    // Call Function
    try{
        self->internalObject->setScaleFactors(sx, sy, sz);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *mpy_CoreCamera_setRotationButton(mpy_CoreCamera *self, PyObject* args){
    // Call Parameters
  int code;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "i", &code)){
        return NULL;
    }

    // Return Value

    // Call Function
    try{
        self->internalObject->setRotationButton(code);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *mpy_CoreCamera_setZoomButton(mpy_CoreCamera *self, PyObject* args){
    // Call Parameters
  int code;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "i", &code)){
        return NULL;
    }

    // Return Value

    // Call Function
    try{
        self->internalObject->setZoomButton(code);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}


PyObject *mpy_CoreCamera_follow(mpy_CoreCamera *self, PyObject* args){
  // Call Parameters
  mpy_Frame *frame_to_follow;
  
  // Parse arguments
  if (!PyArg_ParseTuple(args, "O!", &mpy_FrameType, &frame_to_follow)){
    return NULL;
  }  
  
  // Return Value
  
  // Call Function
  try{
    self->internalObject->follow(frame_to_follow->internalObject);
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_CoreCamera_focus(mpy_CoreCamera *self, PyObject* args){
  return mpy_Frame_parentFrame((mpy_Frame *)self, NULL);
}

PyObject *mpy_CoreCamera_toggleMode(mpy_CoreCamera *self, PyObject* args){
  // Call Parameters
  int mode_mask;
  
  // Parse arguments
  if (!PyArg_ParseTuple(args, "i", &mode_mask)){
    return NULL;
  }
  
  // Return Value

  // Call Function
  try{
    self->internalObject->toggleMode(mode_mask);
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_CoreCamera_modeEnabled(mpy_CoreCamera *self, PyObject* args){
  // Call Parameters
  int mode_mask;
  
  // Parse arguments
  if (!PyArg_ParseTuple(args, "i", &mode_mask)){
    return NULL;
  }
  
  // Return Value
  bool mode_enabled;
  
  // Call Function
  try{
    mode_enabled = self->internalObject->modeEnabled(mode_mask);
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
  
  if (mode_enabled){
    Py_INCREF(Py_True);
    return Py_True;
  }
  Py_INCREF(Py_False);
  return Py_False;
}

PyObject *mpy_CoreCamera_scaleFactors(mpy_CoreCamera *self, PyObject* args){
    // Call Parameters
    GLfloat sx, sy, sz;
    
    // Parse arguments

    // Return Value

    // Call Function
    try{
        self->internalObject->scaleFactors(sx, sy, sz);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("ddd", sx, sy, sz);
}

PyObject *mpy_CoreCamera_rotationButton(mpy_CoreCamera *self, PyObject* args){
  // Call Parameters    
  // Parse arguments
  // Return Value
  int code;
    
  // Call Function
  try{
    code = self->internalObject->rotationButton();
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
  
  return Py_BuildValue("i", code);
}

PyObject *mpy_CoreCamera_zoomButton(mpy_CoreCamera *self, PyObject* args){
  // Call Parameters    
  // Parse arguments
  // Return Value
  int code;
    
  // Call Function
  try{
    code = self->internalObject->zoomButton();
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
  
  return Py_BuildValue("i", code);
}

PyObject *mpy_CoreCamera_scale(mpy_CoreCamera *self, PyObject* args){
    // Call Parameters
    double rx, ry, rz;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "ddd", &rx, &ry, &rz)){
        return NULL;
    }

    // Return Value

    // Call Function
    try{
        self->internalObject->scale(rx, ry, rz);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}


// LookAt Functions

PyObject *mpy_CoreCamera_lookAt(mpy_CoreCamera *self, PyObject* args){
    // Call Parameters
    Mango::Core::Vector point;
    double distance;    
    
    // Parse arguments
    distance = -1;
    if (!PyArg_ParseTuple(args, "O&|d", mpy_VectorConverter, static_cast<void *>(&point), &distance)){
        return NULL;
    }
    
    // Return Value

    // Call Function
    try{
        self->internalObject->lookAt(point, distance);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *mpy_CoreCamera_lookFrom(mpy_CoreCamera *self, PyObject* args){
  // Call Parameters
  PyObject *py_at_point;
  Mango::Core::Vector from_point, at_point;
  
  // Parse arguments  
  py_at_point = NULL;
  if (!PyArg_ParseTuple(args, "O&|O", mpy_VectorConverter, static_cast<void *>(&from_point), &py_at_point)){
    return NULL;
  }

  if ((py_at_point != NULL) && !mpy_VectorFromArgs(py_at_point, at_point)){
    PyErr_SetString(PyExc_TypeError, "Second argument must be a vector or a tuple containing two or three doubles");
    return NULL;
  }
  
  // Return Value
  
  // Call Function
  try{
    if (py_at_point == NULL){
      self->internalObject->lookFrom(from_point);
    }
    else{
      self->internalObject->lookFrom(from_point, at_point);
    }
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}


/*
    Method Table
                        */


PyMethodDef mpy_CoreCamera_methods[] = {
    {"setMode", (PyCFunction)mpy_CoreCamera_setMode, METH_VARARGS,
     "Set the camera mode"
    },
    {"setScaleFactors", (PyCFunction)mpy_CoreCamera_setScaleFactors, METH_VARARGS,
     "Set the camera scale factors"
    },
    {"setRotationButton", (PyCFunction)mpy_CoreCamera_setRotationButton, METH_VARARGS,
     "Set the button code used to rotate the view"
    },
    {"setZoomButton", (PyCFunction)mpy_CoreCamera_setZoomButton, METH_VARARGS,
     "Set the button code used to zoom the view"
    },
    {"follow", (PyCFunction)mpy_CoreCamera_follow, METH_VARARGS,
     "Set an object to follow"
    },
    {"focus", (PyCFunction)mpy_CoreCamera_focus, METH_NOARGS,
     "Get the camera's focus"
    },
    {"toggleMode", (PyCFunction)mpy_CoreCamera_toggleMode, METH_VARARGS,
     "Toggle the camera mode"
    },
    {"modeEnabled", (PyCFunction)mpy_CoreCamera_modeEnabled, METH_VARARGS,
     "Check if a mode is enabled"
    },
    {"scaleFactors", (PyCFunction)mpy_CoreCamera_scaleFactors, METH_VARARGS,
     "Returns the camera scale factors"
    },
    {"rotationButton", (PyCFunction)mpy_CoreCamera_rotationButton, METH_NOARGS,
     "button used to rotate the view"
    },
    {"zoomButton", (PyCFunction)mpy_CoreCamera_zoomButton, METH_NOARGS,
     "button used to zoom the view"
    },    
    {"scale", (PyCFunction)mpy_CoreCamera_scale, METH_VARARGS,
     "Scale the camera scale factors"
    },
    // Look At
    {"lookAt", (PyCFunction)mpy_CoreCamera_lookAt, METH_VARARGS,
     "Look at a point from a given distance and orientation"
    },
    {"lookFrom", (PyCFunction)mpy_CoreCamera_lookFrom, METH_VARARGS,
     "Look at a point from another point given relative to the first one"
    },

    {NULL}  /* Sentinel */
};



PyTypeObject mpy_CoreCameraType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "Core.CoreCamera",             /* tp_name */
    sizeof(mpy_CoreCamera),      /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)mpy_CoreCamera_dealloc, /* tp_dealloc */
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
    "Core Mango camera",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,              /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_CoreCamera_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,//(initproc)mpy_Triangle_init,      /* tp_init */
    0,                         /* tp_alloc */
    mpy_CoreCamera_new,                 /* tp_new */
};


//static
#if 0
PyTypeObject mpy_CoreCameraType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "Core.CoreCamera",       /*tp_name*/
    sizeof(mpy_CoreCamera),  /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)mpy_CoreCamera_dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "Core Camera object",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_CoreCamera_methods,  /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,                         /* tp_init */
    0,                         /* tp_alloc */
    mpy_CoreCamera_new,      /* tp_new */
};
#endif
