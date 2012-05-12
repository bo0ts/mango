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
#include <mango/mangopy/mangopy_pyengine_wrapper.h>


/*
    dealloc and new
                      */

void mpy_PyEngine_dealloc(mpy_PyEngine* self)
{
  // Don't delete the internal object. In the current mangopy implementation, the only instance of an mpy_PyEngine points to
  // an instance of PyEngine that is allocated and deleted in mangopy_on_glut main(), so there is no need to delete it
  //delete self->internalObject;
  Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject *mpy_PyEngine_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    mpy_PyEngine *self;

    self = (mpy_PyEngine *)type->tp_alloc(type, 0);
    if (self != NULL) {
      self->internalObject = new MangoPy::PyEngine();
      if (self->internalObject == NULL){
	Py_DECREF(self);
	PyErr_SetString(PyExc_RuntimeError, "MangoPy Runtime: Failed to create an object of type PyEngine");
	return NULL;
      }
    }
    return (PyObject *)self;
}

// NOTE: this returns the skeleton python object, it does not create an internalObject of type Mango::Core::CoreKeyboard!
mpy_PyEngine *mpy_PyEngine_NEW(){
    mpy_PyEngine *newPyEngine;
    newPyEngine = reinterpret_cast<mpy_PyEngine *>(PyObject_NEW(mpy_PyEngine, &mpy_PyEngineType));
    return newPyEngine;
}

/*
    Method Definitions
                        */
/* Set Functions */
PyObject *mpy_PyEngine_setWindowDimensions(mpy_PyEngine* self, PyObject *args)
{
    // Call Parameters
    int width;
    int height;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "ii", &width, &height)){
        return NULL;
    }

    try{
        self->internalObject->setWindowDimensions(width, height);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *mpy_PyEngine_setWindowFullscreen(mpy_PyEngine *self, PyObject* args){
    // Call Parameters
    bool full_screen;
    PyObject *py_full_screen;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "O", &py_full_screen) || !PyBool_Check(py_full_screen)){
        PyErr_SetString(PyExc_TypeError, "Expected True or False");
        return NULL;
    }

    // Call Function
    try{
        full_screen = (PyObject_IsTrue(py_full_screen) == 1);
        self->internalObject->setWindowFullscreen(full_screen);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    // Return result
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *mpy_PyEngine_setWindowFps(mpy_PyEngine* self, PyObject *args)
{
    // Call Parameters
    int fps;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "i", &fps)){
        return NULL;
    }

    try{
        self->internalObject->setWindowFps(fps);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *mpy_PyEngine_setClearBuffer(mpy_PyEngine *self, PyObject* args){
    // Call Parameters
    bool clear_buffer;
    PyObject *py_clear_buffer;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "O", &py_clear_buffer) || !PyBool_Check(py_clear_buffer)){
        PyErr_SetString(PyExc_TypeError, "Expected True or False");
        return NULL;
    }

    // Call Function
    try{
        clear_buffer = (PyObject_IsTrue(py_clear_buffer) == 1);
        self->internalObject->setClearBuffer(clear_buffer);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    // Return result
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *mpy_PyEngine_setClearColor(mpy_PyEngine* self, PyObject *args)
{
    // Call Parameters
    GLfloat r;
    GLfloat g;
    GLfloat b;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "ddd", &r, &g, &b)){
        return NULL;
    }

    try{
      self->internalObject->setClearColor(r, g, b);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}



/* Get Functions */
PyObject *mpy_PyEngine_windowDimensions(mpy_PyEngine* self, PyObject *args)
{
    // Return Value
    int width;
    int height;

    // Call Function
    try{
        self->internalObject->windowDimensions(width, height);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("ii", width, height);
}

PyObject *mpy_PyEngine_windowFullscreen(mpy_PyEngine *self){
    // Function Return Values
    bool full_screen;

    // Call Function
    try{
        full_screen = self->internalObject->windowFullscreen();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    // Return result
    if (full_screen){
        Py_INCREF(Py_True);
        return Py_True;
    }
    else{
        Py_INCREF(Py_False);
        return Py_False;
    }
}

PyObject *mpy_PyEngine_windowFps(mpy_PyEngine* self, PyObject *args)
{
    // Return Value
    int fps;

    // Call Function
    try{
        fps = self->internalObject->windowFps();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("i", fps);
}

PyObject *mpy_PyEngine_clearBuffer(mpy_PyEngine *self){
    // Function Return Values
    bool clear_buffer;

    // Call Function
    try{
        clear_buffer = self->internalObject->clearBuffer();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    // Return result
    if (clear_buffer){
        Py_INCREF(Py_True);
        return Py_True;
    }
    else{
        Py_INCREF(Py_False);
        return Py_False;
    }
}

PyObject *mpy_PyEngine_clearColor(mpy_PyEngine* self, PyObject *args)
{
    // Return Value
    GLfloat r;
    GLfloat g;
    GLfloat b;

    // Call Function
    try{
        self->internalObject->clearColor(r, g, b);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("ddd", r, g, b);
}

PyObject *mpy_PyEngine_actualFps(mpy_PyEngine* self, PyObject *args)
{
    // Return Value
    double actual_fps;

    // Call Function
    try{
        actual_fps = self->internalObject->actualFps();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("d", actual_fps);
}

/*
    Method Table
                        */
PyMethodDef mpy_PyEngine_methods[] = {
    // Set
    {"setWindowDimensions", (PyCFunction)mpy_PyEngine_setWindowDimensions, METH_VARARGS,
     ""
    },
    {"setWindowFullscreen", (PyCFunction)mpy_PyEngine_setWindowFullscreen, METH_VARARGS,
     ""
    },
    {"setWindowFps", (PyCFunction)mpy_PyEngine_setWindowFps, METH_VARARGS,
     ""
    },
    {"setClearBuffer", (PyCFunction)mpy_PyEngine_setClearBuffer, METH_VARARGS,
     ""
    },
    {"setClearColor", (PyCFunction)mpy_PyEngine_setClearColor, METH_VARARGS,
     ""
    },

    // Get
    {"windowDimensions", (PyCFunction)mpy_PyEngine_windowDimensions, METH_NOARGS,
     ""
    },
    {"windowFullscreen", (PyCFunction)mpy_PyEngine_windowFullscreen, METH_NOARGS,
     ""
    },
    {"windowFps", (PyCFunction)mpy_PyEngine_windowFps, METH_NOARGS,
     ""
    },
    {"clearBuffer", (PyCFunction)mpy_PyEngine_clearBuffer, METH_NOARGS,
     ""
    },
    {"clearColor", (PyCFunction)mpy_PyEngine_clearColor, METH_NOARGS,
     ""
    },
    {"actualFps", (PyCFunction)mpy_PyEngine_actualFps, METH_NOARGS,
     ""
    },

    {NULL}  /* Sentinel */
};

PyTypeObject mpy_PyEngineType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyEngine",             /* tp_name */
    sizeof(mpy_PyEngine),      /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)mpy_PyEngine_dealloc, /* tp_dealloc */
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
    "Core.PyEngine",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,              /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_PyEngine_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,//(initproc)mpy_PyEngine_init,      /* tp_init */
    0,                         /* tp_alloc */
    mpy_PyEngine_new,                 /* tp_new */
};

