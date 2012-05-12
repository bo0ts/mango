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
#include <mango/pygeometry/pygeometry_shell.h>


/*
    dealloc and new
                      */

void mpy_Shell_dealloc(mpy_Shell* self)
{
    delete self->internalObject;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject *mpy_Shell_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    mpy_Shell *self;

    self = (mpy_Shell *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->internalObject = new Mango::Geometry::Shell();
        if (self->internalObject == NULL){
            Py_DECREF(self);
            PyErr_SetString(PyExc_RuntimeError, "MangoPy Runtime: Failed to create an object of type Mango::Geometry::Shell");
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

PyObject *mpy_Shell_setRadius(mpy_Shell* self, PyObject *args)
{
    // Call Parameters
    double r;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "d", &r)){
        return NULL;
    }

    try{
        self->internalObject->setRadius(r);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}



PyObject *mpy_Shell_setThickness(mpy_Shell* self, PyObject *args)
{
    // Call Parameters
    double t;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "d", &t)){
        return NULL;
    }

    try{
        self->internalObject->setThickness(t);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}



PyObject *mpy_Shell_setFraction(mpy_Shell* self, PyObject *args)
{
    // Call Parameters
    double f;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "d", &f)){
        return NULL;
    }

    try{
        self->internalObject->setFraction(f);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}



PyObject *mpy_Shell_setNumberOfSides(mpy_Shell* self, PyObject *args)
{
    // Call Parameters
    int n;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "i", &n)){
        return NULL;
    }

    try{
        self->internalObject->setNumberOfSides(n);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}


/* Get Functions */

PyObject *mpy_Shell_radius(mpy_Shell* self, PyObject *args)
{
    // Return Value
    GLfloat r;

    // Call Function
    try{
        r = self->internalObject->radius();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("d", r);
}



PyObject *mpy_Shell_thickness(mpy_Shell* self, PyObject *args)
{
    // Return Value
    GLfloat t;

    // Call Function
    try{
        t = self->internalObject->thickness();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("d", t);
}



PyObject *mpy_Shell_fraction(mpy_Shell* self, PyObject *args)
{
    // Return Value
    GLfloat f;

    // Call Function
    try{
        f = self->internalObject->fraction();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("d", f);
}



PyObject *mpy_Shell_numberOfSides(mpy_Shell* self, PyObject *args)
{
    // Return Value
    int n;

    // Call Function
    try{
        n = self->internalObject->numberOfSides();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("i", n);
}


/*
    Method Table
                        */
PyMethodDef mpy_Shell_methods[] = {
    // Set
    {"setRadius", (PyCFunction)mpy_Shell_setRadius, METH_VARARGS,
     "Set the radius of a Mango::Geometry::Shell"
    },
    {"setThickness", (PyCFunction)mpy_Shell_setThickness, METH_VARARGS,
     "Set the thickness of a Mango::Geometry::Shell"
    },
    {"setFraction", (PyCFunction)mpy_Shell_setFraction, METH_VARARGS,
     "Set the fraction of a Mango::Geometry::Shell"
    },
    {"setNumberOfSides", (PyCFunction)mpy_Shell_setNumberOfSides, METH_VARARGS,
     "Set the number of sides of a Mango::Geometry::Shell"
    }, 

    // Get
    {"radius", (PyCFunction)mpy_Shell_radius, METH_NOARGS,
     "Get the radius of a Mango::Geometry::Shell"
    },
    {"thickness", (PyCFunction)mpy_Shell_thickness, METH_NOARGS,
     "Get the thickness of a Mango::Geometry::Shell"
    },
    {"fraction", (PyCFunction)mpy_Shell_fraction, METH_NOARGS,
     "Get the fraction of a Mango::Geometry::Shell"
    },
    {"numberOfSides", (PyCFunction)mpy_Shell_numberOfSides, METH_NOARGS,
     "Get the number of sides of a Mango::Geometry::Shell"
    }, 

    {NULL}  /* Sentinel */
};

PyTypeObject mpy_ShellType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "Geometry.Shell",             /* tp_name */
    sizeof(mpy_Shell),      /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)mpy_Shell_dealloc, /* tp_dealloc */
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
    "Mango::Geometry::Shell",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,              /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_Shell_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,//(initproc)mpy_Shell_init,      /* tp_init */
    0,                         /* tp_alloc */
    mpy_Shell_new,                 /* tp_new */
};

