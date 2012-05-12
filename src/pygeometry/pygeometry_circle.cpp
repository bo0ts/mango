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
#include <mango/pygeometry/pygeometry_circle.h>


/*
    dealloc and new
                      */

void mpy_Circle_dealloc(mpy_Circle* self)
{
    delete self->internalObject;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject *mpy_Circle_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    mpy_Circle *self;

    self = (mpy_Circle *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->internalObject = new Mango::Geometry::Circle();
        if (self->internalObject == NULL){
            Py_DECREF(self);
            PyErr_SetString(PyExc_RuntimeError, "MangoPy Runtime: Failed to create an object of type Mango::Geometry::Circle");
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

PyObject *mpy_Circle_setRadius(mpy_Circle* self, PyObject *args)
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



PyObject *mpy_Circle_setStyle(mpy_Circle* self, PyObject *args)
{
    // Call Parameters
    int style;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "i", &style)){
        return NULL;
    }

    try{
        self->internalObject->setStyle(style);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}



PyObject *mpy_Circle_setNumberOfSides(mpy_Circle* self, PyObject *args)
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



PyObject *mpy_Circle_setRenderReverseOrientation(mpy_Circle *self, PyObject* args){
    // Call Parameters
    bool should_also_render_reverse_orientation;
    PyObject *py_should_also_render_reverse_orientation;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "O", &py_should_also_render_reverse_orientation) || !PyBool_Check(py_should_also_render_reverse_orientation)){
        PyErr_SetString(PyExc_TypeError, "Expected True or False");
        return NULL;
    }

    // Call Function
    try{
        should_also_render_reverse_orientation = (PyObject_IsTrue(py_should_also_render_reverse_orientation) == 1);
        self->internalObject->setRenderReverseOrientation(should_also_render_reverse_orientation);
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

PyObject *mpy_Circle_radius(mpy_Circle* self, PyObject *args)
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



PyObject *mpy_Circle_style(mpy_Circle* self, PyObject *args)
{
    // Return Value
    int style;

    // Call Function
    try{
        style = self->internalObject->style();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("i", style);
}



PyObject *mpy_Circle_numberOfSides(mpy_Circle* self, PyObject *args)
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

PyObject *mpy_Circle_renderReverseOrientation(mpy_Circle *self){
    // Function Return Values
    bool renders_reverse_orientation;

    // Parse arguments

    // Call Function
    try{
        renders_reverse_orientation = self->internalObject->renderReverseOrientation();
    }
    catch (Mango::Core::Error &e){
        // An error occured, raise an appropriate Python exception and return NULL
        return pythonExceptionFromCException(e);
    }

    // Return result
    if (renders_reverse_orientation){
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
PyMethodDef mpy_Circle_methods[] = {
    // Set
    {"setRadius", (PyCFunction)mpy_Circle_setRadius, METH_VARARGS,
     "Set the radius of a Mango::Geometry::Circle"
    },
    {"setStyle", (PyCFunction)mpy_Circle_setStyle, METH_VARARGS,
     "Set the style of a Mango::Geometry::Circle"
    },
    {"setNumberOfSides", (PyCFunction)mpy_Circle_setNumberOfSides, METH_VARARGS,
     "Set the number of sides of a Mango::Geometry::Circle"
    },
    {"setRenderReverseOrientation", (PyCFunction)mpy_Circle_setRenderReverseOrientation, METH_VARARGS,
     "Cause the object to also render the reverse orientation if passed true, and not to be also render the reverse orientation if passed false"
    }, 

    // Get
    {"radius", (PyCFunction)mpy_Circle_radius, METH_NOARGS,
     "Get the radius of a Mango::Geometry::Circle"
    },
    {"style", (PyCFunction)mpy_Circle_style, METH_NOARGS,
     "Get the style of a Mango::Geometry::Circle"
    },
    {"numberOfSides", (PyCFunction)mpy_Circle_numberOfSides, METH_NOARGS,
     "Get the number of sides of a Mango::Geometry::Circle"
    },
    {"renderReverseOrientation", (PyCFunction)mpy_Circle_renderReverseOrientation, METH_NOARGS,
     "Returns true if the object also renders the reverse orientation, false otherwise"
    }, 

    {NULL}  /* Sentinel */
};

PyTypeObject mpy_CircleType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "Geometry.Circle",             /* tp_name */
    sizeof(mpy_Circle),      /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)mpy_Circle_dealloc, /* tp_dealloc */
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
    "Mango::Geometry::Circle",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,              /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_Circle_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,//(initproc)mpy_Circle_init,      /* tp_init */
    0,                         /* tp_alloc */
    mpy_Circle_new,                 /* tp_new */
};

