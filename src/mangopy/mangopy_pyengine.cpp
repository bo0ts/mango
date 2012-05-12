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
#include <mango/mangopy/mangopy_pyengine.h>

#include <mango/mangopy/mangopy.h>
#include <string>

namespace MangoPy{
  
  /* Static Members */
  int PyEngine::BOC_TYPE_IDS[ENGINE_MAX_EVENT_TYPES] = {-1};
  
  /* Constructors, Destructors */
  PyEngine::PyEngine(){
      // If not already registered, register the PyEngine as a BOC type for each possible event
      if (PyEngine::BOC_TYPE_IDS[0] == -1){
          for (int i = 0; i < ENGINE_MAX_EVENT_TYPES; i += 1){
              PyEngine::BOC_TYPE_IDS[i] = Mango::Core::Object::createObjectContainerType();
          }
      }
  
  
      for (int i = 0; i < ENGINE_MAX_EVENT_TYPES; i += 1){
          events[i].reserve(ENGINE_INIT_EVENTS_STACK);
          python_events[i].reserve(ENGINE_INIT_EVENTS_STACK);
      }
  
      // Window Properties
  
      setWindowDimensions(640, 480);
      setWindowFullscreen(0);
      setWindowFps(60);
  }
  
  PyEngine::~PyEngine(){
    // the destructor for python_events gets called automatically
    objects.clear();
  }
  
  /* Methods */
  void PyEngine::removeObject(Mango::Core::Object *object_to_remove, int BOCT_ID){
      int object_to_remove_id, python_events_list_size;
  
      if (object_to_remove == NULL){
          throw Mango::Core::ValueError(objectType(), "removeObject", "cannot remove NULL value");
      }
  
      // If object_to_remove isn't keeping track of BOCs at least up to BOCT_ID the object is not added
      if (object_to_remove->objectContainers.capacity() <= BOCT_ID){
          return;
      }
  
      object_to_remove_id = object_to_remove->objectContainers[BOCT_ID].first;
      if (object_to_remove_id > -1 && object_to_remove->objectContainers[BOCT_ID].second == this){
          python_events_list_size = python_events[BOCT_ID].size();
  
          if (object_to_remove_id == python_events_list_size - 1){
              // Just erase it, ids present no problem
              python_events[BOCT_ID].pop_back();
          }
          else{
              // Copy the last member to the position of the bad member
              python_events[BOCT_ID][object_to_remove_id] = python_events[BOCT_ID][python_events_list_size-1];
  
              // Change the id of what was previously the last member
              python_events[BOCT_ID][object_to_remove_id].first->objectContainers[BOCT_ID].first = object_to_remove_id;
  
              // Pop the last member
              python_events[BOCT_ID].pop_back();
          }
          object_to_remove->objectContainers[BOCT_ID].first = -1;
  
      }
  }
  
  
  bool PyEngine::setScriptedEvent(mpy_Object* object, int event_type){    
      ObjectPythonEventRecord eventRecord;
      PyObject *callback;
      int j = 1; // j is the event_type, corresponds to constants defined in constants.h
      if (object->internalObject->objectContainers.size() < ENGINE_MAX_EVENT_TYPES){
          object->internalObject->objectContainers.resize(ENGINE_MAX_EVENT_TYPES);
      }
      for (int i = 0; i < ENGINE_MAX_EVENT_TYPES; i += 1){   
        if ((event_type & j) == j){
  	// Get the appropriate callback
  	const char *object_method_name = getObjectEventMethodName(i);
  	callback = PyObject_GetAttrString(reinterpret_cast<PyObject *>(object), object_method_name);
  	if (callback == NULL){
  	  char err_msg[250];
  	  sprintf(err_msg, "Error: event method '%s' does not exist for this object", object_method_name);
  	  throw Mango::Core::Error(objectType(), "setScriptedEvent", err_msg);
  	}
  	/*
  	  Previous implementation: replace old callback with new callback on repeat event setting
  	    
  	  // If the object already has a callback registered for this event, XDECREF it
  	  if (object->internalObject->objectContainers[BOC_TYPE_IDS[i]].first != -1){
  	  Py_XDECREF(python_events[i][object->internalObject->objectContainers[BOC_TYPE_IDS[i]].first].second);
  	  }
  	*/
  	// New implementation: ignore repeat event setting
  	if (object->internalObject->objectContainers[BOC_TYPE_IDS[i]].first == -1){
  
  	  
  	  Py_INCREF(callback); // Save reference to new callback	    
  	  // Set eventRecord appropriately
  	  eventRecord.first = object->internalObject;
  	  eventRecord.second = callback;
  	  python_events[i].push_back(eventRecord); // Push new callback onto the python_events vector	   
  	  object->internalObject->objectContainers[BOC_TYPE_IDS[i]].first = python_events[i].size()-1; // save a reference to where this callback is stored in the object itself
  	  object->internalObject->objectContainers[BOC_TYPE_IDS[i]].second = this;                     // save a reference to this PyEngine object as a ObjectRecordContainer
  	  
  	  /*
  	    __printPythonEvents(0);
  	    __printPythonEvents(3);
  	    object->internalObject->__printObjectContainers();
  	    object->internalObject->__printObjectEvents();
  	  */
  	}
        }
        j = j << 1;
      }        
      return true;
  }
  
  
  bool PyEngine::removeScriptedEvent(mpy_Object* object, int event_type){        
      ObjectPythonEventRecord eventRecord;
      PyObject *callback;    
      int event_index, event_list_size;
      
      int j = 1; // j is the event_type, corresponds to constants defined in constants.h
      for (int i = 0; i < ENGINE_MAX_EVENT_TYPES; i += 1){        
          if ((event_type & j) == j){            
              // If the object doesn't have an objectContainer registered for this event, it doesn't have a callback either
              if (object->internalObject->objectContainers.size() <= BOC_TYPE_IDS[i]){
                  continue;
              }
                          
              // Check if the object has a callback registered for this event
              if (object->internalObject->objectContainers[BOC_TYPE_IDS[i]].first != -1){
                  event_index = object->internalObject->objectContainers[BOC_TYPE_IDS[i]].first;
                  event_list_size = python_events[i].size();
                  
                  // XDECREF it
                  Py_XDECREF(python_events[i][event_index].second);
                  
                  if (event_index < event_list_size - 1){
                      // Copy the last callback to the position of the callback we're removing
                      python_events[i][event_index] = python_events[i][event_list_size - 1];
                      
                      // Update the index of what was previously the last callback
                      python_events[i][event_index].first->objectContainers[BOC_TYPE_IDS[i]].first = event_index;
                  }
                  
                  // Pop the last member
                  python_events[i].pop_back();   
                  
                  // Remove the event index from the object
                  object->internalObject->objectContainers[BOC_TYPE_IDS[i]].first = -1;                                                              
              }     
              
              /*
              __printPythonEvents(0);
              __printPythonEvents(3);
              object->internalObject->__printObjectContainers();                 
              object->internalObject->__printObjectEvents();
              */
          }
          j = j << 1;
      }        
      return true;
  }
  
  bool PyEngine::toggleScriptedEvent(mpy_Object* object, int event_type){        
      ObjectPythonEventRecord eventRecord;
      PyObject *callback;    
      int event_index, event_list_size;
      
      if (objectHasScriptedEvent(object, event_type)){
        removeScriptedEvent(object, event_type);
      }
      else{
        setScriptedEvent(object, event_type);
      }                      
  
      return true;    
  }
  
  bool PyEngine::objectHasScriptedEvent(mpy_Object* object, int event_type){      
      ObjectPythonEventRecord eventRecord;
      PyObject *callback;
      int j = 1; // j is the event_type, corresponds to constants defined in constants.h
      
      if (object->internalObject->objectContainers.size() < ENGINE_MAX_EVENT_TYPES){
          object->internalObject->objectContainers.resize(ENGINE_MAX_EVENT_TYPES);
      }
      for (int i = 0; i < ENGINE_MAX_EVENT_TYPES; i += 1){        
          if ((event_type & j) == j){        
              // If the object does not have a callback for this event type, return false            
              if (object->internalObject->objectContainers[BOC_TYPE_IDS[i]].first == -1){
                  return false;
              }            
          }
          j = j << 1;
      }
      // The object must have a callback for all events described by event_type, return true
      return true;
  }
  
  
  void PyEngine::evt_step(){
      Mango::Core::Object* currentObject;
      PyObject* result, *arglist;
  
      // Execute C events
      std::vector<Mango::Core::Object*>::iterator current_object;
      for (current_object = events[EVT_TYPE_STEP].begin(); current_object < events[EVT_TYPE_STEP].end(); current_object++){
          (*current_object)->step();
      }
  
      // Execute Python events
      ObjectPythonEventRecord eventRecord;
      for (int i = 0; i < python_events[EVT_TYPE_STEP].size(); ++i){      
        eventRecord = python_events[EVT_TYPE_STEP][i];
        arglist = Py_BuildValue("()");
        result = PyEval_CallObject(eventRecord.second, arglist);
        Py_DECREF(arglist); // dismiss the argument list we created
        if (result == NULL){
  	throwCExceptionFromPythonException(eventRecord.first->objectType(), "step");          
        }
        // We don't care about the result, DECREF it
        Py_DECREF(result);
      }
  }
  
  
  void PyEngine::evt_render(){
      PyObject* result, *arglist;
      std::vector<Mango::Core::Object*>::iterator current_object;
  
      glEnable(GL_LIGHTING);
  
      // If we have a camera, let it do its thing
      if (Mango::Camera != NULL){
          Mango::Camera->manipulateCamera();
      }
  
      // Execute C events
      for (current_object = events[EVT_TYPE_RENDER].begin(); current_object < events[EVT_TYPE_RENDER].end(); current_object++){
          glPushMatrix();
              //executeObjectRenderEvent((*current_object));
              (*current_object)->render();
          glPopMatrix();
      }
  
      // Execute Python events
      ObjectPythonEventRecord eventRecord;
      for (int i = 0; i < python_events[EVT_TYPE_RENDER].size(); ++i){      
        eventRecord = python_events[EVT_TYPE_RENDER][i];
          arglist = Py_BuildValue("()");
  	glPushMatrix();
          result = PyEval_CallObject(eventRecord.second, arglist);
  	glPopMatrix();
          Py_DECREF(arglist); // Dismiss the argument list we created
          if (result == NULL){
              // If the result is NULL, the interpreter threw an exception. raise this as a PythonScript exception
  	  throwCExceptionFromPythonException(eventRecord.first->objectType(), "render");
          }
          // We don't care about the result, DECREF it
          Py_DECREF(result);
      }
  }
  
  void PyEngine::evt_draw(){
      PyObject* result, *arglist;
  
      // Set up an orthographic projection
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();
      glOrtho(-window_width/2.0f, window_width/2.0f, -window_height/2.0f, window_height/2.0f, -1.0f, 1.0f);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glDisable(GL_LIGHTING);
      glClear(GL_DEPTH_BUFFER_BIT);
  
      if (Mango::View != NULL){
          Mango::View->manipulateCamera();
      }
  
      // Execute C events
      std::vector<Mango::Core::Object*>::iterator current_object;
      for (current_object = events[EVT_TYPE_DRAW].begin(); current_object < events[EVT_TYPE_DRAW].end(); current_object++){
          glPushMatrix();
              //executeObjectDrawEvent((*current_object));
              (*current_object)->draw();
          glPopMatrix();
      }
  
      // Execute Python events
      ObjectPythonEventRecord eventRecord;
      for (int i = 0; i < python_events[EVT_TYPE_DRAW].size(); ++i){      
        eventRecord = python_events[EVT_TYPE_DRAW][i];
        arglist = Py_BuildValue("()");
        glPushMatrix();
        result = PyEval_CallObject(eventRecord.second, arglist);
        glPopMatrix();
        Py_DECREF(arglist); // Dismiss the argument list we created
        if (result == NULL){
  	// If the result is NULL, the interpreter threw an exception. raise this as a PythonScript exception
  	throwCExceptionFromPythonException(eventRecord.first->objectType(), "draw");
        }
        // We don't care about the result, DECREF it
        Py_DECREF(result);
      }
      
  
      // Restore the perspective projection
      glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      glMatrixMode(GL_MODELVIEW);
  
  }
  
  void PyEngine::evt_input(){
    std::vector<Mango::Core::Object *>::iterator current_object;
    std::deque<Mango::Core::inputEvent>::iterator current_event;
    PyObject* result, *arglist;
  
    mpy_InputEvent* py_current_event = mpy_InputEvent_NEW();
  
    // Mango::Keyboard Events
    for (current_event = Mango::Keyboard->eventBuffer.begin(); current_event < Mango::Keyboard->eventBuffer.end(); current_event ++){		      	       		     
      // Execute C Events
      for (current_object = events[EVT_TYPE_INPUT].begin(); current_object < events[EVT_TYPE_INPUT].end(); current_object++){
        (*current_object)->input((*current_event));
      }
  
      // Execute Python Events
      //py_current_event->event = (*current_event);
      py_current_event->source = current_event->source;
      py_current_event->type = current_event->type;
      py_current_event->code = current_event->code;
      ObjectPythonEventRecord eventRecord;
      for (int i = 0; i < python_events[EVT_TYPE_INPUT].size(); ++i){      
        eventRecord = python_events[EVT_TYPE_INPUT][i];
        arglist = Py_BuildValue("(O)", (PyObject *)py_current_event);	
        result = PyEval_CallObject(eventRecord.second, arglist);
        Py_DECREF(arglist); // dismiss the argument list we created
        if (result == NULL){
  	// If the result is NULL, the interpreter threw an exception. raise this as a PythonScript exception
  	throwCExceptionFromPythonException(eventRecord.first->objectType(), "input");
        }
        // We don't care about the result, DECREF it
        Py_DECREF(result);
      }
    }	  
    Mango::Keyboard->eventBuffer.clear();  
    
    // Mouse
    for (current_event = Mango::Mouse->eventBuffer.begin(); current_event < Mango::Mouse->eventBuffer.end(); current_event ++){		      	       		     
      // Execute C Events
      for (current_object = events[EVT_TYPE_INPUT].begin(); current_object < events[EVT_TYPE_INPUT].end(); current_object++){
        (*current_object)->input((*current_event));
      }
      
      // Execute Python Events
      //    py_current_event->event = (*current_event);
      py_current_event->source = current_event->source;
      py_current_event->type = current_event->type;
      py_current_event->code = current_event->code;
      std::vector<ObjectPythonEventRecord>::iterator eventRecord;
      for (eventRecord = python_events[EVT_TYPE_INPUT].begin(); eventRecord < python_events[EVT_TYPE_INPUT].end(); eventRecord++){
          arglist = Py_BuildValue("(O)", (PyObject *)py_current_event);
          result = PyEval_CallObject((*eventRecord).second, arglist);
          Py_DECREF(arglist); // dismiss the argument list we created
          if (result == NULL){
              // If the result is NULL, the interpreter threw an exception. raise this as a PythonScript exception
  	  throwCExceptionFromPythonException((*eventRecord).first->objectType(), "input");
          }
          // We don't care about the result, DECREF it
          Py_DECREF(result);
      }
    }
    Mango::Mouse->eventBuffer.clear();    
  
    Py_DECREF(py_current_event);
  }
  
  void PyEngine::executeCallback(mpy_Object *obj, int event_type){
      PyObject *callback, *arglist, *result;
      const char *callback_name;
  
      callback_name = static_cast<MangoPy::PyEngine *>(Mango::Engine)->getObjectEventMethodName(event_type);
      callback = PyObject_GetAttrString(reinterpret_cast<PyObject *>(obj), callback_name);
      arglist = Py_BuildValue("()");
      result = PyEval_CallObject(callback, arglist);
      Py_DECREF(arglist); // Dismiss the argument list we created
      if (result == NULL){
          // If the result is NULL, the interpreter threw an exception. raise this as a PythonScript exception
          PyErr_Print(); // Print the error to stderr
          throw MangoPy::PythonScriptError(obj->internalObject->objectType(), callback_name, "");
      }
      // We don't care about the result, DECREF it
      Py_DECREF(result);
  }
  
  
  const char * PyEngine::getObjectEventMethodName(int event_type){
      const char *ObjectEventMethods[ENGINE_MAX_EVENT_TYPES];
      ObjectEventMethods[EVT_TYPE_RENDER] = "render";
      ObjectEventMethods[EVT_TYPE_DRAW] = "draw";
      ObjectEventMethods[EVT_TYPE_PRE_STEP] = "pre_step";
      ObjectEventMethods[EVT_TYPE_STEP] = "step";
      ObjectEventMethods[EVT_TYPE_POST_STEP] = "post_step";
      ObjectEventMethods[EVT_TYPE_INPUT] = "input";
      ObjectEventMethods[EVT_TYPE_MOUSE_MOVE] = "mouse_move";
  
      if ((event_type < 0) || (event_type >= ENGINE_MAX_EVENT_TYPES )){
          return NULL;
      }
      return ObjectEventMethods[event_type];
  }

} // MangoPy
