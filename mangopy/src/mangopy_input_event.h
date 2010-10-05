#include "Python.h"
#include "structmember.h"

#include "core/input.h" 
#include "core/constants.h" 

#ifndef MANGOPY_CORE_INPUTEVENT
#define MANGOPY_CORE_INPUTEVENT

/*
typedef struct mpy_InputEvent{
  PyObject_HEAD
  Mango::Core::inputEvent event;
} mpy_InputEvent;
*/

typedef struct mpy_InputEvent{
  PyObject_HEAD
  int source;
  int type;
  int code;
} mpy_InputEvent;

extern PyTypeObject mpy_InputEventType;

mpy_InputEvent *mpy_InputEvent_NEW();

#endif // MANGOPY_CORE_INPUTEVENT

