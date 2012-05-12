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
#include <mango/pygeometry/pygeometry_colorful_object.h>


/*
    dealloc and new
                      */

void mpy_ColorfulObject_dealloc(mpy_ColorfulObject* self)
{
    delete self->internalObject;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject *mpy_ColorfulObject_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    mpy_ColorfulObject *self;

    self = (mpy_ColorfulObject *)type->tp_alloc(type, 0);
    if (self != NULL) {
      self->internalObject = new Mango::Geometry::ColorfulObject();
        if (self->internalObject == NULL){
            Py_DECREF(self);
            PyErr_SetString(PyExc_RuntimeError, "MangoPy Runtime: Failed to create an object of type Mango::Geometry::ColorfulObject");
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

PyObject *mpy_ColorfulObject_setRedComponent(mpy_ColorfulObject* self, PyObject *args)
{
    // Call Parameters
    double r;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "d", &r)){
        return NULL;
    }

    try{
        self->internalObject->setRedComponent(r);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}


PyObject *mpy_ColorfulObject_setGreenComponent(mpy_ColorfulObject* self, PyObject *args)
{
    // Call Parameters
    double r;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "d", &r)){
        return NULL;
    }

    try{
        self->internalObject->setGreenComponent(r);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *mpy_ColorfulObject_setBlueComponent(mpy_ColorfulObject* self, PyObject *args)
{
    // Call Parameters
    double r;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "d", &r)){
        return NULL;
    }

    try{
        self->internalObject->setBlueComponent(r);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *mpy_ColorfulObject_setColor(mpy_ColorfulObject* self, PyObject *args){
    // Call Parameters
    double r, g, b;

    // Parse arguments
    if (!mpy_ThreeDoublesFromArgs(args, r, g, b)){
        return NULL;
    }

    try{
        self->internalObject->setColor(r, g, b);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}

/* Get Functions */

PyObject *mpy_ColorfulObject_redComponent(mpy_ColorfulObject* self, PyObject *args)
{
    // Return Value
    double r;

    // Call Function
    try{
        r = self->internalObject->redComponent();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("d", r);
}

PyObject *mpy_ColorfulObject_greenComponent(mpy_ColorfulObject* self, PyObject *args)
{
    // Return Value
    double r;

    // Call Function
    try{
        r = self->internalObject->greenComponent();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("d", r);
}

PyObject *mpy_ColorfulObject_blueComponent(mpy_ColorfulObject* self, PyObject *args)
{
    // Return Value
    double r;

    // Call Function
    try{
        r = self->internalObject->blueComponent();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("d", r);
}

PyObject *mpy_ColorfulObject_color(mpy_ColorfulObject* self, PyObject *args){
    // Return Value
    GLfloat r, g, b;

    // Call Function
    try{
        self->internalObject->color(r, g, b);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("ddd", r, g, b);
}


/*
    Method Table
                        */
PyMethodDef mpy_ColorfulObject_methods[] = {
    // Set
    {"setRedComponent", (PyCFunction)mpy_ColorfulObject_setRedComponent, METH_VARARGS,
     "Set the red component of a Mango::Geometry::ColorfulObject"
    },
    {"setBlueComponent", (PyCFunction)mpy_ColorfulObject_setBlueComponent, METH_VARARGS,
     "Set the blue component of a Mango::Geometry::ColorfulObject"
    },
    {"setGreenComponent", (PyCFunction)mpy_ColorfulObject_setGreenComponent, METH_VARARGS,
     "Set the green component of a Mango::Geometry::ColorfulObject"
    },
    {"setColor", (PyCFunction)mpy_ColorfulObject_setColor, METH_VARARGS,
     "Set the color of a Mango::Geometry::ColorfulObject"
    },
    // Get
    {"redComponent", (PyCFunction)mpy_ColorfulObject_redComponent, METH_NOARGS,
     "Get the red component of a Mango::Geometry::ColorfulObject"
    },
   {"blueComponent", (PyCFunction)mpy_ColorfulObject_blueComponent, METH_NOARGS,
     "Get the blue component of a Mango::Geometry::ColorfulObject"
    },
   {"greenComponent", (PyCFunction)mpy_ColorfulObject_greenComponent, METH_NOARGS,
     "Get the green component of a Mango::Geometry::ColorfulObject"
    },
    {"color", (PyCFunction)mpy_ColorfulObject_color, METH_NOARGS,
     "Get the color of a Mango::Geometry::ColorfulObject"
    },


    {NULL}  /* Sentinel */
};

PyTypeObject mpy_ColorfulObjectType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "Geometry.ColorfulObject",             /* tp_name */
    sizeof(mpy_ColorfulObject),      /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)mpy_ColorfulObject_dealloc, /* tp_dealloc */
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
    "Mango::Geometry::ColorfulObject",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,              /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_ColorfulObject_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,//(initproc)mpy_ColorfulObject_init,      /* tp_init */
    0,                         /* tp_alloc */
    mpy_ColorfulObject_new,                 /* tp_new */
};
