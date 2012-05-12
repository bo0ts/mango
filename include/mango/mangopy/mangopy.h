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
#include <mango/mangopy/mangopy_python.h>
#include <mango/mango.h>
#include <mango/mangopy/mangopy_vector.h>
#include <mango/mangopy/mangopy_core.h>
#include <mango/mangopy/mangopy_frame.h>
#include <mango/mangopy/mangopy_triangle.h>
#include <mango/mangopy/mangopy_camera.h>
#include <mango/mangopy/mangopy_keyboard.h>
#include <mango/mangopy/mangopy_matrix.h>
#include <mango/mangopy/mangopy_mouse.h>
#include <mango/mangopy/mangopy_input_event.h>
#include <mango/mangopy/mangopy_pyengine.h>
#include <mango/mangopy/mangopy_pyengine_wrapper.h>
#include <mango/mangopy/mangopy_opengl.h>
#include <mango/mangopy/mangopy_draw.h>
#include <mango/mangopy/mangopy_error.h>
#include <mango/mangopy/mangopy_core_module.h>
#include <sstream>
#ifndef WIN32
#include <libgen.h>
#endif

#ifndef MANGOPY
#define MANGOPY

namespace MangoPy{
  //// @cond
  PyObject *mpy_getVersion(PyObject *, PyObject* args);
  extern std::stringstream pythonScriptStderr;
  void printPythonScriptStderr();
  //// @endcond
  
  /**
   * Initialize Mangopy. This initializes Mango and Python and sets up
   * the scripted Mango environment. argc and argv are used to
   * initialize python, while setup_default_environment plays a similar
   * role as in Mango::initialize.
   */
  void initialize(int argc, char *argv[], bool setup_default_environment = true);

  /**
   * Finalize Mangopy. This calls the Python and Mango finalization routines.
   */
  void finalize();

  /**
   * Run a script from a file. If the second parameter is true, the
   * path is interpreted relative to the Mango binary. Otherwise the
   * path is interpreted relative to the current working directory.
   */
  void runScript(const char* fname, bool prepend_engine_path);

  //// @cond
  wchar_t *char2wchar(char *arg);
  char* check_cmd_op_presence(char **begin, char **end, const std::string &option);
  void python_home_path(char *exec_path, char *buffer, int buffer_size);
  void posix_cpy_dirname(const char *file_path, char *buffer);
  bool executable_path(char *buff, int buffer_size);
  //// @endcond

  /**
   * Initialize the module environment for a mangopy extension. Must be
   * called in the module initialization routine of every extension. See 
   * the documentation on extending mangopy for more information.
   */
  int initialize_module_environment();

  /**
   * Retreive the PyTypeObject of the Mango type with the given
   * identifier.  This should be used to describe inheritence of
   * Python types in mangopy extensions, see the documentation on
   * writing such extensions for more information.
   */
  PyTypeObject *py_type_object(const char *identifier);

  /**
   * Register a PyTypeObject with an identifier. Should be called in
   * the module initialization routines for all new Mango types
   * created in mangopy extensions. See the documentationo n writing
   * mangopy extensions for more information.
   */
  int register_py_type_object(const char *identifier, PyTypeObject *object_type);
} // MangoPy

#endif //MANGOPY
