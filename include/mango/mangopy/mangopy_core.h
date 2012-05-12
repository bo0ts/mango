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


#ifndef MANGOPY_CORE
#define MANGOPY_CORE

#include <mango/mangopy/mangopy_python.h>
#include <mango/mangopy/mangopy_frame.h>
#include <mango/mango.h>

#define EVT_CORE 1
#define EVT_SCRIPTED 2
#define EVT_BOTH (EVT_CORE | EVT_SCRIPTED)


struct mpy_Object {
  PyObject_HEAD
  mpy_Frame* parentFrame;
  Mango::Core::Object *internalObject;
};


PyObject *pythonExceptionFromCException(Mango::Core::Error &e);
void throwCExceptionFromPythonException(const char *orig_object, const char *orig_method);
PyObject *mpy_addObjectToModule(PyObject *module, PyTypeObject *object, PyTypeObject *base_class, const char *name, bool force_generic_new = false);


#endif // MANGOPY_CORE
