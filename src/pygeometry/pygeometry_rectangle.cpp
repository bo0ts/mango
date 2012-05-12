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
#include <mango/pygeometry/pygeometry_rectangle.h>


/*
    dealloc and new
                      */

void mpy_Rectangle_dealloc(mpy_Rectangle* self)
{
    delete self->internalObject;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject *mpy_Rectangle_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    mpy_Rectangle *self;

    self = (mpy_Rectangle *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->internalObject = new Mango::Geometry::Rectangle();
        if (self->internalObject == NULL){
            Py_DECREF(self);
            PyErr_SetString(PyExc_RuntimeError, "MangoPy Runtime: Failed to create an object of type Mango::Geometry::Rectangle");
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

PyObject *mpy_Rectangle_setWidth(mpy_Rectangle* self, PyObject *args)
{
    // Call Parameters
    double w;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "d", &w)){
        return NULL;
    }

    try{
        self->internalObject->setWidth(w);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}



PyObject *mpy_Rectangle_setLength(mpy_Rectangle* self, PyObject *args)
{
    // Call Parameters
    double l;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "d", &l)){
        return NULL;
    }

    try{
        self->internalObject->setLength(l);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}



PyObject *mpy_Rectangle_setDimensions(mpy_Rectangle* self, PyObject *args)
{
    // Call Parameters
    double w;
    double l;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "dd", &w, &l)){
        return NULL;
    }

    try{
        self->internalObject->setDimensions(w, l);
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}



PyObject *mpy_Rectangle_setStyle(mpy_Rectangle* self, PyObject *args)
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

PyObject *mpy_Rectangle_setRenderReverseOrientation(mpy_Rectangle *self, PyObject* args){
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

PyObject *mpy_Rectangle_width(mpy_Rectangle* self, PyObject *args)
{
    // Return Value
    GLfloat w;

    // Call Function
    try{
        w = self->internalObject->width();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("d", w);
}



PyObject *mpy_Rectangle_length(mpy_Rectangle* self, PyObject *args)
{
    // Return Value
    GLfloat l;

    // Call Function
    try{
        l = self->internalObject->length();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("d", l);
}



PyObject *mpy_Rectangle_style(mpy_Rectangle* self, PyObject *args)
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

PyObject *mpy_Rectangle_renderReverseOrientation(mpy_Rectangle *self){
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
PyMethodDef mpy_Rectangle_methods[] = {
    // Set
    {"setWidth", (PyCFunction)mpy_Rectangle_setWidth, METH_VARARGS,
     "Set the width of a Mango::Geometry::Rectangle"
    },
    {"setLength", (PyCFunction)mpy_Rectangle_setLength, METH_VARARGS,
     "Set the length of a Mango::Geometry::Rectangle"
    },
    {"setDimensions", (PyCFunction)mpy_Rectangle_setDimensions, METH_VARARGS,
     "Set the dimensions of a Mango::Geometry::Rectangle"
    },
    {"setStyle", (PyCFunction)mpy_Rectangle_setStyle, METH_VARARGS,
     "Set the style of a Mango::Geometry::Rectangle"
    }, 
    {"setRenderReverseOrientation", (PyCFunction)mpy_Rectangle_setRenderReverseOrientation, METH_VARARGS,
     "Cause the object to also render the reverse orientation if passed true, and not to be also render the reverse orientation if passed false"
    }, 

    // Get
    {"width", (PyCFunction)mpy_Rectangle_width, METH_NOARGS,
     "Get the width of a Mango::Geometry::Rectangle"
    },
    {"length", (PyCFunction)mpy_Rectangle_length, METH_NOARGS,
     "Get the length of a Mango::Geometry::Rectangle"
    },
    {"style", (PyCFunction)mpy_Rectangle_style, METH_NOARGS,
     "Get the style of a Mango::Geometry::Rectangle"
    }, 
    {"renderReverseOrientation", (PyCFunction)mpy_Rectangle_renderReverseOrientation, METH_NOARGS,
     "Returns true if the object also renders the reverse orientation, false otherwise"
    }, 

    {NULL}  /* Sentinel */
};

PyTypeObject mpy_RectangleType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "Geometry.Rectangle",             /* tp_name */
    sizeof(mpy_Rectangle),      /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)mpy_Rectangle_dealloc, /* tp_dealloc */
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
    "Mango::Geometry::Rectangle",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,              /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_Rectangle_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,//(initproc)mpy_Rectangle_init,      /* tp_init */
    0,                         /* tp_alloc */
    mpy_Rectangle_new,                 /* tp_new */
};

