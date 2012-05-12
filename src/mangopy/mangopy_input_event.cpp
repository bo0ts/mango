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

#include <mango/mangopy/mangopy_input_event.h>
#include <iostream>

/*
    Dealloc and New
                   	 */
    
void mpy_InputEvent_dealloc(mpy_InputEvent* self){    
  Py_TYPE(self)->tp_free((PyObject *)self);
}

PyObject *mpy_InputEvent_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  mpy_InputEvent *self;

  int event_source = -1;
  int event_type = -1;
  int event_code = -1;
  if (!PyArg_ParseTuple(args, "|iii", &event_source, &event_type, &event_code)){    
    return NULL;
  }    

  self = (mpy_InputEvent *)type->tp_alloc(type, 0);    
  self->source = event_source;
  self->type = event_type;
  self->code = event_code;
  return (PyObject *)self;
}

mpy_InputEvent *mpy_InputEvent_NEW(){
  mpy_InputEvent *object;
  object = PyObject_NEW(mpy_InputEvent, &mpy_InputEventType);
  return object;
}


/*
    Method Definitions
                        */
    
static PyObject *mpy_InputEvent_richcompare(PyObject *v, PyObject *w, int op){
  if (op == Py_EQ || op == Py_NE){
    PyObject *true_for_eq_false_for_ne = (op == Py_EQ ? Py_True : Py_False);
    PyObject *false_for_eq_true_for_ne = (op == Py_EQ ? Py_False : Py_True);		
    PyObject *tmp_arg_as_py_double;
    
    if (PyObject_TypeCheck(v, &mpy_InputEventType) && PyObject_TypeCheck(w, &mpy_InputEventType)){
      mpy_InputEvent *a = (mpy_InputEvent *)v;
      mpy_InputEvent *b = (mpy_InputEvent *)w;
      if (((a->source == b->source) || (a->source == -1) || (b->source == -1)) && 
	  ((a->type == b->type) || (a->type == -1) || (b->type == -1)) && 
	  ((a->code == b->code) || (a->code == -1) || (b->code == -1))){
	Py_INCREF(true_for_eq_false_for_ne);
	return true_for_eq_false_for_ne;
      } 
      else {
	Py_INCREF(false_for_eq_true_for_ne);
	return false_for_eq_true_for_ne; 
      }
    }
  }
    
  Py_INCREF(Py_NotImplemented);
  return Py_NotImplemented;
}

static PyObject *mpy_InputEvent_repr(PyObject *selff){
  char object_repr[50];
  mpy_InputEvent *self;
 
  self = reinterpret_cast<mpy_InputEvent *>(selff);
  
  const char *source;
  const char *type;
  const char *button;
  

  if (self->source == KEYBOARD){
    source = "keyboard";
  }
  else if (self->source == MOUSE){
    source = "mouse";
    if (self->code == BUTTON_LEFT){
      button = "left button";
    }
    else if (self->code == BUTTON_RIGHT){
      button = "right button";
    }
    else if (self->code == BUTTON_MIDDLE){
      button = "middle button";
    }
    else if (self->code == -1){
      button = "any button";
    }
    else{
      button = "unknown button";
    }
  }
  else if (self->source == -1){
    source = "any source";
  }
  else {
    source = "unkown source";
  }

  if (self->type == PRESS){
    if (self->source == MOUSE){
      type = "click";
    }
    else {
      type = "press";
    }
  }
  else if (self->type == RELEASE){
    type = "release";
  }
  else if (self->type == -1){
    type = "any type";
  }
  else{
    type = "unkown type";
  }

  if (self->source == MOUSE){
    sprintf(object_repr, "<Input event: %s %s %s>", source, type, button);
  }
  else if ((self->source == KEYBOARD) && (self->code == -1)){
    sprintf(object_repr, "<Input event: %s %s any code>", source, type);
  }
  else{
    sprintf(object_repr, "<Input event: %s %s %d>", source, type, self->code);
  }
  
  return PyUnicode_FromFormat("%s", object_repr);
}



/*
    Method Table
                        */
PyMethodDef mpy_InputEvent_methods[] = {
    {NULL}  /* Sentinel */
};


static PyMemberDef mpy_InputEvent_members[] = {
  {const_cast<char *>("source"), T_INT, offsetof(mpy_InputEvent, source), 0,
   const_cast<char *>("source of the event (KEYBOARD or MOUSE)")},
  {const_cast<char *>("type"), T_INT, offsetof(mpy_InputEvent, type), 0,
   const_cast<char *>("type of the event (PRESS, CLICK or RELEASE)")},
  {const_cast<char *>("code"), T_INT, offsetof(mpy_InputEvent, code), 0,
   const_cast<char *>("code of the event (e.g. BUTTON_LEFT for left mouse button or 97 for 'a')")},
  {NULL}  /* Sentinel */
};

PyTypeObject mpy_InputEventType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "Core.InputEvent",             /* tp_name */
    sizeof(mpy_InputEvent),             /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)mpy_InputEvent_dealloc, /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    &mpy_InputEvent_repr,                         /* tp_repr */
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
    "Input Event",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    &mpy_InputEvent_richcompare, /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    mpy_InputEvent_methods,             /* tp_methods */
    mpy_InputEvent_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,      /* tp_init */
    0,                         /* tp_alloc */
    mpy_InputEvent_new,                 /* tp_new */
};

