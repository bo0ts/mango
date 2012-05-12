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
#include <mango/mangopy/mangopy_core.h>
#include <mango/mangopy/mangopy_frame.h>
#include <mango/mangopy/mangopy_triangle.h>
#include <mango/mangopy/mangopy_camera.h>
#include <mango/mangopy/mangopy_keyboard.h>
#include <mango/mangopy/mangopy_mouse.h>
#include <mango/mangopy/mangopy_input_event.h>
#include <mango/mangopy/mangopy_pyengine_wrapper.h>
#include <mango/mangopy/mangopy_matrix.h>


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
  PyModule_AddIntConstant(m, "STEP", STEP);
  PyModule_AddIntConstant(m, "RENDER", RENDER);
  PyModule_AddIntConstant(m, "DRAW", DRAW);
  PyModule_AddIntConstant(m, "INPUT", INPUT);
 
  // Add Camera Constants
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
