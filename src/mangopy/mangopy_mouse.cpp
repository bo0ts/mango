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
#include <mango/mangopy/mangopy_mouse.h>

/*
    dealloc and new
                    */
void mpy_CoreMouse_dealloc(mpy_CoreMouse* self)
{
  // Don't delete the internal object. In the current mangopy implementation, the only instance of an mpy_CoreMouse points to
  // an instance of CoreMouse that is a static member of the Engine class, so there is no need to delete it 
  //delete self->internalObject;
  self->internalObject = NULL;
  Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject *mpy_CoreMouse_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    mpy_CoreMouse *self;

    self = (mpy_CoreMouse *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->internalObject = new Mango::Core::CoreMouse();
        if (self->internalObject == NULL){
            Py_DECREF(self);
            PyErr_SetString(PyExc_RuntimeError, "MangoPy Runtime: Failed to create an object of type Mango::Core::CoreMouse");
            return NULL;
        }
    }
    return (PyObject *)self;
}

// NOTE: this returns the skeleton python object, it does not create an internalObject of type Mango::Core::CoreMouse!
mpy_CoreMouse *mpy_CoreMouse_NEW(){
    mpy_CoreMouse *newMouse;
    newMouse = reinterpret_cast<mpy_CoreMouse *>(PyObject_NEW(mpy_CoreMouse, &mpy_CoreMouseType));
    return newMouse;
}


/*
    Method Definitions
                        */
PyObject *mpy_CoreMouse_objectType(mpy_CoreMouse* self)
{
    PyObject *result;
    result = PyUnicode_FromString(static_cast<Mango::Core::CoreMouse *>(self->internalObject)->objectType());
    return result;
}




PyObject *mpy_CoreMouse_clearMovedFlag(mpy_CoreMouse *self, PyObject* args){
    try{
        self->internalObject->clearMovedFlag();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}

// Get Functions
PyObject *mpy_CoreMouse_down(mpy_CoreMouse *self, PyObject* args){
    // Call Parameters
    int button_code;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "i", &button_code)){
        return NULL;
    }

    // Return Value
    int button_down;

    // Call Function
    try{
        button_down = self->internalObject->down(button_code);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("i", button_down);
}

PyObject *mpy_CoreMouse_state(mpy_CoreMouse *self, PyObject* args){
    // Call Parameters
    int button_code;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "i", &button_code)){
        return NULL;
    }

    // Return Value
    int button_state;

    // Call Function
    try{
        button_state = self->internalObject->state(button_code);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("i", button_state);
}

PyObject *mpy_CoreMouse_coordinates(mpy_CoreMouse *self, PyObject* args){
    // Call Parameters
    int x, y;

    // Parse arguments

    // Return Value

    // Call Function
    try{
        self->internalObject->coordinates(x, y);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_BuildValue("ii", x, y);
}



PyObject *mpy_CoreMouse_previousCoordinates(mpy_CoreMouse *self, PyObject* args){
    // Call Parameters
    int x, y;

    // Parse arguments

    // Return Value

    // Call Function
    try{
        self->internalObject->previousCoordinates(x, y);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_BuildValue("ii", x, y);
}

PyObject *mpy_CoreMouse_coordinatesDelta(mpy_CoreMouse *self, PyObject* args){
    // Call Parameters
    int dx, dy;

    // Parse arguments

    // Return Value

    // Call Function
    try{
        self->internalObject->coordinatesDelta(dx, dy);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_BuildValue("ii", dx, dy);
}

PyObject *mpy_CoreMouse_moved(mpy_CoreMouse *self, PyObject* args){
    // Call Parameters

    // Parse arguments

    // Return Value
    bool mouse_moved;
    
    // Call Function
    try{
        mouse_moved = self->internalObject->moved();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    if (mouse_moved){
        Py_INCREF(Py_True);
        return Py_True;
    }
    Py_INCREF(Py_False);
    return Py_False;
}

/*
    Method Table
                        */


PyMethodDef mpy_CoreMouse_methods[] = {
    {"objectType", (PyCFunction)mpy_CoreMouse_objectType, METH_NOARGS,
     "Return a string representing the object's type"
    },
    {"clearMouseMovedFalg", (PyCFunction)mpy_CoreMouse_clearMovedFlag, METH_NOARGS,
     "Clear the mouse-moved flag"
    },
    {"down", (PyCFunction)mpy_CoreMouse_down, METH_VARARGS,
     "Returns true if the button with the given code is currently pressed"
    },
    {"state", (PyCFunction)mpy_CoreMouse_state, METH_VARARGS,
     "Returns the state of the button with the given button code"
    },
    {"coordinates", (PyCFunction)mpy_CoreMouse_coordinates, METH_NOARGS,
     "Returns the current coordiantes of the mouse"
    },    
    {"previousCoordinates", (PyCFunction)mpy_CoreMouse_previousCoordinates, METH_NOARGS,
     "Returns the coordiantes of the mouse from the previous frame"
    },
    {"coordinatesDelta", (PyCFunction)mpy_CoreMouse_coordinatesDelta, METH_NOARGS,
     "Returns the change in coordinates from the previous frame to the current one"
    },    
    {"moved", (PyCFunction)mpy_CoreMouse_moved, METH_NOARGS,
     "Return true if the mouse has moved since the last frame"
    },
    
    {NULL}  /* Sentinel */
};

PyTypeObject mpy_CoreMouseType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "Core.CoreMouse",             /* tp_name */
    sizeof(mpy_CoreMouse),      /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)mpy_CoreMouse_dealloc, /* tp_dealloc */
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
    "Core Mango CoreMouse",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,              /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_CoreMouse_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,//(initproc)mpy_CoreMouse_init,      /* tp_init */
    0,                         /* tp_alloc */
    mpy_CoreMouse_new,                 /* tp_new */
};



#if 0
//static
PyTypeObject mpy_CoreMouseType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "_pye3.Mango::Core::CoreMouse",       /*tp_name*/
    sizeof(mpy_CoreMouse),  /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)mpy_CoreMouse_dealloc, /*tp_dealloc*/
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
    "Mango::Core::CoreMouse object",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_CoreMouse_methods,  /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,                         /* tp_init */
    0,                         /* tp_alloc */
    mpy_CoreMouse_new,      /* tp_new */
};
#endif
