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
#include <mango/pygeometry/pygeometry_coordinate_system.h>


/*
    dealloc and new
                      */

void mpy_CoordinateSystem_dealloc(mpy_CoordinateSystem* self)
{
    delete self->internalObject;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject *mpy_CoordinateSystem_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    mpy_CoordinateSystem *self;

    self = (mpy_CoordinateSystem *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->internalObject = new Mango::Geometry::CoordinateSystem();
        if (self->internalObject == NULL){
            Py_DECREF(self);
            PyErr_SetString(PyExc_RuntimeError, "MangoPy Runtime: Failed to create an object of type Mango::Geometry::CoordinateSystem");
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

PyObject *mpy_CoordinateSystem_setAxisThickness(mpy_CoordinateSystem* self, PyObject *args)
{
    // Call Parameters
    double t;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "d", &t)){
        return NULL;
    }

    try{
        self->internalObject->setAxisThickness(t);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}



PyObject *mpy_CoordinateSystem_setAxisLength(mpy_CoordinateSystem* self, PyObject *args)
{
    // Call Parameters
    double l;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "d", &l)){
        return NULL;
    }

    try{
        self->internalObject->setAxisLength(l);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}



PyObject *mpy_CoordinateSystem_setRightHanded(mpy_CoordinateSystem *self, PyObject* args){
    // Call Parameters
    bool should_be_right_handed;
    PyObject *py_should_be_right_handed;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "O", &py_should_be_right_handed) || !PyBool_Check(py_should_be_right_handed)){
        PyErr_SetString(PyExc_TypeError, "Expected True or False");
        return NULL;
    }

    // Call Function
    try{
        should_be_right_handed = (PyObject_IsTrue(py_should_be_right_handed) == 1);
        self->internalObject->setRightHanded(should_be_right_handed);
    }
    catch (Mango::Core::Error &e){
        // An error occured, raise an appropriate Python exception and return NULL
        return pythonExceptionFromCException(e);
    }

    // Return result
    Py_INCREF(Py_None);
    return Py_None;
}


/* Get Functions */

PyObject *mpy_CoordinateSystem_axisThickness(mpy_CoordinateSystem* self, PyObject *args)
{
    // Return Value
    GLfloat t;

    // Call Function
    try{
        t = self->internalObject->axisThickness();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("d", t);
}



PyObject *mpy_CoordinateSystem_axisLength(mpy_CoordinateSystem* self, PyObject *args)
{
    // Return Value
    GLfloat l;

    // Call Function
    try{
        l = self->internalObject->axisLength();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("d", l);
}



PyObject *mpy_CoordinateSystem_rightHanded(mpy_CoordinateSystem *self){
    // Function Return Values
    bool is_right_handed;

    // Parse arguments

    // Call Function
    try{
        is_right_handed = self->internalObject->rightHanded();
    }
    catch (Mango::Core::Error &e){
        // An error occured, raise an appropriate Python exception and return NULL
        return pythonExceptionFromCException(e);
    }

    // Return result
    if (is_right_handed){
        Py_INCREF(Py_True);
        return Py_True;
    }
    else{
        Py_INCREF(Py_False);
        return Py_False;
    }
}


/*
    Method Table
                        */
PyMethodDef mpy_CoordinateSystem_methods[] = {
    // Set
    {"setAxisThickness", (PyCFunction)mpy_CoordinateSystem_setAxisThickness, METH_VARARGS,
     "Set the axis thickness of a Mango::Geometry::CoordinateSystem"
    },
    {"setAxisLength", (PyCFunction)mpy_CoordinateSystem_setAxisLength, METH_VARARGS,
     "Set the axis length of a Mango::Geometry::CoordinateSystem"
    },
    {"setRightHanded", (PyCFunction)mpy_CoordinateSystem_setRightHanded, METH_VARARGS,
     "Cause the object to be right handed if passed true, and not to be right handed if passed false"
    }, 

    // Get
    {"axisThickness", (PyCFunction)mpy_CoordinateSystem_axisThickness, METH_NOARGS,
     "Get the axis thickness of a Mango::Geometry::CoordinateSystem"
    },
    {"axisLength", (PyCFunction)mpy_CoordinateSystem_axisLength, METH_NOARGS,
     "Get the axis length of a Mango::Geometry::CoordinateSystem"
    },
    {"rightHanded", (PyCFunction)mpy_CoordinateSystem_rightHanded, METH_NOARGS,
     "Returns true if the object is right handed, false otherwise"
    }, 

    {NULL}  /* Sentinel */
};

PyTypeObject mpy_CoordinateSystemType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "Geometry.CoordinateSystem",             /* tp_name */
    sizeof(mpy_CoordinateSystem),      /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)mpy_CoordinateSystem_dealloc, /* tp_dealloc */
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
    "Mango::Geometry::CoordinateSystem",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,              /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_CoordinateSystem_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,//(initproc)mpy_CoordinateSystem_init,      /* tp_init */
    0,                         /* tp_alloc */
    mpy_CoordinateSystem_new,                 /* tp_new */
};

