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


#ifndef MANGOPY_PYENGINE
#define MANGOPY_PYENGINE

#include <mango/mangopy/mangopy_core.h>
#include <mango/mangopy/mangopy_python.h>
#include <vector>
#include <mango/mango.h>
#include <mango/mangopy/mangopy_vector.h>
#include <mango/mangopy/mangopy_core.h>

namespace MangoPy{

  //// @cons
  typedef std::pair<Mango::Core::Object *, PyObject *> ObjectPythonEventRecord;
  //// @endcond
    
  /**
   * An error representing an exception in a Python script
   */ 
  class PythonScriptError : public Mango::Core::Error{
  public:
  PythonScriptError(const char *origObjectType, const char *originatingMethodName, const char *m=""): Error(origObjectType, originatingMethodName, m){
    }
    
    //// @cond
    virtual const char *objectType() const{
      return "PythonScriptError";
    }
    //// @endcond
  };
  
  
  /**
   * An engine object derived from Core::CoreEngine that adds support
   * for triggerring Python methods as callback functions. A number of
   * methods dealing with such events ("scripted events") are added. In
   * simulations written in Python, the global Engine is an instance of
   * this class
   */
  class PyEngine : public Mango::Core::CoreEngine, public Mango::Core::ObjectContainer{
      public:
          PyEngine();
          ~PyEngine();
  
	  //// @cond
          virtual const char *objectType() const{
              return "PyEngine";
          }
  
          const char *getObjectEventMethodName(int event_type);
	  //// @endcond
	  
          virtual bool setScriptedEvent(mpy_Object* object, int event_mask);
      	  virtual bool removeScriptedEvent(mpy_Object* object, int event_mask);
          virtual bool toggleScriptedEvent(mpy_Object* object, int event_mask);
          virtual bool objectHasScriptedEvent(mpy_Object *object, int event_mask);        
  
          virtual void removeObject(Mango::Core::Object* object_to_remove, int BOCT_ID);
          
          /*
          virtual bool setEvent(Object* object, int event_type);
          virtual bool removeEvent(Object* object, int event_type);
          */
          
          virtual void executeCallback(mpy_Object *obj, int event_type);
  
  
      protected:
  
          virtual void evt_render();
          virtual void evt_draw();
          virtual void evt_step();
          virtual void evt_input();
  
          std::vector<ObjectPythonEventRecord> python_events[ENGINE_MAX_EVENT_TYPES];
          static int BOC_TYPE_IDS[ENGINE_MAX_EVENT_TYPES];
  };
  
  
 
} // MangoPy  

#endif // MANGOPY_PYENGINE
