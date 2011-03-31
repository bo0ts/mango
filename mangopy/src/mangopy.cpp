#include "mangopy.h"
#include <locale.h>


namespace MangoPy{ 
    
  std::stringstream pythonScriptStderr(std::stringstream::in | std::stringstream::out);

  static void mpy_trivialDelMethod(void *ptr)
  {
    return;
  }

  PyObject *mpy_writeToPythonScriptStderr(PyObject *, PyObject* args){
    // Function Call Parameters
    char *err_msg;

    // Convert arguments
    if(!PyArg_ParseTuple(args, "s", &err_msg)){
      return NULL;
    }

    // Call the function and return the result
    pythonScriptStderr << err_msg;
    Py_INCREF(Py_None);
    return Py_BuildValue("O", Py_None);
  }

  
  void printPythonScriptStderr(){
    pythonScriptStderr.clear();
    std::cerr << pythonScriptStderr.str();
  }
  
  
  PyObject *mpy_getVersion(PyObject *, PyObject* args){
    return Py_BuildValue("s", "Mango: 0.1\nMangoPy: 0.1");
  }

  static PyMethodDef MangoPyGeneralMethods[] = {
    {"getVersion",  mpy_getVersion, METH_VARARGS,
     "Return the version of Mango and MangoPy"},
    {"writeToPythonScriptStderr", mpy_writeToPythonScriptStderr, METH_VARARGS,
     "write a string to the python error buffer"},   
    {NULL, NULL, 0, NULL}        /* Sentinel */
  };
  
  static PyModuleDef _mpygen_def = {
    PyModuleDef_HEAD_INIT,
    "_mpygen",
    "Example module that creates an extension type.",
    -1,
    MangoPyGeneralMethods, 
    NULL, NULL, NULL, NULL
  };
  
  
  PyMODINIT_FUNC PyInit__mpygen(void){			
    PyObject *m;
    
    m = PyModule_Create(&_mpygen_def);
    if (m == NULL){
      return NULL;
    }
    
    return m;
  }
  

  int register_py_type_object(const char *identifier, PyTypeObject *object_type){
    PyObject *mpygen_module = PyImport_AddModule("_mpygen");
    if (mpygen_module == NULL){
      PyErr_SetString(PyExc_RuntimeError, "module '_mpygen' does not exist");
      return NULL;
    }

    PyObject *types = PyObject_GetAttrString(mpygen_module, "TYPES");
    if (types == NULL){
      return NULL;
    }

    PyDict_SetItemString(types, identifier, PyCObject_FromVoidPtr((void *)object_type, mpy_trivialDelMethod));
    return 0;
  }

  PyTypeObject *py_type_object(const char *identifier){
    PyObject *mpygen_module = PyImport_AddModule("_mpygen");
    if (mpygen_module == NULL){
      PyErr_SetString(PyExc_RuntimeError, "module '_mpygen' does not exist");
      return NULL;
    }

    PyObject *types = PyObject_GetAttrString(mpygen_module, "TYPES");
    if (types == NULL){
      return NULL;
    }

    PyObject *py_object_type = PyDict_GetItemString(types, "mangopy.core.object");
    if (py_object_type == NULL){
      return NULL;
    }

    PyTypeObject *dynamic_mpy_type = (PyTypeObject *)PyCObject_AsVoidPtr(py_object_type);
    return dynamic_mpy_type;
  }

  
  void initialize(int argc, char *argv[], bool setup_default_environment){
    wchar_t **argv_copy;
    
    argv_copy = (wchar_t **)PyMem_Malloc(sizeof(wchar_t*)*argc);
    for (int i = 0; i < argc - 1; i++) {
      argv_copy[i] = char2wchar(argv[i + 1]);
      // todo: handle the case where argv_copy is NULL
    }

    Mango::initialize(false);

    if (setup_default_environment) {      
      Mango::GlobalFrame = new Mango::Core::Frame(true);
      Mango::Engine = new PyEngine();
      Mango::Keyboard = new Mango::Core::CoreKeyboard();
      Mango::Mouse = new Mango::Core::CoreMouse();
      Mango::Camera = new Mango::Core::CoreCamera();
      Mango::View = new Mango::Core::CoreCamera();      
      
      Mango::Camera->set(STEP);
      Mango::Camera->lookAt(Mango::Vector(0, 0, 0), 5);
      
      Mango::View->set(STEP);
      Mango::View->setMode(RMB_CYLINDRICAL_ROTATE | LMB_DRAG_FOCUS | ZOOM_SCALES);

      Mango::Engine->setCameraObject(Mango::Camera);
      Mango::Engine->setViewObject(Mango::View);
    }


    // Add modules - phase one
    PyImport_AppendInittab("_mpygen", PyInit__mpygen);
    PyImport_AppendInittab("Core", PyInit_Core);
    PyImport_AppendInittab("OpenGL", PyInit_OpenGL);
    PyImport_AppendInittab("Draw", PyInit_Draw);
    
    // Initialize Python    
    Py_Initialize();
    PySys_SetArgv(argc - 1, argv_copy);
    
    // Add modules - phase two
    PyObject* main_module = PyImport_AddModule("__main__");    
    PyObject *module_mpygen = PyImport_ImportModule("_mpygen");	
    Py_INCREF(module_mpygen);
    PyModule_AddObject(main_module, "_mpygen", module_mpygen);

    if (module_mpygen == NULL){
      std::cout << "MangoPy: Error creating module _mpygen" << std::endl;	
      exit(1);
    }
    
    PyObject *module_core = PyImport_ImportModule("Core");	
    Py_INCREF(module_core);
    PyModule_AddObject(main_module, "Core", module_core);
    
    if (module_core == NULL){
      std::cout << "MangoPy: Error creating module Core" << std::endl;	
      exit(1);
    }
    
    PyObject *module_opengl = PyImport_ImportModule("OpenGL");	
    Py_INCREF(module_opengl);
    PyModule_AddObject(main_module, "OpenGL", module_opengl);
    
    if (module_opengl == NULL){
      std::cout << "MangoPy: Error creating module OpenGL" << std::endl;	
      exit(1);
    }

    PyObject *module_draw = PyImport_ImportModule("Draw");	
    Py_INCREF(module_draw);
    PyModule_AddObject(main_module, "Draw", module_draw);
    
    if (module_draw == NULL){
      std::cout << "MangoPy: Error creating module Draw" << std::endl;	
      exit(1);
    }
    
    // Add absolute path to engine to the module search path
    PyModule_AddStringConstant(module_core, "MANGO_RELATIVE_EXECUTABLE_NAME", argv[0]);
    PyRun_SimpleString("import os; Core.MANGO_ABSOLUTE_PATH = os.path.dirname(os.path.normpath(os.path.join(os.getcwd(), Core.MANGO_RELATIVE_EXECUTABLE_NAME)))");
    PyRun_SimpleString("import sys; sys.path.append(Core.MANGO_ABSOLUTE_PATH)");        

    // Make the Core module globally available
    PyRun_SimpleString("__builtins__._mpygen = _mpygen");
    PyRun_SimpleString("__builtins__.Core = Core");
    PyRun_SimpleString("__builtins__.Draw = Draw");
    PyRun_SimpleString("__builtins__.OpenGL = OpenGL");
    PyRun_SimpleString("__builtins__.Vector = Core.Vector");
    PyRun_SimpleString("__builtins__.PRE_STEP = Core.PRE_STEP");
    PyRun_SimpleString("__builtins__.STEP = Core.STEP");
    PyRun_SimpleString("__builtins__.POST_STEP = Core.POST_STEP");
    PyRun_SimpleString("__builtins__.RENDER = Core.RENDER");
    PyRun_SimpleString("__builtins__.DRAW = Core.DRAW");
    PyRun_SimpleString("__builtins__.INPUT = Core.INPUT");
    
    PyRun_SimpleString("__builtins__.CAMERA_DEFAULT_MODE = Core.CAMERA_DEFAULT_MODE");
    PyRun_SimpleString("__builtins__.LOCK_PAN = Core.LOCK_PAN");
    PyRun_SimpleString("__builtins__.LOCK_DISTANCE = Core.LOCK_DISTANCE");
    PyRun_SimpleString("__builtins__.LOCK_ALPHA = Core.LOCK_ALPHA");
    PyRun_SimpleString("__builtins__.LOCK_BETA = Core.LOCK_BETA");
    PyRun_SimpleString("__builtins__.LOCK_GAMMA = Core.LOCK_GAMMA");
    PyRun_SimpleString("__builtins__.RMB_CYLINDRICAL_ROTATE  = Core.RMB_CYLINDRICAL_ROTATE");
    PyRun_SimpleString("__builtins__.LMB_DRAG_FOCUS = Core.LMB_DRAG_FOCUS");
    PyRun_SimpleString("__builtins__.LOCK_ALL = Core.LOCK_ALL");
    
    PyRun_SimpleString("__builtins__.KEY_WINDOWS_MENU = Core.KEY_WINDOWS_MENU");
    PyRun_SimpleString("__builtins__.KEY_WINDOWS_RIGHT = Core.KEY_WINDOWS_RIGHT");
    PyRun_SimpleString("__builtins__.KEY_WINDOWS_LEFT = Core.KEY_WINDOWS_LEFT");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_DIVIDE = Core.KEY_NUMPAD_DIVIDE");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_DECIMAL = Core.KEY_NUMPAD_DECIMAL");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_SUBTRACT = Core.KEY_NUMPAD_SUBTRACT");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_SEPARATOR = Core.KEY_NUMPAD_SEPARATOR");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_ADD = Core.KEY_NUMPAD_ADD");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_MULTIPLY = Core.KEY_NUMPAD_MULTIPLY");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_EQUAL = Core.KEY_NUMPAD_EQUAL");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_DELETE = Core.KEY_NUMPAD_DELETE");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_INSERT = Core.KEY_NUMPAD_INSERT");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_BEGIN = Core.KEY_NUMPAD_BEGIN");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_END = Core.KEY_NUMPAD_END");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_PAGEDOWN = Core.KEY_NUMPAD_PAGEDOWN");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_PAGEUP = Core.KEY_NUMPAD_PAGEUP");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_DOWN = Core.KEY_NUMPAD_DOWN");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_RIGHT = Core.KEY_NUMPAD_RIGHT");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_UP = Core.KEY_NUMPAD_UP");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_LEFT = Core.KEY_NUMPAD_LEFT");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_HOME = Core.KEY_NUMPAD_HOME");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_F4 = Core.KEY_NUMPAD_F4");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_F3 = Core.KEY_NUMPAD_F3");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_F2 = Core.KEY_NUMPAD_F2");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_F1 = Core.KEY_NUMPAD_F1");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_ENTER = Core.KEY_NUMPAD_ENTER");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_TAB = Core.KEY_NUMPAD_TAB");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD_SPACE = Core.KEY_NUMPAD_SPACE");
    PyRun_SimpleString("__builtins__.KEY_PAGEDOWN = Core.KEY_PAGEDOWN");
    PyRun_SimpleString("__builtins__.KEY_PAGEUP = Core.KEY_PAGEUP");
    PyRun_SimpleString("__builtins__.KEY_SCROLL = Core.KEY_SCROLL");
    PyRun_SimpleString("__builtins__.KEY_NUMLOCK = Core.KEY_NUMLOCK");
    PyRun_SimpleString("__builtins__.KEY_F24 = Core.KEY_F24");
    PyRun_SimpleString("__builtins__.KEY_F23 = Core.KEY_F23");
    PyRun_SimpleString("__builtins__.KEY_F22 = Core.KEY_F22");
    PyRun_SimpleString("__builtins__.KEY_F21 = Core.KEY_F21");
    PyRun_SimpleString("__builtins__.KEY_F20 = Core.KEY_F20");
    PyRun_SimpleString("__builtins__.KEY_F19 = Core.KEY_F19");
    PyRun_SimpleString("__builtins__.KEY_F18 = Core.KEY_F18");
    PyRun_SimpleString("__builtins__.KEY_F17 = Core.KEY_F17");
    PyRun_SimpleString("__builtins__.KEY_F16 = Core.KEY_F16");
    PyRun_SimpleString("__builtins__.KEY_F15 = Core.KEY_F15");
    PyRun_SimpleString("__builtins__.KEY_F14 = Core.KEY_F14");
    PyRun_SimpleString("__builtins__.KEY_F13 = Core.KEY_F13");
    PyRun_SimpleString("__builtins__.KEY_F12 = Core.KEY_F12");
    PyRun_SimpleString("__builtins__.KEY_F11 = Core.KEY_F11");
    PyRun_SimpleString("__builtins__.KEY_F10 = Core.KEY_F10");
    PyRun_SimpleString("__builtins__.KEY_F9 = Core.KEY_F9");
    PyRun_SimpleString("__builtins__.KEY_F8 = Core.KEY_F8");
    PyRun_SimpleString("__builtins__.KEY_F7 = Core.KEY_F7");
    PyRun_SimpleString("__builtins__.KEY_F6 = Core.KEY_F6");
    PyRun_SimpleString("__builtins__.KEY_F5 = Core.KEY_F5");
    PyRun_SimpleString("__builtins__.KEY_F4 = Core.KEY_F4");
    PyRun_SimpleString("__builtins__.KEY_F3 = Core.KEY_F3");
    PyRun_SimpleString("__builtins__.KEY_F2 = Core.KEY_F2");
    PyRun_SimpleString("__builtins__.KEY_F1 = Core.KEY_F1");
    PyRun_SimpleString("__builtins__.KEY_DIVIDE = Core.KEY_DIVIDE");
    PyRun_SimpleString("__builtins__.KEY_DECIMAL = Core.KEY_DECIMAL");
    PyRun_SimpleString("__builtins__.KEY_SUBTRACT = Core.KEY_SUBTRACT");
    PyRun_SimpleString("__builtins__.KEY_SEPARATOR = Core.KEY_SEPARATOR");
    PyRun_SimpleString("__builtins__.KEY_ADD = Core.KEY_ADD");
    PyRun_SimpleString("__builtins__.KEY_MULTIPLY = Core.KEY_MULTIPLY");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD9 = Core.KEY_NUMPAD9");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD8 = Core.KEY_NUMPAD8");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD7 = Core.KEY_NUMPAD7");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD6 = Core.KEY_NUMPAD6");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD5 = Core.KEY_NUMPAD5");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD4 = Core.KEY_NUMPAD4");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD3 = Core.KEY_NUMPAD3");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD2 = Core.KEY_NUMPAD2");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD1 = Core.KEY_NUMPAD1");
    PyRun_SimpleString("__builtins__.KEY_NUMPAD0 = Core.KEY_NUMPAD0");
    PyRun_SimpleString("__builtins__.KEY_HELP = Core.KEY_HELP");
    PyRun_SimpleString("__builtins__.KEY_INSERT = Core.KEY_INSERT");
    PyRun_SimpleString("__builtins__.KEY_SNAPSHOT = Core.KEY_SNAPSHOT");
    PyRun_SimpleString("__builtins__.KEY_EXECUTE = Core.KEY_EXECUTE");
    PyRun_SimpleString("__builtins__.KEY_PRINT = Core.KEY_PRINT");
    PyRun_SimpleString("__builtins__.KEY_SELECT = Core.KEY_SELECT");
    PyRun_SimpleString("__builtins__.KEY_DOWN = Core.KEY_DOWN");
    PyRun_SimpleString("__builtins__.KEY_RIGHT = Core.KEY_RIGHT");
    PyRun_SimpleString("__builtins__.KEY_UP = Core.KEY_UP");
    PyRun_SimpleString("__builtins__.KEY_LEFT = Core.KEY_LEFT");
    PyRun_SimpleString("__builtins__.KEY_HOME = Core.KEY_HOME");
    PyRun_SimpleString("__builtins__.KEY_END = Core.KEY_END");
    PyRun_SimpleString("__builtins__.KEY_CAPITAL = Core.KEY_CAPITAL");
    PyRun_SimpleString("__builtins__.KEY_PAUSE = Core.KEY_PAUSE");
    PyRun_SimpleString("__builtins__.KEY_MENU = Core.KEY_MENU");
    PyRun_SimpleString("__builtins__.KEY_CONTROL = Core.KEY_CONTROL");
    PyRun_SimpleString("__builtins__.KEY_ALT = Core.KEY_ALT");
    PyRun_SimpleString("__builtins__.KEY_SHIFT = Core.KEY_SHIFT");
    PyRun_SimpleString("__builtins__.KEY_CLEAR = Core.KEY_CLEAR");
    PyRun_SimpleString("__builtins__.KEY_MBUTTON = Core.KEY_MBUTTON");
    PyRun_SimpleString("__builtins__.KEY_CANCEL = Core.KEY_CANCEL");
    PyRun_SimpleString("__builtins__.KEY_RBUTTON = Core.KEY_RBUTTON");
    PyRun_SimpleString("__builtins__.KEY_LBUTTON = Core.KEY_LBUTTON");
    PyRun_SimpleString("__builtins__.KEY_START = Core.KEY_START");
    PyRun_SimpleString("__builtins__.KEY_DELETE = Core.KEY_DELETE");
    PyRun_SimpleString("__builtins__.KEY_SPACE = Core.KEY_SPACE");
    PyRun_SimpleString("__builtins__.KEY_ESCAPE = Core.KEY_ESCAPE");
    PyRun_SimpleString("__builtins__.KEY_RETURN = Core.KEY_RETURN");
    PyRun_SimpleString("__builtins__.KEY_ENTER = Core.KEY_ENTER");
    PyRun_SimpleString("__builtins__.KEY_TAB = Core.KEY_TAB");
    PyRun_SimpleString("__builtins__.BUTTON_RIGHT = Core.BUTTON_RIGHT");
    PyRun_SimpleString("__builtins__.KEY_BACKSPACE = Core.KEY_BACKSPACE");
    PyRun_SimpleString("__builtins__.BUTTON_MIDDLE = Core.BUTTON_MIDDLE");
    PyRun_SimpleString("__builtins__.BUTTON_LEFT = Core.BUTTON_LEFT");
    PyRun_SimpleString("__builtins__.ANY = Core.ANY");
    PyRun_SimpleString("__builtins__.RELEASE = Core.RELEASE");
    PyRun_SimpleString("__builtins__.CLICK = Core.CLICK");
    PyRun_SimpleString("__builtins__.PRESS = Core.PRESS");
    PyRun_SimpleString("__builtins__.MOUSE = Core.MOUSE");
    PyRun_SimpleString("__builtins__.KEYBOARD = Core.KEYBOARD");
    PyRun_SimpleString("__builtins__.BUTTON_STATE_DOWN = Core.BUTTON_STATE_DOWN");
    PyRun_SimpleString("__builtins__.BUTTON_STATE_UP = Core.BUTTON_STATE_UP");
    PyRun_SimpleString("__builtins__.KEY_STATE_DOWN = Core.KEY_STATE_DOWN");
    PyRun_SimpleString("__builtins__.KEY_STATE_UP = Core.KEY_STATE_UP");

    
    // Make opengl methods available in the global namespace
    PyRun_SimpleString("__builtins__.GL_POINTS = OpenGL.GL_POINTS");
    PyRun_SimpleString("__builtins__.GL_LINES = OpenGL.GL_LINES"); 
    PyRun_SimpleString("__builtins__.GL_LINE_LOOP = OpenGL.GL_LINE_LOOP");
    PyRun_SimpleString("__builtins__.GL_LINE_STRIP = OpenGL.GL_LINE_STRIP");                           
    PyRun_SimpleString("__builtins__.GL_TRIANGLES = OpenGL.GL_TRIANGLES");                            
    PyRun_SimpleString("__builtins__.GL_TRIANGLE_STRIP = OpenGL.GL_TRIANGLE_STRIP");                       
    PyRun_SimpleString("__builtins__.GL_TRIANGLE_FAN = OpenGL.GL_TRIANGLE_FAN");                         
    PyRun_SimpleString("__builtins__.GL_QUADS = OpenGL.GL_QUADS");                                
    PyRun_SimpleString("__builtins__.GL_QUAD_STRIP = OpenGL.GL_QUAD_STRIP");
    PyRun_SimpleString("__builtins__.GL_POLYGON = OpenGL.GL_POLYGON");
    
    PyRun_SimpleString("__builtins__.glBegin = OpenGL.glBegin");
    PyRun_SimpleString("__builtins__.glEnd = OpenGL.glEnd");
    PyRun_SimpleString("__builtins__.glVertex = OpenGL.glVertex");
    PyRun_SimpleString("__builtins__.glNormal = OpenGL.glNormal");
    PyRun_SimpleString("__builtins__.glColor = OpenGL.glColor");
    PyRun_SimpleString("__builtins__.glTranslate = OpenGL.glTranslate");
    PyRun_SimpleString("__builtins__.glRotate = OpenGL.glRotate");
    PyRun_SimpleString("__builtins__.glScale = OpenGL.glScale");
    PyRun_SimpleString("__builtins__.glScale = OpenGL.glScale");
    PyRun_SimpleString("__builtins__.glPushMatrix = OpenGL.glPushMatrix");
    PyRun_SimpleString("__builtins__.glPopMatrix = OpenGL.glPopMatrix");


    // Create global engine instance
    mpy_PyEngine *py_global_engine = mpy_PyEngine_NEW();
    //py_global_engine->internalObject = (PyEngine *)Mango::Engine; // WARNING: this downcasting from a CoreEngine to a PyEngine is dangerous, and only works if you are SURE that Mango::Engine is actually a PyEngine!
    py_global_engine->internalObject = Mango::Engine; // WARNING: this downcasting from a CoreEngine to a PyEngine is dangerous, and only works if you are SURE that Mango::Engine is actually a PyEngine!
    PyModule_AddObject(module_core, "Engine", reinterpret_cast<PyObject *>(py_global_engine));
    PyRun_SimpleString("__builtins__.Engine = Core.Engine");
    
    // Create global keyboard instance
    mpy_CoreKeyboard *py_global_keyboard = mpy_CoreKeyboard_NEW();
    py_global_keyboard->internalObject = Mango::Keyboard;
    PyModule_AddObject(module_core, "Keyboard", reinterpret_cast<PyObject *>(py_global_keyboard));
    PyRun_SimpleString("__builtins__.Keyboard = Core.Keyboard");
    
    // Create global mouse instance
    mpy_CoreMouse *py_global_mouse = mpy_CoreMouse_NEW();
    py_global_mouse->internalObject = Mango::Mouse;
    PyModule_AddObject(module_core, "Mouse", reinterpret_cast<PyObject *>(py_global_mouse));
    PyRun_SimpleString("__builtins__.Mouse = Core.Mouse");

    // Create global frame instance
    PyGlobalFrame  = mpy_Frame_NEW();
    PyGlobalFrame->internalObject = Mango::GlobalFrame;
    PyGlobalFrame->parentFrame = NULL;
    Py_INCREF(PyGlobalFrame);
    PyModule_AddObject(module_core, "GlobalFrame", reinterpret_cast<PyObject *>(PyGlobalFrame));
    PyRun_SimpleString("__builtins__.GlobalFrame = Core.GlobalFrame");
    
    // Create global camera instance
    if (Mango::Camera != NULL){
      mpy_Frame *py_camera_focus = mpy_Frame_NEW();
      py_camera_focus->internalObject = Mango::Camera->parentFrame();      
      mpy_Frame_init(py_camera_focus, NULL, NULL);

      mpy_CoreCamera *py_global_camera = mpy_CoreCamera_NEW();
      Py_INCREF(py_camera_focus);
      py_global_camera->parentFrame = py_camera_focus;
      mpy_Object_init((mpy_Object *)py_global_camera, NULL, NULL);            
      
      py_global_camera->internalObject = Mango::Camera;
      PyModule_AddObject(module_core, "Camera", reinterpret_cast<PyObject *>(py_global_camera));
      PyRun_SimpleString("__builtins__.Camera = Core.Camera");
    }
  
    // Create global view instance
    if (Mango::View != NULL){
      mpy_CoreCamera *py_global_view = mpy_CoreCamera_NEW();
      py_global_view->internalObject = Mango::View;
      PyModule_AddObject(module_core, "View", reinterpret_cast<PyObject *>(py_global_view));
      PyRun_SimpleString("__builtins__.View = Core.View");
    }

    // Make environment available to extensions
    PyModule_AddObject(module_mpygen, "GLOBAL_FRAME", PyCObject_FromVoidPtr((void *)Mango::GlobalFrame, mpy_trivialDelMethod));
    PyModule_AddObject(module_mpygen, "PY_GLOBAL_FRAME", PyCObject_FromVoidPtr((void *)PyGlobalFrame, mpy_trivialDelMethod));
    PyModule_AddObject(module_mpygen, "ENGINE", PyCObject_FromVoidPtr((void *)Mango::Engine, mpy_trivialDelMethod));
    PyModule_AddObject(module_mpygen, "CAMERA", PyCObject_FromVoidPtr((void *)Mango::Camera, mpy_trivialDelMethod));
    PyModule_AddObject(module_mpygen, "VIEW", PyCObject_FromVoidPtr((void *)Mango::View, mpy_trivialDelMethod));
    PyModule_AddObject(module_mpygen, "KEYBOARD", PyCObject_FromVoidPtr((void *)Mango::Keyboard, mpy_trivialDelMethod));
    PyModule_AddObject(module_mpygen, "MOUSE", PyCObject_FromVoidPtr((void *)Mango::Mouse, mpy_trivialDelMethod));    

    //PyModule_AddObject(module_mpygen, "TYPE_OBJECT", PyCObject_FromVoidPtr((void *)&mpy_ObjectType, mpy_trivialDelMethod));

    PyObject *global_types = PyDict_New();
    PyModule_AddObject(module_mpygen, "TYPES", global_types);

    //PyDict_SetItemString(global_types, "mangopy.core.object", PyCObject_FromVoidPtr((void *)&mpy_ObjectType, mpy_trivialDelMethod));
    MangoPy::register_py_type_object("mangopy.core.input_event", &mpy_InputEventType);
    MangoPy::register_py_type_object("mangopy.core.vector", &mpy_VectorType);
    MangoPy::register_py_type_object("mangopy.core.matrix", &mpy_MatrixType);
    MangoPy::register_py_type_object("mangopy.core.object", &mpy_ObjectType);
    MangoPy::register_py_type_object("mangopy.core.frame", &mpy_FrameType);
    MangoPy::register_py_type_object("mangopy.core.py_enging", &mpy_PyEngineType);
    MangoPy::register_py_type_object("mangopy.core.core_camera", &mpy_CoreCameraType);
    MangoPy::register_py_type_object("mangopy.core.core_keyboard", &mpy_CoreKeyboardType);
    MangoPy::register_py_type_object("mangopy.core.core_mouse", &mpy_CoreMouseType);
    MangoPy::register_py_type_object("mangopy.core.triangle", &mpy_TriangleType);

    // Setup Python error buffer
    PyRun_SimpleString("\n\
#import sys \n\
class MangoPy_StdErr: \n\
    def write(self, msg): \n\
        _mpygen.writeToPythonScriptStderr(msg) \n\
sys.stderr = MangoPy_StdErr() \n\
");    
  }
  
  void runScript(const char* fname, bool prepend_engine_path){    
    char run_script_code[300];
    
    if (prepend_engine_path){
      sprintf(run_script_code, "exec(compile(open(os.path.join(Core.MANGO_ABSOLUTE_PATH, \"%s\")).read(), 'main.py', 'exec'), locals(), globals())", fname, fname);
    }
    else{
      sprintf(run_script_code, "exec(compile(open(\"%s\").read(), '%s', 'exec'), locals(), globals())", fname, fname);		
    }    
    if (PyRun_SimpleString(run_script_code) == -1){
      throw MangoPy::ScriptError(NULL, "Main Script", "");
    }    
  }
  
  void finalize(){
    Py_DECREF(PyGlobalFrame);
    Py_Finalize();
    Mango::finalize();
  }








  
  // Convert a "char *" string to "whcar_t *", or NULL on error.
  // Result string must be free'd
  wchar_t *char2wchar(char *arg)  {

#ifdef WINDOWS
    wchar_t *result;
    DWORD dest_cch;
    int arg_len = strlen(arg) + 1; // include NULL term in all ops
    /* use MultiByteToWideChar() to see how much we need. */
    /* NOTE: this will include the null-term in the length */
    dest_cch = MultiByteToWideChar(CP_ACP, 0, arg, arg_len, NULL, 0);
    // alloc the buffer
    result = (wchar_t *)malloc(dest_cch * sizeof(wchar_t));
    if (result==NULL)
      return NULL;
    /* do the conversion */
    if (0==MultiByteToWideChar(CP_ACP, 0, arg, arg_len, result, dest_cch)) {
      free(result);
      return NULL;
    }
    return result;
  }


#else // conditional on def(WINDOWS)

    
  wchar_t *res;
#ifdef HAVE_BROKEN_MBSTOWCS
  /* Some platforms have a broken implementation of
   * mbstowcs which does not count the characters that
   * would result from conversion.  Use an upper bound.
   */
  size_t argsize = strlen(arg);
#else
  size_t argsize = mbstowcs(NULL, arg, 0);
#endif
  size_t count;
  unsigned char *in;
  wchar_t *out;
#ifdef HAVE_MBRTOWC
  mbstate_t mbs;
#endif
  if (argsize != (size_t)-1) {
    res = (wchar_t *)PyMem_Malloc((argsize+1)*sizeof(wchar_t));
    if (!res)
      goto oom;
    count = mbstowcs(res, arg, argsize+1);
    if (count != (size_t)-1) {
      wchar_t *tmp;
      /* Only use the result if it contains no
	 surrogate characters. */
      for (tmp = res; *tmp != 0 &&
	     (*tmp < 0xd800 || *tmp > 0xdfff); tmp++)
	;
      if (*tmp == 0)
	return res;
    }
    PyMem_Free(res);
  }
  /* Conversion failed. Fall back to escaping with surrogateescape. */
#ifdef HAVE_MBRTOWC
  /* Try conversion with mbrtwoc (C99), and escape non-decodable bytes. */
	
  /* Overallocate; as multi-byte characters are in the argument, the
     actual output could use less memory. */
  argsize = strlen(arg) + 1;
  res = (wchar_t *)PyMem_Malloc(argsize*sizeof(wchar_t));
  if (!res) goto oom;
  in = (unsigned char*)arg;
  out = res;
  memset(&mbs, 0, sizeof mbs);
  while (argsize) {
    size_t converted = mbrtowc(out, (char*)in, argsize, &mbs);
    if (converted == 0)
      /* Reached end of string; null char stored. */
      break;
    if (converted == (size_t)-2) {
      /* Incomplete character. This should never happen,
	 since we provide everything that we have -
	 unless there is a bug in the C library, or I 
	 misunderstood how mbrtowc works. */
      fprintf(stderr, "unexpected mbrtowc result -2\n");
      return NULL;
    }
    if (converted == (size_t)-1) {
      /* Conversion error. Escape as UTF-8b, and start over
	 in the initial shift state. */
      *out++ = 0xdc00 + *in++;
      argsize--;
      memset(&mbs, 0, sizeof mbs);
      continue;
    }
    if (*out >= 0xd800 && *out <= 0xdfff) {
      /* Surrogate character.  Escape the original
	 byte sequence with surrogateescape. */
      argsize -= converted;
      while (converted--)
	*out++ = 0xdc00 + *in++;
      continue;
    }
    /* successfully converted some bytes */
    in += converted;
    argsize -= converted;
    out++;
  }
#else
  /* Cannot use C locale for escaping; manually escape as if charset
     is ASCII (i.e. escape all bytes > 128. This will still roundtrip
     correctly in the locale's charset, which must be an ASCII superset. */
  res = (wchar_t *)PyMem_Malloc((strlen(arg)+1)*sizeof(wchar_t));
  if (!res) goto oom;
  in = (unsigned char*)arg;
  out = res;
  while(*in)
    if(*in < 128)
      *out++ = *in++;
    else
      *out++ = 0xdc00 + *in++;
  *out = 0;
#endif
  return res;
 oom:
  fprintf(stderr, "out of memory\n");
  return NULL;
}


#endif // conditional on def(WINDOWS)


int initialize_module_environment(){
  PyObject *mpygen_module = PyImport_AddModule("_mpygen");
  if (mpygen_module == NULL){
    return -1;
  }
 
  PyObject *py_global_frame = PyObject_GetAttrString(mpygen_module, "GLOBAL_FRAME");
  Mango::GlobalFrame = (Mango::Core::Frame *)PyCObject_AsVoidPtr(py_global_frame);
  PyObject *py_engine = PyObject_GetAttrString(mpygen_module, "ENGINE");
  Mango::Engine = (Mango::Core::CoreEngine *)PyCObject_AsVoidPtr(py_engine);  
  PyObject *py_camera = PyObject_GetAttrString(mpygen_module, "CAMERA");
  Mango::Camera = (Mango::Core::CoreCamera *)PyCObject_AsVoidPtr(py_camera);  
  PyObject *py_view = PyObject_GetAttrString(mpygen_module, "VIEW");
  Mango::View = (Mango::Core::CoreCamera *)PyCObject_AsVoidPtr(py_view);  
  PyObject *py_keyboard = PyObject_GetAttrString(mpygen_module, "KEYBOARD");
  Mango::Keyboard = (Mango::Core::CoreKeyboard *)PyCObject_AsVoidPtr(py_keyboard);
  PyObject *py_mouse = PyObject_GetAttrString(mpygen_module, "MOUSE");
  Mango::Mouse = (Mango::Core::CoreMouse *)PyCObject_AsVoidPtr(py_mouse);    
  PyObject *py_pyglobalframe = PyObject_GetAttrString(mpygen_module, "PY_GLOBAL_FRAME");  
  PyGlobalFrame = (mpy_Frame *)PyCObject_AsVoidPtr(py_pyglobalframe);    
 
  return 0;
}

  
} // MangoPy

