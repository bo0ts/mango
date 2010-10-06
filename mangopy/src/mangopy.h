#include "mangopy_python.h"
#include "mango.h"
#include "mangopy_vector.h"
#include "mangopy_core.h"
#include "mangopy_frame.h"
#include "mangopy_triangle.h"
#include "mangopy_camera.h"
#include "mangopy_keyboard.h"
#include "mangopy_mouse.h"
#include "mangopy_input_event.h"
#include "mangopy_pyengine.h" 
#include "mangopy_pyengine_wrapper.h"
#include "mangopy_opengl.h"
#include "mangopy_draw.h"
#include "mangopy_error.h"
#include "mangopy_core_module.h"

#ifndef MANGOPY
#define MANGOPY

namespace MangoPy{
  PyObject *mpy_getVersion(PyObject *, PyObject* args);
  void printPythonScriptStderr();
  
  void initialize(int argc, char *argv[], bool setup_default_environment = true);
  void finalize();
  void runScript(const char* fname, bool prepend_engine_path);
  wchar_t *char2wchar(char *arg);
} // MangoPy

#endif //MANGOPY
