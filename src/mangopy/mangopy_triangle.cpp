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
#include <mango/mangopy/mangopy_triangle.h>

/*
    Dealloc and New
                    */
    

void mpy_Triangle_dealloc(mpy_Triangle *self)
{
    delete self->internalObject;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject *mpy_Triangle_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    mpy_Triangle *self;

    self = (mpy_Triangle *)type->tp_alloc(type, 0);    
    if (self != NULL) {        
        self->internalObject = new Mango::Core::Triangle();
        if (self->internalObject == NULL){
            Py_DECREF(self);
            PyErr_SetString(PyExc_RuntimeError, "MangoPy Runtime: Failed to create an object of type Mango::Core::Triangle");
            return NULL;
        }
	self->parentFrame = NULL;
    }    
    return (PyObject *)self;
}




/* Set Functions */
PyObject *mpy_Triangle_setSize(mpy_Triangle *self, PyObject* args){
    // Call Parameters
    double size;
    
    if (!PyArg_ParseTuple(args, "d", &size)){    
        return NULL;
    }    
    
    // Call Function
    try{
        self->internalObject->setSize(size);
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

PyObject *mpy_Triangle_size(mpy_Triangle *self, PyObject* args){        
    // Return Values
    GLfloat size;            
    
    // Call Function
    try{
        size = self->internalObject->size();
    }
    catch (Mango::Core::Error &e){
        // An error occured, raise an appropriate Python exception and return NULL
        return pythonExceptionFromCException(e);
    }

    // Return result    
    return Py_BuildValue("d", (double)size);
}



/*
    Method Definitions
                        */
    /*
PyObject *mpy_Triangle_objectType(mpy_Triangle *self)
{
    PyObject *result;
    result = PyUnicode_FromString(static_cast<Mango::Core::Triangle *>(self->internalObject)->objectType());
    return result;
}*/
/*

static PyObject *mpy_Triangle_repr(PyObject *selff){
    char object_repr[50];
    mpy_Triangle *self;

    self = reinterpret_cast<mpy_Triangle *>(selff);
    sprintf(object_repr, "<%s #%d>", self->internalObject->objectType(), self->internalObject->getObjectID());
    return PyUnicode_FromString(object_repr);
}*/












/*
    Method Table
                        */
PyMethodDef mpy_Triangle_methods[] = {    
    
    // Set Functions
    {"setSize", (PyCFunction)mpy_Triangle_setSize, METH_VARARGS,
     "set the size of the triangle (distance from its center to one of its vertices)"
    },		
	
    // Get Functions
    {"size", (PyCFunction)mpy_Triangle_size, METH_NOARGS,
     "Returns the size of the triangle (distance from its center to one of its vertices)"
    },

    {NULL}  /* Sentinel */
};



PyTypeObject mpy_TriangleType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "Core.Triangle",             /* tp_name */
    sizeof(mpy_Triangle),      /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)mpy_Triangle_dealloc, /* tp_dealloc */
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
    "Core Mango triangle",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,              /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_Triangle_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,//(initproc)mpy_Triangle_init,      /* tp_init */
    0,                         /* tp_alloc */
    mpy_Triangle_new,                 /* tp_new */
};

