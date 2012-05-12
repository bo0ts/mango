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

#include <mango/mangopy/mangopy_vector.h>
#include <iostream>

/*
	Conversion Methods
						*/
	

int mpy_VectorConverter(PyObject *arg, void *vector_address){
  Mango::Core::Vector v;
  if (mpy_VectorFromArgs(arg, v)){
    *static_cast<Mango::Core::Vector *>(vector_address) = v;
    return 1;
  }  
  return 0;
}
	
// This function takes the python object args and tries to extract a vector from
// it. arg can be: A tuple of two or three doubles, a vector or a tuple containing one
// of these. Returns true on success, false on failure. The calling function should return NULL
// to the python interpereter in the event of failure
bool mpy_VectorFromArgs(PyObject *arg, Mango::Core::Vector &v){
  PyObject *tmp;
  double x, y, z;
  int arg_size;
  
  // If it's a tuple with one element, unpack that element
  if (PyObject_TypeCheck(arg, &PyTuple_Type)){
    arg_size = PyTuple_Size(arg);
    if (arg_size == 1){
      if (!PyArg_ParseTuple(arg, "O", &tmp)){
	return false;
      }
      arg = tmp;
    }
  }
  
  // If we're left with a tuple, try to extract three doubles from it
  if (PyObject_TypeCheck(arg, &PyTuple_Type)){
    arg_size = PyTuple_Size(arg);
    if ((arg_size == 2) || (arg_size == 3)){
      z = 0;
      if (!PyArg_ParseTuple(arg, "dd|d", &x, &y, &z)){
	PyErr_SetString(PyExc_TypeError, "Expected an instance of class Vector or a tuple containing two or three doubles");
	return false;
      }
      v[0] = x;
      v[1] = y;
      v[2] = z;
      return true;
    }
    else{
      PyErr_SetString(PyExc_TypeError, "Expected an instance of a Vector or a tuple containing two or three doubles");
      return false;
    }
  }
  
  // If we're left with a vector, try to extract it
  if (PyObject_TypeCheck(arg, &mpy_VectorType)){
    v = reinterpret_cast<mpy_Vector *>(arg)->v;
    return true;
  }
  
  PyErr_SetString(PyExc_TypeError, "Expected an instance of a Vector or a tuple containing two or three doubles");
  return false;
}

// This function takes the python object args and tries to extract three doubles from
// it. arg can be: A tuple of two or three doubles or a tuple containing a tuple of two 
// or three doubles. If only two doubles are provided the third is defaults to zero.
// Returns true on success, false on failure. The calling function should return NULL
// to the python interpereter in the event of failure
bool mpy_ThreeDoublesFromArgs(PyObject *arg, double &x, double &y, double &z){
    PyObject *tmp;
    double _x, _y, _z;
    int arg_size;

    // If it's a tuple with one element, unpack that element
    if (PyObject_TypeCheck(arg, &PyTuple_Type)){
        arg_size = PyTuple_Size(arg);
        if (arg_size == 1){
            if (!PyArg_ParseTuple(arg, "O", &tmp)){
                return false;
            }
            arg = tmp;
        }
    }

    // If we're left with a tuple, try to extract two or three doubles from it
    if (PyObject_TypeCheck(arg, &PyTuple_Type)){
        arg_size = PyTuple_Size(arg);
        if (arg_size == 3 || arg_size == 2){
            _z = 0;
            if (!PyArg_ParseTuple(arg, "dd|d", &_x, &_y, &_z)){
                PyErr_SetString(PyExc_TypeError, "Expected two or three doubles, or a tuple containing two or three doubles");
                return false;
            }            
            
            x = _x;
            y = _y;
            z = _z;
            return true;
        }
    }

   PyErr_SetString(PyExc_TypeError, "Expected two or three doubles, or a tuple containing two or three doubles");
    return false;
}





/*
    Dealloc and New
                   	 */
    
void mpy_Vector_dealloc(mpy_Vector* self){    
  Py_TYPE(self)->tp_free((PyObject *)self);
}

PyObject *mpy_Vector_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  mpy_Vector *self;
  self = (mpy_Vector *)type->tp_alloc(type, 0);    
  return (PyObject *)self;
}

mpy_Vector *mpy_Vector_NEW(){
  mpy_Vector *object;
  object = PyObject_NEW(mpy_Vector, &mpy_VectorType);
  return object;
}


/*
    Method Definitions
                        */
    
static PyObject *mpy_Vector_richcompare(PyObject *v, PyObject *w, int op)
{
	if (op == Py_EQ || op == Py_NE){
		PyObject *true_for_eq_false_for_ne = (op == Py_EQ ? Py_True : Py_False);
		PyObject *false_for_eq_true_for_ne = (op == Py_EQ ? Py_False : Py_True);		
		PyObject *tmp_arg_as_py_double;
		
		if (PyObject_TypeCheck(v, &mpy_VectorType)){		
			if (PyObject_TypeCheck(w, &mpy_VectorType)){			
				if (((mpy_Vector*)v)->v == ((mpy_Vector*)w)->v){
					Py_INCREF(true_for_eq_false_for_ne);
					return true_for_eq_false_for_ne;
				}			
				Py_INCREF(false_for_eq_true_for_ne);
				return false_for_eq_true_for_ne;
			}	
			//else if (PyObject_TypeCheck(w, &PyLong_Type)){
			//	long w_as_long = PyLong_AsLong(w);
			else if (PyNumber_Check(w)){				
				tmp_arg_as_py_double = PyNumber_Float(w);
				if (tmp_arg_as_py_double != NULL){
					double w_as_double = PyFloat_AsDouble(tmp_arg_as_py_double);
					if (w_as_double == 0){			
						if ( ((mpy_Vector*)v)->v[0] == 0 && ((mpy_Vector*)v)->v[1] == 0 && ((mpy_Vector*)v)->v[2] == 0){
							Py_INCREF(true_for_eq_false_for_ne);
							return true_for_eq_false_for_ne;
						}				
						Py_INCREF(false_for_eq_true_for_ne);
						return false_for_eq_true_for_ne;
					}			
				}
			}		
		}		
		else if (PyNumber_Check(v)){
			if (PyObject_TypeCheck(w, &mpy_VectorType)){				
				tmp_arg_as_py_double = PyNumber_Float(v);
				if (tmp_arg_as_py_double != NULL){
					double v_as_double = PyFloat_AsDouble(tmp_arg_as_py_double);
					if (v_as_double == 0){			
						if ( ((mpy_Vector*)w)->v[0] == 0 && ((mpy_Vector*)w)->v[1] == 0 && ((mpy_Vector*)w)->v[2] == 0){
							Py_INCREF(true_for_eq_false_for_ne);
							return true_for_eq_false_for_ne;
						}		
						Py_INCREF(false_for_eq_true_for_ne);
						return false_for_eq_true_for_ne;
					}			
				}
			}		
		}
	}
	
	Py_INCREF(Py_NotImplemented);
	return Py_NotImplemented;
}

PyObject *mpy_Vector_norm(mpy_Vector* self)
{
    double norm = sqrt( (double)self->v[0]*self->v[0] +
                    (double)self->v[1]*self->v[1] +
                    (double)self->v[2]*self->v[2] );
    return Py_BuildValue("d", norm);
}

PyObject *mpy_Vector_normSq(mpy_Vector *self)
{
    double normSquared = (double)self->v[0]*self->v[0] +
                    (double)self->v[1]*self->v[1] +
                    (double)self->v[2]*self->v[2];
    return Py_BuildValue("d", normSquared);
}

PyObject *mpy_Vector_normalize(mpy_Vector *self)
{
    self->v.normalize();
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *mpy_Vector_dot(mpy_Vector *self, PyObject *args)
{
 	// Call Parameters
    Mango::Core::Vector w;

    // Parse arguments
    if (!mpy_VectorFromArgs(args, w)){
        return NULL;
    }
    	
    double dot_product = (double)self->v[0]*(double)w[0] +
                    (double)self->v[1]*(double)w[1] +
                    (double)self->v[2]*(double)w[2];
    return Py_BuildValue("d", dot_product);
}

PyObject *mpy_Vector_cross(mpy_Vector *self, PyObject *args)
{
 	// Call Parameters
    Mango::Core::Vector w;

    // Parse arguments
    if (!mpy_VectorFromArgs(args, w)){
        return NULL;
    }
    
	// Return Values
    mpy_Vector *cross_product = mpy_Vector_NEW();
    Py_XINCREF(cross_product);    
    
	cross_product->v[0] = self->v[1]*w[2] - self->v[2]*w[1];
	cross_product->v[1] = self->v[2]*w[0] - self->v[0]*w[2];
	cross_product->v[2] = self->v[0]*w[1] - self->v[1]*w[0];
    
    return Py_BuildValue("O", (PyObject *)(cross_product));
}

static PyObject *mpy_Vector_repr(PyObject *selff){
    char object_repr[50];
    mpy_Vector *self;

    //    std::cout << "Representing object" << std::endl;
    self = reinterpret_cast<mpy_Vector *>(selff);
    sprintf(object_repr, "<%.2f, %.2f, %.2f>", self->v[0], self->v[1], self->v[2]);
    //    std::cout << "Done Representing object" << std::endl;
    return PyUnicode_FromFormat("%s", object_repr);
}


PyObject *mpy_Vector_scale(mpy_Vector *self, PyObject *args){
    double k;
    if (!PyArg_ParseTuple(args, "d", &k)){
        return NULL;
    }

    self->v[0] = self->v[0] * k;
    self->v[1] = self->v[1] * k;
    self->v[2] = self->v[2] * k;

    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *mpy_Vector_call(PyObject *selff, PyObject *args, PyObject *kw){
    mpy_Vector *self;
    self = reinterpret_cast<mpy_Vector *>(selff);
    return mpy_Vector_dot(self, args);
}

static int mpy_Vector_init(mpy_Vector *self, PyObject *args, PyObject *kwds){
    PyObject *tmp;

    int arg_size = PyTuple_Size(args);
   
    if (arg_size > 0){
      if (!mpy_VectorFromArgs(args, self->v)){
	PyErr_SetString(PyExc_TypeError, "Valid constructors are Vector(), Vector(v), Vector(double, double), Vector(double, double, double)");
	return -1;
      }
    }
    else{
      self->v[0] = 0;
      self->v[1] = 0;
      self->v[2] = 0;
    }

    return 0;
}


/*
    Sequence Methods
                        */

//static
PyObject *mpy_Vector_item(mpy_Vector *self, Py_ssize_t i)
{ 
  int index = Py_SAFE_DOWNCAST(i, Py_ssize_t, int);
 
  if (index < 0 || index >= 3) {
    char indexError[100];
    sprintf(indexError, "Invalid index '%d' for three dimensional vector (valid indices are 0, 1, 2)", index);
    PyErr_SetString(PyExc_IndexError, indexError);
    return NULL;
  }
  
  return Py_BuildValue("d", self->v[index]);
}

//static
int mpy_Vector_ass_item(mpy_Vector *self, Py_ssize_t i, PyObject *v)
{
  int newval;
  int index = Py_SAFE_DOWNCAST(i, Py_ssize_t, int);

  if (index < 0 || index >= 3) {
    char indexError[100];
    sprintf(indexError, "Invalid index '%d' for three dimensional vector (valid indices are 0, 1, 2)", index);
    PyErr_SetString(PyExc_IndexError, indexError);
    return -1;
  }
  if (v == NULL){
    PyErr_SetString(PyExc_ValueError, "Cannot assign NULL object");
    return -1;
  }

  self->v[index] = PyFloat_AsDouble(v);
  return 0;
}

static PySequenceMethods mpy_Vector_as_sequence = {
	0,			                        /* sq_length */
	0,		                            /* sq_concat */
	0,		                            /* sq_repeat */
	(ssizeargfunc)mpy_Vector_item,		    /* sq_item */
	0,		                            /* sq_slice */
	(ssizeobjargproc)mpy_Vector_ass_item,		/* sq_ass_item */
	0,	                                /* sq_ass_slice */
	0,		                            /* sq_contains */
	0,	                                /* sq_inplace_concat */
	0,	                                /* sq_inplace_repeat */
};



/*
    Number Methods
                    */

static PyObject *mpy_Vector_add(mpy_Vector *v, mpy_Vector *w)
{
    mpy_Vector *result;
    
    Mango::Core::Vector t, u;
    if (!mpy_VectorFromArgs((PyObject *)v, t) || !mpy_VectorFromArgs((PyObject *)w, u)) {
        PyErr_SetString(PyExc_TypeError, "operands must be a vector and a vector, a tuple and a vector or a vector or a tuple");
        return NULL;
    }

    result = mpy_Vector_NEW();
    result->v = t + u;
    return (PyObject *)result;
}

static PyObject *mpy_Vector_inplace_add(mpy_Vector *v, mpy_Vector *w)
{
  Mango::Core::Vector u;
  if (!PyObject_TypeCheck(v, &mpy_VectorType) || !mpy_VectorFromArgs((PyObject *)w, u)) {
    PyErr_SetString(PyExc_TypeError, "second operand must be a vector or a tuple");
    return NULL;
  }
  
  v->v += u;
  Py_INCREF(v);
  return (PyObject *)v;
}

static PyObject *mpy_Vector_sub(mpy_Vector *v, mpy_Vector *w)
{
  mpy_Vector *result;
  
  Mango::Core::Vector t, u;
  if (!mpy_VectorFromArgs((PyObject *)v, t) || !mpy_VectorFromArgs((PyObject *)w, u)) {
    PyErr_SetString(PyExc_TypeError, "operands must be a vector and a vector, a tuple and a vector or a vector or a tuple");
    return NULL;
  }
  
  result = mpy_Vector_NEW();
  result->v = t - u;
  return (PyObject *)result;
}

static PyObject *mpy_Vector_inplace_sub(mpy_Vector *v, mpy_Vector *w)
{
  Mango::Core::Vector u;
  if (!PyObject_TypeCheck(v, &mpy_VectorType) || !mpy_VectorFromArgs((PyObject *)w, u)) {
    PyErr_SetString(PyExc_TypeError, "second operand must be a vector or a tuple");
    return NULL;
  }
  
  v->v -= u;
  Py_INCREF(v);
  return (PyObject *)v;
}

static PyObject *mpy_Vector_mul(PyObject *v, PyObject *w)
{		
	PyObject *tmp_arg_as_py_double;
	mpy_Vector *result;
	
	if (PyObject_TypeCheck(v, &mpy_VectorType)){		
		if (PyNumber_Check(w)){				
			tmp_arg_as_py_double = PyNumber_Float(w);
			if (tmp_arg_as_py_double != NULL){				
				double w_as_double = PyFloat_AsDouble(tmp_arg_as_py_double);				
				result = mpy_Vector_NEW();				
				result->v = (((mpy_Vector *)v)->v)*w_as_double;
				return (PyObject *)result;
			}
		}		
	}		
	else if (PyNumber_Check(v)){
		if (PyObject_TypeCheck(w, &mpy_VectorType)){				
			tmp_arg_as_py_double = PyNumber_Float(v);
			if (tmp_arg_as_py_double != NULL){
				double v_as_double = PyFloat_AsDouble(tmp_arg_as_py_double);				
				result = mpy_Vector_NEW();				
				result->v = (((mpy_Vector *)w)->v)*v_as_double;
				return (PyObject *)result;
			}
		}		
	}
	
	Py_INCREF(Py_NotImplemented);
	return Py_NotImplemented;
}

static PyObject *mpy_Vector_inplace_mul(PyObject *v, PyObject *w)
{		
	PyObject *tmp_arg_as_py_double;	
	
	if (PyObject_TypeCheck(v, &mpy_VectorType)){		
		if (PyNumber_Check(w)){				
			tmp_arg_as_py_double = PyNumber_Float(w);
			if (tmp_arg_as_py_double != NULL){				
				double w_as_double = PyFloat_AsDouble(tmp_arg_as_py_double);
				((mpy_Vector *)v)->v *= w_as_double;
				Py_INCREF(v);
				return v;
			}
		}		
	}		
	else if (PyNumber_Check(v)){
		if (PyObject_TypeCheck(w, &mpy_VectorType)){				
			tmp_arg_as_py_double = PyNumber_Float(v);
			if (tmp_arg_as_py_double != NULL){
				double v_as_double = PyFloat_AsDouble(tmp_arg_as_py_double);
				((mpy_Vector *)w)->v *= v_as_double;
				Py_INCREF(w);
				return w;
			}
		}		
	}
	
	Py_INCREF(Py_NotImplemented);
	return Py_NotImplemented;
}

static PyObject *mpy_Vector_div(PyObject *v, PyObject *w)
{	
	PyObject *tmp_arg_as_py_double;
	mpy_Vector *result;
	
	if (PyObject_TypeCheck(v, &mpy_VectorType)){		
		if (PyNumber_Check(w)){				
			tmp_arg_as_py_double = PyNumber_Float(w);
			if (tmp_arg_as_py_double != NULL){				
				double w_as_double = PyFloat_AsDouble(tmp_arg_as_py_double);	
				if (w_as_double == 0){
					PyErr_SetString(PyExc_ZeroDivisionError, "Cannot divide Vector object by zero");
					return NULL;	
				}			
				result = mpy_Vector_NEW();				
				result->v = (((mpy_Vector *)v)->v)/w_as_double;
				return (PyObject *)result;
			}
		}		
	}			
	
	Py_INCREF(Py_NotImplemented);
	return Py_NotImplemented;
}

static PyObject *mpy_Vector_inplace_div(PyObject *v, PyObject *w)
{	
	PyObject *tmp_arg_as_py_double;
	mpy_Vector *result;
	
	if (PyObject_TypeCheck(v, &mpy_VectorType)){		
		if (PyNumber_Check(w)){				
			tmp_arg_as_py_double = PyNumber_Float(w);
			if (tmp_arg_as_py_double != NULL){				
				double w_as_double = PyFloat_AsDouble(tmp_arg_as_py_double);	
				if (w_as_double == 0){
					PyErr_SetString(PyExc_ZeroDivisionError, "Cannot divide Vector object by zero");
					return NULL;	
				}		
				((mpy_Vector *)v)->v /= w_as_double;
				Py_INCREF(v);													
				return v;
			}
		}		
	}			
	
	Py_INCREF(Py_NotImplemented);
	return Py_NotImplemented;
}

static PyObject *mpy_Vector_negative(PyObject *v){
	mpy_Vector *result;
		
	result = mpy_Vector_NEW();				
	result->v = -((mpy_Vector *)v)->v;																
	return (PyObject *)result;						
}

static PyNumberMethods mpy_Vector_as_number = {
    (binaryfunc)mpy_Vector_add, 		/* nb_add */
	(binaryfunc)mpy_Vector_sub, 		/* nb_subtract */
	(binaryfunc)mpy_Vector_mul, 		/* nb_multiply */	
     0,		/*  nb_remainder */
     0,		/*  nb_divmod */
     0,		/*  nb_power */
     (unaryfunc)mpy_Vector_negative,		/*  nb_negative */
     0,		/*  nb_positive */
     0,		/*  nb_absolute */
     0,		/*  nb_bool */
     0,		/*  nb_invert */
     0,		/*  nb_lshift */
     0,		/*  nb_rshift */
     0,		/*  nb_and */
     0,		/*  nb_xor */
     0,		/*  nb_or */
     0,		/*  nb_int */
     NULL,  /* nb_reserved */
     0,		/*  nb_float */

     (binaryfunc)mpy_Vector_inplace_add,					/* nb_inplace_add */
	 (binaryfunc)mpy_Vector_inplace_sub,					/* nb_inplace_subtract */
	 (binaryfunc)mpy_Vector_inplace_mul,					/* nb_inplace_multiply*/
	 (binaryfunc)mpy_Vector_inplace_div,					/* nb_inplace_divide */
     0,		/*  nb_inplace_remainder */
     0,		/*  nb_inplace_power */
     0,		/*  nb_inplace_lshift */
     0,		/*  nb_inplace_rshift */
     0,		/*  nb_inplace_and */
     0,		/*  nb_inplace_xor */
     0,		/*  nb_inplace_or */

     (binaryfunc)mpy_Vector_div,		/*  nb_floor_divide */
     (binaryfunc)mpy_Vector_div,		/*  nb_true_divide */
     (binaryfunc)mpy_Vector_inplace_div,		/*  nb_inplace_floor_divide */
     0,		/*  nb_inplace_true_divide */

     //0		/*  nb_index */
};



/*
    Method Table
                        */
PyMethodDef mpy_Vector_methods[] = {
    {"norm", (PyCFunction)mpy_Vector_norm, METH_NOARGS,
     "Return the norm of the vector"
    },
    {"normSq", (PyCFunction)mpy_Vector_normSq, METH_NOARGS,
     "Return the square of the norm of the vector"
    },
    {"normalize", (PyCFunction)mpy_Vector_normalize, METH_NOARGS,
     "Normalizes the vector"
    },
    {"scale", (PyCFunction)mpy_Vector_scale, METH_VARARGS,
     "Scales the vector"
    },
    {"dot", (PyCFunction)mpy_Vector_dot, METH_VARARGS,
     "Dot the vector with another"
    },
    {"cross", (PyCFunction)mpy_Vector_cross, METH_VARARGS,
     "Cross the vector with another"
    },
    {NULL}  /* Sentinel */
};



PyTypeObject mpy_VectorType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "Core.Vector",             /* tp_name */
    sizeof(mpy_Vector),             /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)mpy_Vector_dealloc, /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    &mpy_Vector_repr,                         /* tp_repr */
    &mpy_Vector_as_number,                         /* tp_as_number */
    &mpy_Vector_as_sequence,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    (ternaryfunc) mpy_Vector_call,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE,   /* tp_flags */
    "Three dimensional vector",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    &mpy_Vector_richcompare,              /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_Vector_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)mpy_Vector_init,      /* tp_init */
    0,                         /* tp_alloc */
    mpy_Vector_new,                 /* tp_new */
};

