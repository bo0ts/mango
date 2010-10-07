#include "mangopy_core.h"
#include "mangopy_frame.h"
#include "mangopy_triangle.h"
#include "mangopy_camera.h"
#include "mangopy_keyboard.h"
#include "mangopy_mouse.h"
#include "mangopy_input_event.h"
#include "mangopy_pyengine_wrapper.h"
#include "mangopy_matrix.h"

PyObject *mpy_addObjectToModule(PyObject *module, PyTypeObject *object, PyTypeObject *base_class, const char *name, bool force_generic_new){
  if (force_generic_new){
    object->tp_new = PyType_GenericNew;
  }
  if (base_class != NULL){
    object->tp_base = base_class;
  }
  if (PyType_Ready(object) < 0){
    return NULL;
  }
  Py_INCREF(object);
  PyModule_AddObject(module, name, (PyObject *)object);
  
}

PyMODINIT_FUNC
PyInit_Core(void){
  PyObject* m;
  
  m = PyModule_Create(&core_module_def);
  if (m == NULL){
    return NULL;
  }
  
  //mpy_addObjectToModule(m, &mpy_VectorType, NULL, "Vector", true);
  mpy_addObjectToModule(m, &mpy_VectorType, NULL, "Vector");
  mpy_addObjectToModule(m, &mpy_MatrixType, NULL, "Matrix");
  mpy_addObjectToModule(m, &mpy_FrameType, NULL, "Frame");
  mpy_addObjectToModule(m, &mpy_ObjectType, &mpy_FrameType, "Object");
  mpy_addObjectToModule(m, &mpy_TriangleType, &mpy_ObjectType, "Triangle");
  mpy_addObjectToModule(m, &mpy_CoreCameraType, &mpy_ObjectType, "CoreCamera");
  mpy_addObjectToModule(m, &mpy_CoreKeyboardType, NULL, "CoreKeyboard");
  mpy_addObjectToModule(m, &mpy_CoreMouseType, NULL, "CoreMouse");
  mpy_addObjectToModule(m, &mpy_InputEventType, NULL, "InputEvent");
  mpy_addObjectToModule(m, &mpy_PyEngineType, NULL, "PyEngine");

  // Add Event Constants
  PyModule_AddIntConstant(m, "PRE_STEP", PRE_STEP);
  PyModule_AddIntConstant(m, "STEP", STEP);
  PyModule_AddIntConstant(m, "POST_STEP", POST_STEP);
  PyModule_AddIntConstant(m, "RENDER", RENDER);
  PyModule_AddIntConstant(m, "DRAW", DRAW);
  PyModule_AddIntConstant(m, "INPUT", INPUT);
 
  // Add Camera Constants
  PyModule_AddIntConstant(m, "PRE_STEP", PRE_STEP);
  PyModule_AddIntConstant(m, "CAMERA_DEFAULT_MODE", CAMERA_DEFAULT_MODE);
  PyModule_AddIntConstant(m, "LOCK_PAN", LOCK_PAN);
  PyModule_AddIntConstant(m, "LOCK_DISTANCE", LOCK_DISTANCE);
  PyModule_AddIntConstant(m, "LOCK_ALPHA", LOCK_ALPHA);
  PyModule_AddIntConstant(m, "LOCK_BETA", LOCK_BETA);
  PyModule_AddIntConstant(m, "LOCK_GAMMA", LOCK_GAMMA);
  PyModule_AddIntConstant(m, "RMB_CYLINDRICAL_ROTATE", RMB_CYLINDRICAL_ROTATE);
  PyModule_AddIntConstant(m, "LMB_DRAG_FOCUS", LMB_DRAG_FOCUS);
  PyModule_AddIntConstant(m, "LOCK_POSITION", LOCK_POSITION);
  PyModule_AddIntConstant(m, "LOCK_ALL", LOCK_ALL);

  // Add Input Constants

  PyModule_AddIntConstant(m, "KEY_STATE_UP", KEY_STATE_UP);
  PyModule_AddIntConstant(m, "KEY_STATE_DOWN", KEY_STATE_DOWN);       

  PyModule_AddIntConstant(m, "KEYBOARD", KEYBOARD);       
  PyModule_AddIntConstant(m, "ANY", ANY);       
  PyModule_AddIntConstant(m, "MOUSE", MOUSE);       
  
  PyModule_AddIntConstant(m, "PRESS", PRESS);       
  PyModule_AddIntConstant(m, "CLICK", CLICK);       
  PyModule_AddIntConstant(m, "RELEASE", RELEASE);       

  PyModule_AddIntConstant(m, "BUTTON_STATE_UP", BUTTON_STATE_UP);   
  PyModule_AddIntConstant(m, "BUTTON_STATE_DOWN", BUTTON_STATE_DOWN);
  
  PyModule_AddIntConstant(m, "BUTTON_LEFT", BUTTON_LEFT);
  PyModule_AddIntConstant(m, "BUTTON_MIDDLE", BUTTON_MIDDLE);
  PyModule_AddIntConstant(m, "BUTTON_RIGHT", BUTTON_RIGHT);

  PyModule_AddIntConstant(m, "KEY_BACKSPACE", KEY_BACKSPACE);
  PyModule_AddIntConstant(m, "KEY_TAB", KEY_TAB);
  PyModule_AddIntConstant(m, "KEY_ENTER", KEY_ENTER);
  PyModule_AddIntConstant(m, "KEY_RETURN", KEY_RETURN);
  PyModule_AddIntConstant(m, "KEY_ESCAPE", KEY_ESCAPE);
  PyModule_AddIntConstant(m, "KEY_SPACE", KEY_SPACE);
  PyModule_AddIntConstant(m, "KEY_DELETE", KEY_DELETE);

  PyModule_AddIntConstant(m, "KEY_START", KEY_START);
  PyModule_AddIntConstant(m, "KEY_LBUTTON", KEY_LBUTTON);
  PyModule_AddIntConstant(m, "KEY_RBUTTON", KEY_RBUTTON);
  PyModule_AddIntConstant(m, "KEY_CANCEL", KEY_CANCEL);
  PyModule_AddIntConstant(m, "KEY_MBUTTON", KEY_MBUTTON);
  PyModule_AddIntConstant(m, "KEY_CLEAR", KEY_CLEAR);
  PyModule_AddIntConstant(m, "KEY_SHIFT", KEY_SHIFT);
  PyModule_AddIntConstant(m, "KEY_ALT", KEY_ALT);
  PyModule_AddIntConstant(m, "KEY_CONTROL", KEY_CONTROL);
  PyModule_AddIntConstant(m, "KEY_MENU", KEY_MENU);
  PyModule_AddIntConstant(m, "KEY_PAUSE", KEY_PAUSE);
  PyModule_AddIntConstant(m, "KEY_CAPITAL", KEY_CAPITAL);
  PyModule_AddIntConstant(m, "KEY_END", KEY_END);
  PyModule_AddIntConstant(m, "KEY_HOME", KEY_HOME);
  PyModule_AddIntConstant(m, "KEY_LEFT", KEY_LEFT);
  PyModule_AddIntConstant(m, "KEY_UP", KEY_UP);
  PyModule_AddIntConstant(m, "KEY_RIGHT", KEY_RIGHT);
  PyModule_AddIntConstant(m, "KEY_DOWN", KEY_DOWN);
  PyModule_AddIntConstant(m, "KEY_SELECT", KEY_SELECT);
  PyModule_AddIntConstant(m, "KEY_PRINT", KEY_PRINT);
  PyModule_AddIntConstant(m, "KEY_EXECUTE", KEY_EXECUTE);
  PyModule_AddIntConstant(m, "KEY_SNAPSHOT", KEY_SNAPSHOT);
  PyModule_AddIntConstant(m, "KEY_INSERT", KEY_INSERT);
  PyModule_AddIntConstant(m, "KEY_HELP", KEY_HELP);
  PyModule_AddIntConstant(m, "KEY_NUMPAD0", KEY_NUMPAD0);
  PyModule_AddIntConstant(m, "KEY_NUMPAD1", KEY_NUMPAD1);
  PyModule_AddIntConstant(m, "KEY_NUMPAD2", KEY_NUMPAD2);
  PyModule_AddIntConstant(m, "KEY_NUMPAD3", KEY_NUMPAD3);
  PyModule_AddIntConstant(m, "KEY_NUMPAD4", KEY_NUMPAD4);
  PyModule_AddIntConstant(m, "KEY_NUMPAD5", KEY_NUMPAD5);
  PyModule_AddIntConstant(m, "KEY_NUMPAD6", KEY_NUMPAD6);
  PyModule_AddIntConstant(m, "KEY_NUMPAD7", KEY_NUMPAD7);
  PyModule_AddIntConstant(m, "KEY_NUMPAD8", KEY_NUMPAD8);
  PyModule_AddIntConstant(m, "KEY_NUMPAD9", KEY_NUMPAD9);
  PyModule_AddIntConstant(m, "KEY_MULTIPLY", KEY_MULTIPLY);
  PyModule_AddIntConstant(m, "KEY_ADD", KEY_ADD);
  PyModule_AddIntConstant(m, "KEY_SEPARATOR", KEY_SEPARATOR);
  PyModule_AddIntConstant(m, "KEY_SUBTRACT", KEY_SUBTRACT);
  PyModule_AddIntConstant(m, "KEY_DECIMAL", KEY_DECIMAL);
  PyModule_AddIntConstant(m, "KEY_DIVIDE", KEY_DIVIDE);
  PyModule_AddIntConstant(m, "KEY_F1", KEY_F1);
  PyModule_AddIntConstant(m, "KEY_F2", KEY_F2);
  PyModule_AddIntConstant(m, "KEY_F3", KEY_F3);
  PyModule_AddIntConstant(m, "KEY_F4", KEY_F4);
  PyModule_AddIntConstant(m, "KEY_F5", KEY_F5);
  PyModule_AddIntConstant(m, "KEY_F6", KEY_F6);
  PyModule_AddIntConstant(m, "KEY_F7", KEY_F7);
  PyModule_AddIntConstant(m, "KEY_F8", KEY_F8);
  PyModule_AddIntConstant(m, "KEY_F9", KEY_F9);
  PyModule_AddIntConstant(m, "KEY_F10", KEY_F10);
  PyModule_AddIntConstant(m, "KEY_F11", KEY_F11);
  PyModule_AddIntConstant(m, "KEY_F12", KEY_F12);
  PyModule_AddIntConstant(m, "KEY_F13", KEY_F13);
  PyModule_AddIntConstant(m, "KEY_F14", KEY_F14);
  PyModule_AddIntConstant(m, "KEY_F15", KEY_F15);
  PyModule_AddIntConstant(m, "KEY_F16", KEY_F16);
  PyModule_AddIntConstant(m, "KEY_F17", KEY_F17);
  PyModule_AddIntConstant(m, "KEY_F18", KEY_F18);
  PyModule_AddIntConstant(m, "KEY_F19", KEY_F19);
  PyModule_AddIntConstant(m, "KEY_F20", KEY_F20);
  PyModule_AddIntConstant(m, "KEY_F21", KEY_F21);
  PyModule_AddIntConstant(m, "KEY_F22", KEY_F22);
  PyModule_AddIntConstant(m, "KEY_F23", KEY_F23);
  PyModule_AddIntConstant(m, "KEY_F24", KEY_F24);
  PyModule_AddIntConstant(m, "KEY_NUMLOCK", KEY_NUMLOCK);
  PyModule_AddIntConstant(m, "KEY_SCROLL", KEY_SCROLL);
  PyModule_AddIntConstant(m, "KEY_PAGEUP", KEY_PAGEUP);
  PyModule_AddIntConstant(m, "KEY_PAGEDOWN", KEY_PAGEDOWN);
  
  PyModule_AddIntConstant(m, "KEY_NUMPAD_SPACE", KEY_NUMPAD_SPACE);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_TAB", KEY_NUMPAD_TAB);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_ENTER", KEY_NUMPAD_ENTER);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_F1", KEY_NUMPAD_F1);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_F2", KEY_NUMPAD_F2);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_F3", KEY_NUMPAD_F3);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_F4", KEY_NUMPAD_F4);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_HOME", KEY_NUMPAD_HOME);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_LEFT", KEY_NUMPAD_LEFT);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_UP", KEY_NUMPAD_UP);    
  PyModule_AddIntConstant(m, "KEY_NUMPAD_RIGHT", KEY_NUMPAD_RIGHT);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_DOWN", KEY_NUMPAD_DOWN);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_PAGEUP", KEY_NUMPAD_PAGEUP);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_PAGEDOWN", KEY_NUMPAD_PAGEDOWN);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_END", KEY_NUMPAD_END);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_BEGIN", KEY_NUMPAD_BEGIN);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_INSERT", KEY_NUMPAD_INSERT);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_DELETE", KEY_NUMPAD_DELETE);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_EQUAL", KEY_NUMPAD_EQUAL);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_MULTIPLY", KEY_NUMPAD_MULTIPLY);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_ADD", KEY_NUMPAD_ADD);   
  PyModule_AddIntConstant(m, "KEY_NUMPAD_SEPARATOR", KEY_NUMPAD_SEPARATOR);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_SUBTRACT", KEY_NUMPAD_SUBTRACT);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_DECIMAL", KEY_NUMPAD_DECIMAL);
  PyModule_AddIntConstant(m, "KEY_NUMPAD_DIVIDE", KEY_NUMPAD_DIVIDE);
						      
  PyModule_AddIntConstant(m, "KEY_WINDOWS_LEFT", KEY_WINDOWS_LEFT);
  PyModule_AddIntConstant(m, "KEY_WINDOWS_RIGHT", KEY_WINDOWS_RIGHT);
  PyModule_AddIntConstant(m, "KEY_WINDOWS_MENU", KEY_WINDOWS_MENU);

  return m;
}

PyObject *pythonExceptionFromCException(Mango::Core::Error &e){
  const char *errorType = e.objectType();
  PyObject *exceptionToThrow = PyExc_RuntimeError;
  if (strcmp(errorType, "ValueError") == 0){
    exceptionToThrow = PyExc_ValueError;
  }
  PyErr_SetString(exceptionToThrow, e.FullMessage());
  return NULL;
}


/*
  Dealloc and New
*/
    

void mpy_Object_dealloc(mpy_Object *self)
{
  delete self->internalObject;
  Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject *mpy_Object_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  mpy_Object *self;

  //std::cout << "Creating a new object with type" << type <<  std::endl;
  self = (mpy_Object *)(type->tp_alloc(type, 0));    
  //std::cout << "Created python object" << std::endl;

  if (self != NULL) {        
    self->internalObject = new Mango::Core::Object();
    if (self->internalObject == NULL){
      Py_DECREF(self);
      PyErr_SetString(PyExc_RuntimeError, "MangoPy Runtime: Failed to create an object of type Mango::Core::Object");
      return NULL;
    }	
    self->parentFrame = NULL;
  }    

  //std::cout << "Created new mpy_Object at" << self << ", with internal Core::Object at " << self->internalObject << std::endl;
  return (PyObject *)self;
}

int mpy_Object_init(mpy_Object *self, PyObject *args, PyObject *kw){
  mpy_Frame_init((mpy_Frame *)self, NULL, NULL);
  return 0;
}

/*
  Visibility
*/
    
    
PyObject *mpy_Object_toggleVisibility(mpy_Object *self){
  // Call Function
  try{        
    self->internalObject->toggleVisibility();
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *mpy_Object_setVisible(mpy_Object *self, PyObject* args){
  // Call Parameters
  bool should_be_visible;
  PyObject *py_should_be_visible;

  // Parse arguments
  if (!PyArg_ParseTuple(args, "O", &py_should_be_visible) || !PyBool_Check(py_should_be_visible)){
    PyErr_SetString(PyExc_TypeError, "Expected True or False");
    return NULL;
  }

  // Call Function
  try{
    should_be_visible = (PyObject_IsTrue(py_should_be_visible) == 1);
    self->internalObject->setVisible(should_be_visible);
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}


PyObject *mpy_Object_visible(mpy_Object *self){
  // Function Return Values
  bool is_visible;

  // Parse arguments

  // Call Function
  try{
    is_visible = self->internalObject->visible();
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  if (is_visible){
    Py_INCREF(Py_True);
    return Py_True;
  }
  else{
    Py_INCREF(Py_False);
    return Py_False;
  }
}


static PyObject *mpy_Object_set(mpy_Object *self, PyObject *args){
  // Function Call Parameters
  int event_mask;  

  // Function Return Values

  // Convert arguments
  if(!PyArg_ParseTuple(args, "i", &event_mask)){
    return NULL;
  } 
  
  // Call Function
  int j = 1; // j is the event_type, corresponds to constants defined in constants.h

  try{ 
    for (int i = 0; i < ENGINE_MAX_EVENT_TYPES; i += 1){                
      if ((event_mask & j) == j){
	const char *event_method_name = static_cast<PyEngine *>(Mango::Engine)->getObjectEventMethodName(i);
	
	PyObject *instance_method = PyObject_GetAttrString(reinterpret_cast<PyObject *>(self), event_method_name);
	if (instance_method == NULL){
	  return NULL;
	}
	
	PyObject *instance_method_func = PyObject_GetAttrString(instance_method, "__func__");
	if (!PyErr_Occurred() && (instance_method_func != NULL)){
	  reinterpret_cast<PyEngine *>(Mango::Engine)->setScriptedEvent(self, j);
	}
	else if (PyErr_Occurred() && PyErr_ExceptionMatches(PyExc_AttributeError) && (instance_method_func == NULL)){
	  Mango::Engine->setEvent(self->internalObject, j);
	  PyErr_Clear();
	}
	else{
	  return NULL;
	}		
      }
      j = j << 1;
    }      
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
    
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *mpy_Object_unset(mpy_Object *self, PyObject *args){
  // Function Call Parameters
  int event_mask;
  int event_type_mask = EVT_BOTH;

  // Function Return Values

  // Convert arguments
  if(!PyArg_ParseTuple(args, "i|i", &event_mask, &event_type_mask)){
    return NULL;
  }

  try{
    // Unset core event if the flag was set
    if ((event_type_mask & EVT_CORE) != 0){
      Mango::Engine->removeEvent(self->internalObject, event_mask);
    }
    if ((event_type_mask & EVT_SCRIPTED) != 0){
      reinterpret_cast<PyEngine *>(Mango::Engine)->removeScriptedEvent(self, event_mask);
    }
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *mpy_Object_toggle(mpy_Object *self, PyObject *args){
  // Function Call Parameters
  int event_mask;
  int event_type_mask = EVT_BOTH;

  // Function Return Values

  // Convert arguments
  if(!PyArg_ParseTuple(args, "i|i", &event_mask, &event_type_mask)){
    return NULL;
  }

  try{
    // Unset core event if the flag was set
    if ((event_type_mask & EVT_CORE) != 0){
      Mango::Engine->toggleEvent(self->internalObject, event_mask);
    }
    if ((event_type_mask & EVT_SCRIPTED) != 0){
      reinterpret_cast<PyEngine *>(Mango::Engine)->toggleScriptedEvent(self, event_mask);
    }
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *mpy_Object_executes(mpy_Object *self, PyObject *args){
  // Function Call Parameters
  int event_mask;
  int event_type_mask = EVT_BOTH;
    
  // Function Return Values
  bool executes_core = false;
  bool executes_scripted = false;

  // Convert arguments
  if(!PyArg_ParseTuple(args, "i|i", &event_mask, &event_type_mask)){
    return NULL;
  }

  try{
    // Unset core event if the flag was set
    if ((event_type_mask & EVT_CORE) != 0){
      executes_core = Mango::Engine->objectHasEvent(self->internalObject, event_mask);
    }
    if ((event_type_mask & EVT_SCRIPTED) != 0){
      executes_scripted = reinterpret_cast<PyEngine *>(Mango::Engine)->objectHasScriptedEvent(self, event_mask);
    }
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
    
  PyObject *truth_to_return;        
  if (((event_type_mask & EVT_CORE) != 0) && ((event_type_mask & EVT_SCRIPTED) != 0)){
    if (executes_core && executes_scripted){
      truth_to_return = Py_True;
    }
    else{
      truth_to_return = Py_False;
    }
  }
  else if ((event_type_mask & EVT_CORE) != 0){
    if (executes_core){
      truth_to_return = Py_True;
    }
    else{
      truth_to_return = Py_False;
    }                       
  }
  else if ((event_type_mask & EVT_SCRIPTED) != 0){
    if (executes_scripted){
      truth_to_return = Py_True;
    }
    else{
      truth_to_return = Py_False;
    }                       
  }
  else{
    PyErr_SetString(PyExc_RuntimeError, "Object.executes called with bad event type mask");   
    return NULL;
  }
    
  Py_INCREF(truth_to_return);
  return truth_to_return;
}



/*
  Object Events
*/
static PyObject *mpy_Object_pre_step(mpy_Object *self){
  try{
    self->internalObject->pre_step();
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *mpy_Object_step(mpy_Object *self){
  try{
    self->internalObject->step();
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *mpy_Object_post_step(mpy_Object *self){
  try{
    self->internalObject->post_step();
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *mpy_Object_render(mpy_Object *self){
  try{
    self->internalObject->render();
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *mpy_Object_draw(mpy_Object *self){
  try{
    self->internalObject->draw();
  }
  catch (Mango::Core::Error &e){
    return pythonExceptionFromCException(e);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *mpy_Object_input(mpy_Object *self, PyObject *args){
  // Call Parameters
  mpy_InputEvent *py_event;
  Mango::Core::inputEvent event;

  // Parse arguments
  if (!PyArg_ParseTuple(args, "O!", &mpy_InputEventType, &py_event)){
    return NULL;
  }
  event.source = py_event->source;
  event.type = py_event->type;
  event.code = py_event->code;
  
  // Call Function
  try{   
    self->internalObject->input(event);
  }
  catch (Mango::Core::Error &e){
    // An error occured, raise an appropriate Python exception and return NULL
    return pythonExceptionFromCException(e);
  }

  // Return result
  Py_INCREF(Py_None);
  return Py_None;
}



/*
  Method Definitions
*/
PyObject *mpy_Object_objectType(mpy_Object *self)
{
  PyObject *result;
  result = PyUnicode_FromString(static_cast<Mango::Core::Object *>(self->internalObject)->objectType());
  return result;
}


static PyObject *mpy_Object_repr(PyObject *selff){
  char object_repr[50];
  mpy_Object *self;

  //std::cout << "Representing object at " << selff << std::endl;
  self = reinterpret_cast<mpy_Object *>(selff);
  sprintf(object_repr, "<%s #%d>", self->internalObject->objectType(), self->internalObject->objectID());
  //sprintf(object_repr, "Some Object");
  //std::cout << "Done representing object at " << selff << std::endl;
  return PyUnicode_FromString(object_repr);
  //return PyUnicode_FromString("An Object");
}












/*
  Method Table
*/
PyMethodDef mpy_Object_methods[] = {
  {"objectType", (PyCFunction)mpy_Object_objectType, METH_NOARGS,
   "Return a string representing the object's type"
  },

  {"set", (PyCFunction)mpy_Object_set, METH_VARARGS,
   "Set an event for the object"
  },
  {"unset", (PyCFunction)mpy_Object_unset, METH_VARARGS,
   "Remove an event for the object"
  },
  {"toggle", (PyCFunction)mpy_Object_toggle, METH_VARARGS,
   "Toggle the execution of an event for the object"
  },
  {"executes", (PyCFunction)mpy_Object_executes, METH_VARARGS,
   "Check if the object executes a given event"
  },

    
  // Visibility
  {"toggleVisibility", (PyCFunction)mpy_Object_toggleVisibility, METH_NOARGS,
   "Toggle of the visibility of an object"
  },    
  {"setVisible", (PyCFunction)mpy_Object_setVisible, METH_VARARGS,
   "set the object visibility property"
  },
  {"visible", (PyCFunction)mpy_Object_visible, METH_NOARGS,
   "Returns true if the object is visible, false otherwise"
  },
    
  // Events
  {"pre_step", (PyCFunction)mpy_Object_pre_step, METH_VARARGS,
   "Object pre-step event"
  },
  {"step", (PyCFunction)mpy_Object_step, METH_VARARGS,
   "Object step event"
  },
  {"post_step", (PyCFunction)mpy_Object_post_step, METH_VARARGS,
   "Object post-step event"
  },
  {"render", (PyCFunction)mpy_Object_render, METH_VARARGS,
   "Object render event"
  },
  {"draw", (PyCFunction)mpy_Object_draw, METH_VARARGS,
   "Object draw event"
  },
  {"input", (PyCFunction)mpy_Object_input, METH_VARARGS,
   "Object input event"
  },

  {NULL}  /* Sentinel */
};



PyTypeObject mpy_ObjectType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "Core.Object",             /* tp_name */
  sizeof(mpy_Object),             /* tp_basicsize */
  0,                         /* tp_itemsize */
  (destructor)mpy_Object_dealloc, /* tp_dealloc */
  0,                         /* tp_print */
  0,                         /* tp_getattr */
  0,                         /* tp_setattr */
  0,                         /* tp_reserved */
  &mpy_Object_repr,                         /* tp_repr */
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
  "Core Mango object",           /* tp_doc */
  0,		               /* tp_traverse */
  0,		               /* tp_clear */
  0,              /* tp_richcompare */
  0,		               /* tp_weaklistoffset */
  0,		               /* tp_iter */
  0,		               /* tp_iternext */
  mpy_Object_methods,             /* tp_methods */
  0,             /* tp_members */
  0,                         /* tp_getset */
  0,                         /* tp_base */
  0,                         /* tp_dict */
  0,                         /* tp_descr_get */
  0,                         /* tp_descr_set */
  0,                         /* tp_dictoffset */
  (initproc)mpy_Object_init,      /* tp_init */
  0,                         /* tp_alloc */
  mpy_Object_new,                 /* tp_new */
};

