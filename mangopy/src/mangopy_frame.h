#include "Python.h"
#include "structmember.h"
#include "mangopy_core.h"

#ifndef MPY_MANGOPY_FRAME
#define MPY_MANGOPY_FRAME

#define VERIFY_FRAME_INITIALIZED(obj) if (!mpy_Frame_initialized((mpy_Frame *)obj)) return NULL

typedef struct mpy_Frame{
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
