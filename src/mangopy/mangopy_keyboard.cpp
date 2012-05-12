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
#include <mango/mangopy/mangopy_keyboard.h>

/*
    dealloc and new
                    */
void mpy_CoreKeyboard_dealloc(mpy_CoreKeyboard* self)
{
  // Don't delete the internal object. In the current mangopy implementation, the only instance of an mpy_CoreKeyboard points to
  // an instance of CoreKeyboard that is a static member of the Engine class, so there is no need to delete it 
  //delete self->internalObject;
  self->internalObject = NULL;
  Py_TYPE(self)->tp_free((PyObject*)self);  
}

PyObject *mpy_CoreKeyboard_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    mpy_CoreKeyboard *self;

    self = (mpy_CoreKeyboard *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->internalObject = new Mango::Core::CoreKeyboard();
        if (self->internalObject == NULL){
            Py_DECREF(self);
            PyErr_SetString(PyExc_RuntimeError, "MangoPy Runtime: Failed to create an object of type Mango::Core::CoreKeyboard");
            return NULL;
        }
    }
    return (PyObject *)self;
}

// NOTE: this returns the skeleton python object, it does not create an internalObject of type Mango::Core::CoreKeyboard!
mpy_CoreKeyboard *mpy_CoreKeyboard_NEW(){
    mpy_CoreKeyboard *newKeyboard;
    newKeyboard = reinterpret_cast<mpy_CoreKeyboard *>(PyObject_NEW(mpy_CoreKeyboard, &mpy_CoreKeyboardType));
    return newKeyboard;
}


/*
    Method Definitions
                        */
PyObject *mpy_CoreKeyboard_objectType(mpy_CoreKeyboard* self)
{
    PyObject *result;
    result = PyUnicode_FromString(static_cast<Mango::Core::CoreKeyboard *>(self->internalObject)->objectType());
    return result;
}


PyObject *mpy_CoreKeyboard_down(mpy_CoreKeyboard *self, PyObject* args){
    // Call Parameters
    int key_code;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "i", &key_code)){
        return NULL;
    }

    // Return Value
    bool is_down;

    // Call Function
    try{
        is_down = self->internalObject->down(key_code);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    if (is_down){
        Py_INCREF(Py_True);
        return Py_True;
    }
    Py_INCREF(Py_False);
    return Py_False;
}

PyObject *mpy_CoreKeyboard_state(mpy_CoreKeyboard *self, PyObject* args){
    // Call Parameters
    int key_code;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "i", &key_code)){
        return NULL;
    }

    // Return Value
    int key_state;

    // Call Function
    try{
        key_state = self->internalObject->state(key_code);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_BuildValue("i", key_state);
}


/*
    Method Table
                        */


PyMethodDef mpy_CoreKeyboard_methods[] = {
    {"objectType", (PyCFunction)mpy_CoreKeyboard_objectType, METH_NOARGS,
     "Return a string representing the object's type"
    },
    {"down", (PyCFunction)mpy_CoreKeyboard_down, METH_VARARGS,
     "Returns true if the key with the given key code is pressed"
    },
    {"state", (PyCFunction)mpy_CoreKeyboard_state, METH_VARARGS,
     "Returns the key state of the key with the given key code"
    },

    {NULL}  /* Sentinel */
};

PyTypeObject mpy_CoreKeyboardType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "Core.CoreKeyboard",             /* tp_name */
    sizeof(mpy_CoreKeyboard),      /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)mpy_CoreKeyboard_dealloc, /* tp_dealloc */
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
    "Core Mango CoreKeyboard",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,              /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_CoreKeyboard_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,//(initproc)mpy_CoreKeyboard_init,      /* tp_init */
    0,                         /* tp_alloc */
    mpy_CoreKeyboard_new,                 /* tp_new */
};
