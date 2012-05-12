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


#include <mango/mangopy/mangopy_matrix.h>
#include <mango/mangopy/mangopy_vector.h>
#include <iostream>

/*
    Dealloc and New
                   	 */
    
void mpy_Matrix_dealloc(mpy_Matrix* self){    
  Py_TYPE(self)->tp_free((PyObject *)self);
}

PyObject *mpy_Matrix_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  mpy_Matrix *self;
  self = (mpy_Matrix *)type->tp_alloc(type, 0);    
  return (PyObject *)self;
}

mpy_Matrix *mpy_Matrix_NEW(){
  mpy_Matrix *object;
  object = PyObject_NEW(mpy_Matrix, &mpy_MatrixType);
  return object;
}


/*
    Method Definitions
                        */
    
static PyObject *mpy_Matrix_richcompare(PyObject *M, PyObject *N, int op)
{
	if (op == Py_EQ || op == Py_NE){
		PyObject *true_for_eq_false_for_ne = (op == Py_EQ ? Py_True : Py_False);
		PyObject *false_for_eq_true_for_ne = (op == Py_EQ ? Py_False : Py_True);		
		PyObject *tmp_arg_as_py_double;
		
		if (PyObject_TypeCheck(M, &mpy_MatrixType)){
			if (PyObject_TypeCheck(N, &mpy_MatrixType)){			
				if (((mpy_Matrix*)M)->M == ((mpy_Matrix*)N)->M){
					Py_INCREF(true_for_eq_false_for_ne);
					return true_for_eq_false_for_ne;
				}			
				Py_INCREF(false_for_eq_true_for_ne);
				return false_for_eq_true_for_ne;
			}	
		}		
	}
	
	Py_INCREF(Py_NotImplemented);
	return Py_NotImplemented;
}


static PyObject *mpy_Matrix_repr(PyObject *selff){
    char object_repr[75];
    mpy_Matrix *self;

    self = reinterpret_cast<mpy_Matrix *>(selff);
    sprintf(object_repr, \
	    "|%.2f, %.2f, %.2f|\n"			\
	    "|%.2f, %.2f, %.2f|\n" \
	    "|%.2f, %.2f, %.2f|", \
	    self->M[0][0], self->M[0][1], self->M[0][2],
	    self->M[1][0], self->M[1][1], self->M[1][2],
	    self->M[2][0], self->M[2][1], self->M[2][2]);
    return PyUnicode_FromFormat("%s", object_repr);
}


PyObject *mpy_Matrix_scale(mpy_Matrix *self, PyObject *args){
    double k;
    if (!PyArg_ParseTuple(args, "d", &k)){
        return NULL;
    }

    self->M *= k;

    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *mpy_Matrix_det(mpy_Matrix *self, PyObject* args){
  // Call Parameters
  double det;
  // Parse arguments  

  // Call Function
  try{
    det = self->M.det(); 
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  return Py_BuildValue("d", det);
}

PyObject *mpy_Matrix_tr(mpy_Matrix *self, PyObject* args){
  // Call Parameters
  double tr;
  // Parse arguments  

  // Call Function
  try{
    tr = self->M.tr(); 
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  return Py_BuildValue("d", tr);
}

PyObject *mpy_Matrix_transform(mpy_Matrix *self, PyObject* args){
  // Call Parameters
  Mango::Core::Vector v;
  mpy_Matrix *M;
  mpy_Matrix *matrix_result = mpy_Matrix_NEW();
  mpy_Vector *vector_result = mpy_Vector_NEW();
  
  // Parse arguments  
  bool arg_is_matrix = false;
  if (!PyArg_ParseTuple(args, "O&", mpy_VectorConverter, static_cast<void *>(&v))){
    PyErr_Clear();
    if (PyArg_ParseTuple(args, "O!", &mpy_MatrixType, &M)){
      arg_is_matrix = true;
    }
    else{
      PyErr_SetString(PyExc_TypeError, "Expected a vector or a matrix");
      return NULL;
    }
  }

  // Call Function
  try{
    if (arg_is_matrix){
      matrix_result->M = self->M.transform(M->M);
    }
    else{
      vector_result->v = self->M.transform(v);
    }
     
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  PyObject *result = (arg_is_matrix ? (PyObject *)matrix_result : (PyObject *)vector_result);
  return Py_BuildValue("O", result);
}

PyObject *mpy_Matrix_rightTransform(mpy_Matrix *self, PyObject* args){
  // Call Parameters
  Mango::Core::Vector v;
  mpy_Matrix *M;
  mpy_Matrix *matrix_result = mpy_Matrix_NEW();
  mpy_Vector *vector_result = mpy_Vector_NEW();
  
  // Parse arguments  
  bool arg_is_matrix = false;
  if (!PyArg_ParseTuple(args, "O&", mpy_VectorConverter, static_cast<void *>(&v))){
    PyErr_Clear();
    if (PyArg_ParseTuple(args, "O!", &mpy_MatrixType, &M)){
      arg_is_matrix = true;
    }
    else{
      PyErr_SetString(PyExc_TypeError, "Expected a vector or a matrix");
      return NULL;
    }
  }

  // Call Function
  try{
    if (arg_is_matrix){
      matrix_result->M = self->M.rightTransform(M->M);
    }
    else{
      vector_result->v = self->M.rightTransform(v);
    }     
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  PyObject *result = (arg_is_matrix ? (PyObject *)matrix_result : (PyObject *)vector_result);
  return Py_BuildValue("O", result);
}


PyObject *mpy_Matrix_call(PyObject *selff, PyObject *args, PyObject *kw){
    mpy_Matrix *self;
    self = reinterpret_cast<mpy_Matrix *>(selff);
    return mpy_Matrix_transform(self, args);
}

static int mpy_Matrix_init(mpy_Matrix *self, PyObject *args, PyObject *kwds){
    PyObject *tmp;
    int arg_size;
    
    double m00, m01, m02;
    double m10, m11, m12;
    double m20, m21, m22;

    m00 = 1; m01 = 0; m02 = 0;
    m10 = 0; m11 = 1; m12 = 0;
    m20 = 0; m21 = 0; m22 = 1;
       
    arg_size = PyTuple_Size(args);
    m22 = (arg_size == 2 ? 0 : 1);
    
    if ((arg_size == 2)){
      if (!PyArg_ParseTuple(args, "(dd)(dd)", 
			    &m00, &m01, 
			    &m10, &m11)){
	return -1;
      }
    }
    else if (!PyArg_ParseTuple(args, "|(ddd)(ddd)(ddd)", 
			       &m00, &m01, &m02, 
			       &m10, &m11, &m12, 
			       &m20, &m21, &m22)){
	return -1;
    }

    self->M[0][0] = m00;
    self->M[0][1] = m01;
    self->M[0][2] = m02;

    self->M[1][0] = m10;
    self->M[1][1] = m11;
    self->M[1][2] = m12;

    self->M[2][0] = m20;
    self->M[2][1] = m21;
    self->M[2][2] = m22;

    return 0;
}


/*
    Sequence Methods
                        */

//static
PyObject *mpy_Matrix_item(mpy_Matrix *self, Py_ssize_t i)
{ 
  int index = Py_SAFE_DOWNCAST(i, Py_ssize_t, int);
 
  if (index < 0 || index >= 3) {
    char indexError[100];
    sprintf(indexError, "Invalid index '%d' for three dimensional matrix (valid indices are 0, 1, 2)", index);
    PyErr_SetString(PyExc_IndexError, indexError);
    return NULL;
  }
  
  return Py_BuildValue("ddd", self->M[index][0], self->M[index][1], self->M[index][2]);
}

//static
int mpy_Matrix_ass_slice(mpy_Matrix *self, Py_ssize_t i, Py_ssize_t j, PyObject *v)
{
  int newval;
  int index = Py_SAFE_DOWNCAST(i, Py_ssize_t, int);
  int jndex = Py_SAFE_DOWNCAST(j, Py_ssize_t, int);

  if (index < 0 || index >= 3 || jndex < 0 || jndex >= 3) {
    char indexError[100];
    sprintf(indexError, "Invalid indices '%d, %d' for three dimensional matrix (valid indices are 0, 1, 2)", index, jndex);
    PyErr_SetString(PyExc_IndexError, indexError);
    return -1;
  }
  if (v == NULL){
    PyErr_SetString(PyExc_ValueError, "Cannot assign NULL object");
    return -1;
  }

  self->M[index][jndex] = PyFloat_AsDouble(v);
  return 0;
}

static PySequenceMethods mpy_Matrix_as_sequence = {
	0,			                        /* sq_length */
	0,		                            /* sq_concat */
	0,		                            /* sq_repeat */
	(ssizeargfunc)mpy_Matrix_item,		    /* sq_item */
	0,		                            /* sq_slice */
	0,                      		/* sq_ass_item */
	(void *)mpy_Matrix_ass_slice,  /* sq_ass_slice */
	0,		                        /* sq_contains */
	0,	                                /* sq_inplace_concat */
	0,	                                /* sq_inplace_repeat */
};



/*
    Number Methods
                    */

static PyObject *mpy_Matrix_add(mpy_Matrix *M, mpy_Matrix *N)
{
    mpy_Matrix *result;    
    result = mpy_Matrix_NEW();
    result->M = M->M + N->M;
    return (PyObject *)result;
}

static PyObject *mpy_Matrix_inplace_add(mpy_Matrix *M, mpy_Matrix *N)
{  
  M->M += N->M;
  Py_INCREF(M);
  return (PyObject *)M;
}

static PyObject *mpy_Matrix_sub(mpy_Matrix *M, mpy_Matrix *N)
{
  mpy_Matrix *result;
  
  result = mpy_Matrix_NEW();
  result->M = M->M - N->M;
  return (PyObject *)result;
}

static PyObject *mpy_Matrix_inplace_sub(mpy_Matrix *M, mpy_Matrix *N)
{  
  M->M -= N->M;
  Py_INCREF(M);
  return (PyObject *)M;
}

static PyObject *mpy_Matrix_mul(PyObject *M, PyObject *N)
{		
	PyObject *tmp_arg_as_py_double;
	mpy_Matrix *result;
	
	if (PyObject_TypeCheck(M, &mpy_MatrixType)){
		if (PyNumber_Check(N)){				
			tmp_arg_as_py_double = PyNumber_Float(N);
			if (tmp_arg_as_py_double != NULL){				
				double N_as_double = PyFloat_AsDouble(tmp_arg_as_py_double);				
				result = mpy_Matrix_NEW();				
				result->M = (((mpy_Matrix *)M)->M)*N_as_double;
				return (PyObject *)result;
			}
		}		
	}		
	else if (PyNumber_Check(M)){
		if (PyObject_TypeCheck(N, &mpy_MatrixType)){				
			tmp_arg_as_py_double = PyNumber_Float(M);
			if (tmp_arg_as_py_double != NULL){
				double M_as_double = PyFloat_AsDouble(tmp_arg_as_py_double);				
				result = mpy_Matrix_NEW();				
				result->M = (((mpy_Matrix *)N)->M)*M_as_double;
				return (PyObject *)result;
			}
		}		
	}
	
	Py_INCREF(Py_NotImplemented);
	return Py_NotImplemented;
}

static PyObject *mpy_Matrix_inplace_mul(PyObject *M, PyObject *N)
{		
	PyObject *tmp_arg_as_py_double;	
	
	if (PyObject_TypeCheck(M, &mpy_MatrixType)){		
		if (PyNumber_Check(N)){				
			tmp_arg_as_py_double = PyNumber_Float(N);
			if (tmp_arg_as_py_double != NULL){				
				double N_as_double = PyFloat_AsDouble(tmp_arg_as_py_double);
				((mpy_Matrix *)M)->M *= N_as_double;
				Py_INCREF(M);
				return M;
			}
		}		
	}		
	else if (PyNumber_Check(M)){
		if (PyObject_TypeCheck(N, &mpy_MatrixType)){				
			tmp_arg_as_py_double = PyNumber_Float(M);
			if (tmp_arg_as_py_double != NULL){
				double M_as_double = PyFloat_AsDouble(tmp_arg_as_py_double);
				((mpy_Matrix *)N)->M *= M_as_double;
				Py_INCREF(N);
				return N;
			}
		}		
	}
	
	Py_INCREF(Py_NotImplemented);
	return Py_NotImplemented;
}

static PyObject *mpy_Matrix_div(PyObject *M, PyObject *N)
{	
	PyObject *tmp_arg_as_py_double;
	mpy_Matrix *result;
	
	if (PyObject_TypeCheck(M, &mpy_MatrixType)){		
		if (PyNumber_Check(N)){				
			tmp_arg_as_py_double = PyNumber_Float(N);
			if (tmp_arg_as_py_double != NULL){				
				double N_as_double = PyFloat_AsDouble(tmp_arg_as_py_double);	
				if (N_as_double == 0){
					PyErr_SetString(PyExc_ZeroDivisionError, "Cannot divide Matrix object by zero");
					return NULL;	
				}			
				result = mpy_Matrix_NEW();				
				result->M = (((mpy_Matrix *)M)->M)/N_as_double;
				return (PyObject *)result;
			}
		}		
	}			
	
	Py_INCREF(Py_NotImplemented);
	return Py_NotImplemented;
}

static PyObject *mpy_Matrix_inplace_div(PyObject *M, PyObject *N)
{	
	PyObject *tmp_arg_as_py_double;
	mpy_Matrix *result;
	
	if (PyObject_TypeCheck(M, &mpy_MatrixType)){		
		if (PyNumber_Check(N)){				
			tmp_arg_as_py_double = PyNumber_Float(N);
			if (tmp_arg_as_py_double != NULL){				
				double N_as_double = PyFloat_AsDouble(tmp_arg_as_py_double);	
				if (N_as_double == 0){
					PyErr_SetString(PyExc_ZeroDivisionError, "Cannot divide Matrix object by zero");
					return NULL;	
				}		
				((mpy_Matrix *)M)->M /= N_as_double;
				Py_INCREF(M);													
				return M;
			}
		}		
	}			
	
	Py_INCREF(Py_NotImplemented);
	return Py_NotImplemented;
}

static PyObject *mpy_Matrix_negative(PyObject *M){
	mpy_Matrix *result;
		
	result = mpy_Matrix_NEW();				
	result->M = -((mpy_Matrix *)M)->M;																
	return (PyObject *)result;						
}

static PyNumberMethods mpy_Matrix_as_number = {
    (binaryfunc)mpy_Matrix_add, 		/* nb_add */
    (binaryfunc)mpy_Matrix_sub, 		/* nb_subtract */
    (binaryfunc)mpy_Matrix_mul, 		/* nb_multiply */	
    0,		/*  nb_remainder */
    0,		/*  nb_divmod */
    0,		/*  nb_power */
    (unaryfunc)mpy_Matrix_negative,		/*  nb_negative */
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
    
    (binaryfunc)mpy_Matrix_inplace_add,					/* nb_inplace_add */
    (binaryfunc)mpy_Matrix_inplace_sub,					/* nb_inplace_subtract */
    (binaryfunc)mpy_Matrix_inplace_mul,					/* nb_inplace_multiply*/
    (binaryfunc)mpy_Matrix_inplace_div,					/* nb_inplace_divide */
    0,		/*  nb_inplace_remainder */
    0,		/*  nb_inplace_power */
    0,		/*  nb_inplace_lshift */
    0,		/*  nb_inplace_rshift */
    0,		/*  nb_inplace_and */
    0,		/*  nb_inplace_xor */
    0,		/*  nb_inplace_or */
    
    (binaryfunc)mpy_Matrix_div,		/*  nb_floor_divide */
    (binaryfunc)mpy_Matrix_div,		/*  nb_true_divide */
    (binaryfunc)mpy_Matrix_inplace_div,		/*  nb_inplace_floor_divide */
    0,		/*  nb_inplace_true_divide */
    
    //0		/*  nb_index */
};



/*
    Method Table
                        */
PyMethodDef mpy_Matrix_methods[] = {
    {"transform", (PyCFunction)mpy_Matrix_transform, METH_VARARGS,
     ""
    },
    {"rightTransform", (PyCFunction)mpy_Matrix_rightTransform, METH_VARARGS,
     ""
    },
    {"det", (PyCFunction)mpy_Matrix_det, METH_NOARGS,
     ""
    },
    {"tr", (PyCFunction)mpy_Matrix_tr, METH_NOARGS,
     ""
    },
    {NULL}  /* Sentinel */
};



PyTypeObject mpy_MatrixType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "Core.Matrix",             /* tp_name */
    sizeof(mpy_Matrix),             /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)mpy_Matrix_dealloc, /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    &mpy_Matrix_repr,                         /* tp_repr */
    &mpy_Matrix_as_number,                         /* tp_as_number */
    &mpy_Matrix_as_sequence,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    (ternaryfunc) mpy_Matrix_call,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE,   /* tp_flags */
    "Three dimensional matrix",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    &mpy_Matrix_richcompare,              /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_Matrix_methods,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)mpy_Matrix_init,      /* tp_init */
    0,                         /* tp_alloc */
    mpy_Matrix_new,                 /* tp_new */
};

