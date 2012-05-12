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
#include <mango/pygeometry/pygeometry_box.h>

/*
    dealloc and new
                      */

void mpy_Box_dealloc(mpy_Box* self)
{
    delete self->internalObject;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject *mpy_Box_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    mpy_Box *self;

    self = (mpy_Box *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->internalObject = new Mango::Geometry::Box(1.0, 1.0, 1.0);
        if (self->internalObject == NULL){
            Py_DECREF(self);
            PyErr_SetString(PyExc_RuntimeError, "MangoPy Runtime: Failed to create an object of type Mango::Geometry::Box");
            return NULL;
        }
	self->parentFrame = NULL;
    }
    return (PyObject *)self;
}

/*
    Method Definitions
                        */
/* Set Functions */

PyObject *mpy_Box_setDimensions(mpy_Box* self, PyObject *args)
{
    // Call Parameters
    double h;
    double w;
    double l;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "ddd", &h, &w, &l)){
        return NULL;
    }

    try{
        self->internalObject->setDimensions(h, w, l);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}


/* Get Functions */

PyObject *mpy_Box_dimensions(mpy_Box* self, PyObject *args)
{
    // Return Value
    GLfloat h;
    GLfloat w;
    GLfloat l;

    // Call Function
    try{
        self->internalObject->dimensions(h, w, l);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("ddd", h, w, l);
}


/*
    Method Table
                        */
PyMethodDef mpy_Box_methods[] = {
    // Set
    {"setDimensions", (PyCFunction)mpy_Box_setDimensions, METH_VARARGS,
     "Set the dimensions of a Mango::Geometry::Box"
    }, 

    // Get
    {"dimensions", (PyCFunction)mpy_Box_dimensions, METH_NOARGS,
     "Get the dimensions of a Mango::Geometry::Box"
    }, 

    {NULL}  /* Sentinel */
};

PyTypeObject mpy_BoxType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "Geometry.Box",             /* tp_name */
    sizeof(mpy_Box),      /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)mpy_Box_dealloc, /* tp_dealloc */
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
    "Mango::Geometry::Box",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,              /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_Box_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,//(initproc)mpy_Box_init,      /* tp_init */
    0,                         /* tp_alloc */
    mpy_Box_new,                 /* tp_new */
};

