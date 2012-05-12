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
#include <iostream>
#include <vector>
#include <deque>
#include "vector.h"
#include "constants.h"
#include "error.h"
#include "input.h"
#include "frame.h" 
#include "utils.h"

#ifndef MANGO_CORE
#define MANGO_CORE


namespace Mango{
  namespace Core{		
    
    class Object;
    class BaseCamera;
    class CoreEngine;
    class CoreCamera;
    

    /**
     * An "abstract" class from which classes that keep lists of
     * pointers to Core::Frames should inherit. Each ObjectContainer
     * has a unique object-container ID and can register itself as a
     * container of a given Core::Frame. Upon destruction the
     * Core::Frame instance will notify each of its containers that it
     * is being destroyed by calling its removeObject method and
     * passing the appropriate object-container ID (this allows the
     * ObjectContainer to retrieve the ObjectContainerRecord that
     * captures the relationship between these two particular
     * instances of a Frame and an ObjectContainer).
     *
     * This class is not used in the core Mango libraries, but
     * supports fundamental functionality in the Python bindings.
     */
    class ObjectContainer{
    public:
      virtual void removeObject(Object *object_to_remove, int BOCT_ID){
      }
    };
    
    /**
     * A convenience class that pairs an ObjectContainer pointer with
     * an int. Every Core::Frame keeps a list of
     * ObjectContainerRecords, the existence of which is assumed by
     * the ObjectContainer. The latter may iterate over the list
     * and store context information in the int portion of the
     * pair. The existence of a populated ObjectContainerRecord in the
     * list of a Core::Frame instance essentially means "this
     * ObjectContainer contains me, and it asked me to remember that
     * I'm it's number <value-of-first-member>, whatever that means".
     */
    class ObjectContainerRecord: public std::pair<int, ObjectContainer*>{
    public:
      ObjectContainerRecord(){
	first = -1;
	second = NULL;		            
      }
    };
    
    /**
     * The base class for all event-capable objects. It inherits from
     * Core::Frame, and implements event setting and unsetting
     * mechanisms, as well as empty event callbacks.
     */
    class Object : public Frame{
   public:
      Object();		        
      ~Object();
      //// @cond
      virtual void removeObjectFromEngineAndBOCs();
      //// @endcond
      
      /**
       * Return a string that represents the object type. This method
       * is automatically called in some error conditions in order to
       * provide object-specific trace information. Derived classes 
       * should override this method for customization.
       */
      virtual const char *objectType() const{
	return "Object";
      }

      //// @cond
      void __printEventIndices__();
      
      bool toggleVisibility();
      void setVisible(bool should_be_visible);
      bool visible();
      //// @endcond

      bool set(int event_type);
      bool unset(int event_type);
      void toggle(int event_type);
      bool executes(int event_type);
            
      //// @cond
      int objectID();
      
      int events;
      int event_indices[ENGINE_MAX_EVENT_TYPES]; // keeps track of where in the events array this object is
      //// @endcond
      
      virtual void step();
      virtual void render();
      virtual void draw();
      virtual void input(inputEvent &event);
      
		
      //// @cond
      std::vector<ObjectContainerRecord> objectContainers;
      static int nextObjectTypeId;
      static int createObjectContainerType(){
	nextObjectTypeId += 1;
	return nextObjectTypeId - 1;
      }   
      //// @endcond
           
      
    protected:
      void setObjectID(int new_objectID);
      bool is_visible;      
      int ID;
      
      friend class CoreEngine;
    };	
    
    
    
    
    
    
    
    
    
		
    /**
     * The base engine class, it is responsible for keeping track of
     * all objects, triggering object events callback functions
     * (including the camera) and storing program initilization
     * infromation. For most uses it is not necessary to derive any
     * classes from it.
     */
    class CoreEngine{
    public:
      CoreEngine();
      ~CoreEngine();
      
      virtual const char *objectType() const{
	return "CoreEngine";
      }
      
      int addObject(Object* object);
      Object* object(int objectID);
      Object* removeObject(int objectID);
      
      virtual bool setEvent(Object* object, int event_type);
      virtual bool removeEvent(Object* object, int event_type);
      virtual bool toggleEvent(Object* object, int event_type);
      virtual bool objectHasEvent(Object* object, int event_type);
      

      virtual void executeStepEvents();
      virtual void executeRenderEvents();
      virtual void executeDrawEvents();		        
      virtual void executeInputEvents();
      
      
      void setCameraObject(BaseCamera* cam);
      void setViewObject(BaseCamera* vw);
      
      //// @cond
      BaseCamera *camera, *view;
      int prev_mouse_x, prev_mouse_y;
      //// @endcond
      
      // Window Settings Setters/Getters
      void setWindowDimensions(int width, int height);
      void setWindowFullscreen(bool mode);
      void setWindowFps(int fps);
      void setClearBuffer(bool should_clear);
      void setClearColor(GLfloat cl_r, GLfloat cl_g, GLfloat cl_b);
      
      void windowDimensions(int &width, int &height);
      int windowWidth();
      int windowHeight();
      bool windowFullscreen();
      int windowFps();
      bool clearBuffer();
      void clearColor(GLfloat &cl_r, GLfloat &cl_g, GLfloat &cl_b);
      
      void limitFps();
      void countFrame();
      double actualFps();

    protected:
      virtual void evt_render();
      virtual void evt_draw();
      virtual void evt_step();
      virtual void evt_input();
      
      std::vector<Object *> objects;
      std::vector<Object *> events[ENGINE_MAX_EVENT_TYPES];
      
      int window_width;
      int window_height;
      int desired_fps;

      float milliseconds_per_frame;
      int last_render_time;
      int frame_count;
      int last_fps_calc;
      float actual_fps;

      bool full_screen_mode, clear_buffer;      
    };
    
    
    
    
		
    /**
     * The base class from which all camera objects should be derived
     * - in fact, this class is more of an 'interface' in that all of
     * its method implementations are empty. A derived camera object
     * should at least override manipulateCamera(), as this method is
     * called at a the very begining of the rendering process and this
     * makes the camera object uniquely suited for modifying the
     * rendering process based on input or other parameters (for
     * instance changing the angle at which the scene is viewed based
     * on the mouse position). CoreCamera is a class that implements
     * the some common functions for a camera object and it suffices
     * for most uses. When more specialized camera functionality is
     * needed it will be necessary to derive a class from BaseCamera
     * (or perhaps from CoreCamera).  
     *
     * @see CoreCamera
     */
    class BaseCamera : public Object{
    public:
      BaseCamera();
      ~BaseCamera();
      
      //// @cond
      virtual const char *objectType() const{
	return "BaseCamera";
      }
      //// @endcond
      
      virtual void manipulateCamera();
    };
    
    
    
    
		
		


    /**
     * A Camera object derived from BaseCamera that implements
     * rudimentary control of the viewing angle, angle and
     * position locking and convenient camera positioning
     * functions. The CoreCamera object supports various modes:     
     * \verbatim embed:rst 
     * LOCK_PAN: disable panning (disables panning by clicking and dragging the left mouse button) 
     * LOCK_DISTANCE: disable zooming (disables zooming by holding and dragging both mouse buttons)
     * LOCK_FIRST_ANGLE: locks the first orientation angle of the 
         camera object (no rotation about the vertical
         axis of the local coordinate system of the camera when the 
         right mouse button is dragged)
     * LOCK_SECOND_ANGLE: locks the second orientation angle of the 
         camera object (no rotation about the horizontal
         axis of the local coordinate system of the camera when the 
         right mouse button is dragged)
     * LOCK_THIRD_ANGLE: locks the third orientation angle of the 
         camera object (no rotation about the axis running
         into the screen of the local coordinate system of the
         camera. This affects the camera's interaction with the 
         mouse only if RMB_CYLINDRICAL_ROTATE is set, in which case 
         the camera won't rotate when the right mouse button is dragged)
     * RMB_CYLINDRICAL_ROTATE: Dragging the right mouse button will 
         cause the camera to rotate around the axis of the local 
         coordinate system going into the screen.
     * LOCK_POSITION = LOCK_DISTANCE | LOCK_FIRST_ANGLE | 
         LOCK_SECOND_ANGLE | LOCK_THIRD_ANGLE
     *  LOCK_ALL = LOCK_POSITION | LOCK_PAN
      \endverbatim
     * @see BaseCamera
     */
    class CoreCamera : public BaseCamera{
    public:
      CoreCamera();
      ~CoreCamera();
      
      //// @cond
      virtual const char *objectType() const{
	return "CoreCamera";
      }
      
      void setRotationButton(int code);
      void setZoomButton(int code);
      int rotationButton();
      int zoomButton();
      //// @endcond
      
      void setMode(int new_mode);      
      void setScaleFactors(GLfloat sx, GLfloat sy, GLfloat sz);
      
      void follow(Frame *frame_to_follow);
      Frame *focus();

      void toggleMode(int mode_mask);
      bool modeEnabled(int mode_mask);
      
      void scaleFactors(GLfloat &sx, GLfloat &sy, GLfloat &sz);           
      void scale(GLfloat rx, GLfloat ry, GLfloat rz = 1);

      void lookAt(Vector at_point, GLfloat dist = -1);
      void lookFrom(Vector from_point, Vector at_point);
      void lookFrom(Vector from_point);

      virtual void manipulateCamera();
      virtual void step();
      
    protected:
      int mode;
      int rotate_camera_button_code;
      int zoom_camera_button_code;

      Frame *focus_frame;
      int prev_mouse_x, prev_mouse_y;
      Vector objf_axis_1, objf_axis_2, objf_axis_3; // rotation axes of object camera is following
      GLfloat objf_alpha, objf_beta, objf_gamma;      // rotation angles of object camera is following
      GLfloat scale_x, scale_y, scale_z;              // factors by which camera scales the world
    };
    
    
    
    
    
  }

  extern Core::CoreEngine *Engine;
  extern Core::CoreKeyboard *Keyboard;
  extern Core::CoreMouse *Mouse;
  extern Core::CoreCamera *Camera;
  extern Core::CoreCamera *View;
  extern Core::Frame *GlobalFrame;

  void requirePresenceOfEngine(const char *object, const char *method);
  void requirePresenceOfGlobalFrame(const char *object, const char *method);
  void requirePresenceOfKeyboard(const char *object, const char *method);
  void requirePresenceOfMouse(const char *object, const char *method);
  void requirePresenceOfCamera(const char *object, const char *method);
  void requirePresenceOfView(const char *object, const char *method);

}

#endif // MANGO_CORE
