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

#ifndef MPY_MANGOPY_FRAME
#define MPY_MANGOPY_FRAME

#include <mango/core/frame.h>
#include <mango/mangopy/mangopy_python.h>

#define VERIFY_FRAME_INITIALIZED(obj) if (!mpy_Frame_initialized((mpy_Frame *)obj)) return NULL

typedef struct mpy_Frame {
  PyObject_HEAD
  mpy_Frame *parentFrame;
  Mango::Core::Frame *internalObject;
} mpy_Frame;

extern PyTypeObject mpy_FrameType;
mpy_Frame *mpy_Frame_NEW();
int mpy_Frame_init(mpy_Frame *self, PyObject *args, PyObject *kw);
PyObject *mpy_Frame_parentFrame(mpy_Frame* self, PyObject *args);

extern mpy_Frame* PyGlobalFrame;

#endif // MPY_MANGOPY_FRAME 
