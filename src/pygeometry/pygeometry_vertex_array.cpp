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
#include <mango/pygeometry/pygeometry_vertex_array.h>

/*
    dealloc and new
                      */

void mpy_VertexArray_dealloc(mpy_VertexArray* self)
{
    delete self->internalObject;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject *mpy_VertexArray_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    mpy_VertexArray *self;

    self = (mpy_VertexArray *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->internalObject = new Mango::Geometry::VertexArray();
        if (self->internalObject == NULL){
            Py_DECREF(self);
            PyErr_SetString(PyExc_RuntimeError, "MangoPy Runtime: Failed to create an object of type Mango::Geometry::VertexArray");
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

PyObject *mpy_VertexArray_setStyle(mpy_VertexArray* self, PyObject *args)
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

PyObject *mpy_VertexArray_setRenderReverseOrientation(mpy_VertexArray *self, PyObject* args){
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

PyObject *mpy_VertexArray_size(mpy_VertexArray* self, PyObject *args)
{
    // Return Value
    int n;

    // Call Function
    try{
        n = self->internalObject->size();
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    return Py_BuildValue("i", n);
}



PyObject *mpy_VertexArray_style(mpy_VertexArray* self, PyObject *args)
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

PyObject *mpy_VertexArray_renderReverseOrientation(mpy_VertexArray *self){
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

/* Vertex Methods */

PyObject *mpy_VertexArray_add(mpy_VertexArray* self, PyObject *args){
  // Call Parameters
  Mango::Core::Vector vertex;

  // Parse arguments
  if (!mpy_VectorFromArgs(args, vertex)){
    return NULL;
  }
  
  try{
    self->internalObject->add(vertex);
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
  
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_VertexArray_removeAt(mpy_VertexArray* self, PyObject *args)
{
    // Call Parameters
    int index;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "i", &index)){
        return NULL;
    }

    try{
        self->internalObject->removeAt(index);        
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *mpy_VertexArray_insertAt(mpy_VertexArray* self, PyObject *args)
{
    // Call Parameters
    int index;
    Mango::Core::Vector vertex;
    PyObject *py_vertex;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "iO", &index, &py_vertex)){
        return NULL;
    }
    if (!mpy_VectorFromArgs(py_vertex, vertex)){
      return NULL;
    }

    try{
      self->internalObject->insertAt(index, vertex);        
    }
    catch (Mango::Core::Error &e){
        return pythonExceptionFromCException(e);
    }

    Py_INCREF(Py_None);
    return Py_None;
}


/*
    Method Table
                        */
PyMethodDef mpy_VertexArray_methods[] = {
    // Set
    {"setStyle", (PyCFunction)mpy_VertexArray_setStyle, METH_VARARGS,
     "Set the style of a Mango::Geometry::VertexArray"
    }, 
   {"setRenderReverseOrientation", (PyCFunction)mpy_VertexArray_setRenderReverseOrientation, METH_VARARGS,
     "Cause the object to also render the reverse orientation if passed true, and not to be also render the reverse orientation if passed false"
    }, 

    // Get
    {"size", (PyCFunction)mpy_VertexArray_size, METH_NOARGS,
     "Get the size of a Mango::Geometry::VertexArray"
    },
    {"style", (PyCFunction)mpy_VertexArray_style, METH_NOARGS,
     "Get the style of a Mango::Geometry::VertexArray"
    }, 
    {"renderReverseOrientation", (PyCFunction)mpy_VertexArray_renderReverseOrientation, METH_NOARGS,
     "Returns true if the object also renders the reverse orientation, false otherwise"
    }, 

    // Vertex
    {"add", (PyCFunction)mpy_VertexArray_add, METH_VARARGS,
     "Add a vertex to the vertex array (at the end of the array)"
    },
    {"removeAt", (PyCFunction)mpy_VertexArray_removeAt, METH_VARARGS,
     "remove a vertex at a given index from the vertex array"
    },
    {"insertAt", (PyCFunction)mpy_VertexArray_insertAt, METH_VARARGS,
     "inserts a vertex at a given index in the vertex array"
    },

    {NULL}  /* Sentinel */
};



/*   Sequence Methods */

static Py_ssize_t mpy_VertexArray_length(mpy_VertexArray *self)
{
  return self->internalObject->size();
}

static PyObject *mpy_VertexArray_repr(PyObject *self)
{
  Py_ssize_t i;
  PyObject *s, *temp;
  PyObject *pieces = NULL, *result = NULL;
  
  if (reinterpret_cast<mpy_VertexArray *>(self)->internalObject->size() == 0) {
    result = PyUnicode_FromString("[]");
    goto Done;
  }
  
  pieces = PyList_New(0);
  if (pieces == NULL){
    goto Done;
  }
  
  char vertex_str[30];
  for (i = 0; i < reinterpret_cast<mpy_VertexArray *>(self)->internalObject->size(); ++i) {
    int status;
    Mango::Core::Vector v = reinterpret_cast<mpy_VertexArray *>(self)->internalObject->vertexAt(i);
    sprintf(vertex_str, "<%.2f, %.2f, %.2f>", v[0], v[1], v[2]);
    s = PyUnicode_FromString(vertex_str);
    if (s == NULL){
      goto Done;
    }
    status = PyList_Append(pieces, s);
    Py_DECREF(s);  /* append created a new ref */
    if (status < 0){
      goto Done;
    }
  }
  
  /* Add "[]" decorations to the first and last items. */
  assert(PyList_GET_SIZE(pieces) > 0);
  char vertexarray_string[50];
  sprintf(vertexarray_string, "<VertexArray #%d   ", reinterpret_cast<mpy_VertexArray *>(self)->internalObject->objectID());
  //s = PyUnicode_FromString("<VertexArray [");
  s = PyUnicode_FromString(vertexarray_string);
  if (s == NULL)
    goto Done;
  temp = PyList_GET_ITEM(pieces, 0);
  PyUnicode_AppendAndDel(&s, temp);
  PyList_SET_ITEM(pieces, 0, s);
  if (s == NULL)
    goto Done;
  
  s = PyUnicode_FromString(">");
  if (s == NULL)
    goto Done;
  temp = PyList_GET_ITEM(pieces, PyList_GET_SIZE(pieces) - 1);
  PyUnicode_AppendAndDel(&temp, s);
  PyList_SET_ITEM(pieces, PyList_GET_SIZE(pieces) - 1, temp);
  if (temp == NULL){
    goto Done;
  }
  
  /* Paste them all together with ", " between. */
  s = PyUnicode_FromString(", ");
  if (s == NULL)
    goto Done;
  result = PyUnicode_Join(s, pieces);
  Py_DECREF(s);
  
 Done:
  Py_XDECREF(pieces);
  return result;
}


static PyObject *mpy_VertexArray_item(PyObject *selff, Py_ssize_t i)
{	
  mpy_VertexArray *self;
  if (!PyObject_TypeCheck(selff, &mpy_VertexArrayType)){
    PyErr_SetString(PyExc_TypeError, "Expected VertexArray or derived claass");
  }
  self = reinterpret_cast<mpy_VertexArray *>(selff);
  
  mpy_Vector *pos;
  pos = mpy_Vector_NEW();
  try{
    pos->v = self->internalObject->vertexAt(i);
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  Py_INCREF(pos);
  return (PyObject *)pos;
}

static int mpy_VertexArray_ass_item(PyListObject *a, Py_ssize_t i, PyObject *v)
{
	PyObject *old_value;
	mpy_VertexArray *self = (mpy_VertexArray *)a;
	Mango::Core::Vector vertex;

	if (!mpy_VectorFromArgs(v, vertex)){
	  return -1;
	}
	if (i < 0 || i >= self->internalObject->size()) {
		PyErr_SetString(PyExc_IndexError,
				"VertexArray assignment index out of range");
		return -1;
	}

	self->internalObject->removeAt(i);
	if (v != NULL){
	  self->internalObject->insertAt(i, vertex);
	}
	
	return 0;
}


static PySequenceMethods mpy_VertexArray_as_sequence = {
  (lenfunc)mpy_VertexArray_length,			/* sq_length */
  0,		/* sq_concat */
  0,		/* sq_repeat */
  (ssizeargfunc)mpy_VertexArray_item,		/* sq_item */
  0, 		/* sq_slice */
  (ssizeobjargproc)mpy_VertexArray_ass_item,		/* sq_ass_item */
  0,	/* sq_ass_slice */
  0,		/* sq_contains */
  0,	/* sq_inplace_concat */
  0,	/* sq_inplace_repeat */
};




static PyObject *mpy_VertexArray_subscript(mpy_VertexArray* self, PyObject* item){
  if (PyIndex_Check(item)) {
    Py_ssize_t i;
    i = PyNumber_AsSsize_t(item, PyExc_IndexError);
    if (i == -1 && PyErr_Occurred()){
      return NULL;
    }
    if (i < 0){
      i += self->internalObject->size();
    }
    return mpy_VertexArray_item((PyObject *)self, i);
  }
  else if (PySlice_Check(item)) {
    Py_ssize_t start, stop, step, slicelength, cur, i;
    PyObject* result;
    PyObject* it;
    PyObject **src, **dest;
    
    if (PySlice_GetIndicesEx(item, self->internalObject->size(),
			     &start, &stop, &step, &slicelength) < 0) {
      return NULL;
    }
    
    if (slicelength <= 0) {
      return PyList_New(0);
    }
    else {
      result = PyList_New(slicelength);
      if (!result){
	return NULL;
      }

      mpy_Vector *vertex;
      dest = ((PyListObject *)result)->ob_item;
      for (cur = start, i = 0; i < slicelength; cur += step, i += 1){
	vertex = mpy_Vector_NEW();
	vertex->v = self->internalObject->vertexAt(cur);
	Py_INCREF(vertex);
	dest[i] = (PyObject *)vertex;
      }

      return result;
    }
  }
  else {
    PyErr_Format(PyExc_TypeError,
		 "list indices must be integers, not %.200s",
		 item->ob_type->tp_name);
    return NULL;
  }
}



static PyMappingMethods mpy_VertexArray_as_mapping = {
	(lenfunc)mpy_VertexArray_length,
	(binaryfunc)mpy_VertexArray_subscript,
	0,//(objobjargproc)list_ass_subscript
};








PyTypeObject mpy_VertexArrayType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "Geometry.VertexArray",             /* tp_name */
    sizeof(mpy_VertexArray),      /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)mpy_VertexArray_dealloc, /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    &mpy_VertexArray_repr,                         /* tp_repr */
    0,                         /* tp_as_number */
    &mpy_VertexArray_as_sequence,                         /* tp_as_sequence */
    &mpy_VertexArray_as_mapping,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE,   /* tp_flags */
    "Mango::Geometry::VertexArray",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,              /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_VertexArray_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,//(initproc)mpy_VertexArray_init,      /* tp_init */
    0,                         /* tp_alloc */
    mpy_VertexArray_new,                 /* tp_new */
};

