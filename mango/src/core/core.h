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
    //		class CoreMouse;
    //		class CoreKeyboard;
        
    class ObjectContainer{
    public:
      virtual void removeObject(Object *object_to_remove, int BOCT_ID){
	std::cout << "Called the base function ObjectContainer::removeBasicObject" << std::endl;
      }
    };
    
    class ObjectContainerRecord: public std::pair<int, ObjectContainer*>{
    public:
      ObjectContainerRecord(){
	first = -1;
	second = NULL;		            
      }
    };
    
    /**
     * The base-class for all event-capable objects.
     * The base-class for all event-capable objects, it implements
     * - Position and arbitrary orientation in 3-space
     * - Global to local and local to global transformations
     * - (Empty) events
     */
    class Object : public Frame{
   public:
      Object();		        
      ~Object();
      virtual void removeObjectFromEngineAndBOCs();
      
      virtual const char *objectType() const{
	return "Object";
      }
      
      void __printEventIndices__();
      
      bool toggleVisibility();
      void setVisible(bool should_be_visible);
      bool visible();

      bool set(int event_type);
      bool unset(int event_type);
      void toggle(int event_type);
      bool executes(int event_type);
      //int getEventMask();		uncomment if needed                        
            
      int objectID();								        
      
      int events;
      int event_indices[ENGINE_MAX_EVENT_TYPES]; // keeps track of where in the events array this object is
      
      virtual void pre_step();
      virtual void step();
      virtual void post_step();
      virtual void render();
      virtual void draw();
      virtual void input(inputEvent &event);
      
		
      std::vector<ObjectContainerRecord> objectContainers;
      static int nextObjectTypeId;
      static int createObjectContainerType(){
	nextObjectTypeId += 1;
	return nextObjectTypeId - 1;
      }            
      
      
      // Debugging
      
      void __printObjectContainers(){
	int size = objectContainers.size();
	std::cout << std::endl << "----------------------------------------------------------------" << std::endl;
	std::cout << "object @(" << this << ") with " << size << " object containers: " << std::endl;
	for (int i = 0; i < size; i += 1){
	  std::cout << "  " << i << ") object->objectContainers[i] = " << &(objectContainers[i]) << std::endl;
	  std::cout << "  " << i << ") object->objectContainers[i].first = " << objectContainers[i].first << std::endl;
	  std::cout << "  " << i << ") object->objectContainers[i].second = " << objectContainers[i].second << std::endl;
	}
	std::cout << std::endl << "----------------------------------------------------------------" << std::endl;    
      }		    
      
      void __printObjectEvents(){
	std::cout << std::endl << "----------------------------------------------------------------" << std::endl;
	std::cout << "object @(" << this << ") with event_mask: " << events << std::endl;
	for (int i = 0; i < ENGINE_MAX_EVENT_TYPES; i += 1){
	  std::cout << "  " << i << ") object->event_indices[" << i << "] = " << event_indices[i] << std::endl;		                
	}
	std::cout << std::endl << "----------------------------------------------------------------" << std::endl;    
      }		        
      
    protected:
      void setObjectID(int new_objectID);
      bool is_visible;      
      int ID;
      
      friend class CoreEngine;
    };	
    
    
    
    
    
    
    
    
    
		
		
		
		
		
		
		
		
		
		
		
		
    /**
     * The base engine class.
     * The base engine class, it is responsible for keeping track of all objects, triggering object events
     * callback functions (including the camera) and storing program initilization infromation. For most uses it is
     * not necessary to derive any classes from it.
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
      
      //virtual void executeEvent(int event);
      virtual void executePreStepEvents();
      virtual void executeStepEvents();
      virtual void executePostStepEvents();
      virtual void executeRenderEvents();
      virtual void executeDrawEvents();		        
      virtual void executeInputEvents();
      
      
      void setCameraObject(BaseCamera* cam);
      void setViewObject(BaseCamera* vw);
      
      BaseCamera *camera, *view;
      int prev_mouse_x, prev_mouse_y;
      
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
      virtual void evt_pre_step();
      virtual void evt_step();
      virtual void evt_post_step();
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
     * The base-class for camera objects.
     * The base-class from which all camera objects should be derived - in fact, this class is more of an 'interface' in
     * that all of its method implementations are empty (it doesn't really do anything other then force derived classes
     * to have certain methods). A derived camera object should at least override manipulateCamera(), as this
     * method is called at a the very begining of the rendering  process and this makes the camera object uniquely suited
     * for modifying the rendering process based on input or other parameters (for instance changing the angle at which
     * the scene is viewed based on the mouse position). CoreCamera is a class that implements the most common functions
     * for a camera object and it suffices for most uses. When more specialized camera functionality is needed it will be
     * necessary to derive a class from BaseCamera (or perhaps from CoreCamera).
     * @see CoreCamera
     */
    class BaseCamera : public Object{
    public:
      BaseCamera();
      ~BaseCamera();
      
      virtual const char *objectType() const{
	return "BaseCamera";
      }
      
      virtual void manipulateCamera();
    };
    
    
    
    
		
		


    /**
     * A camera object implementing the most common camera functionality.
     * A camera object derived from BaseCamera that implements rudimentary mouse-control of the viewing angle, angle and position locking
     * and convenient camera positioning functions. The CoreCamera object supports various modes:
     * - LOCK_PAN: disable panning (disables panning by clicking and dragging the left mouse button)
     * - LOCK_DISTANCE: disable zooming (disables zooming by holding and dragging both mouse buttons)
     * - LOCK_FIRST_ANGLE: locks the first orientation angle of the camera object (no rotation about the vertical
     * axis of the local coordinate system of the camera when the right mouse button is dragged)
     * - LOCK_SECOND_ANGLE: locks the second orientation angle of the camera object (no rotation about the horizontal
     * axis of the local coordinate system of the camera when the right mouse button is dragged)
     * - LOCK_THIRD_ANGLE: locks the third orientation angle of the camera object (no rotation about the axis running
     * into the screen of the local coordinate system of the camera. This affects the camera's interaction with the mouse only
     * if RMB_CYLINDRICAL_ROTATE is set, in which case the camera won't rotate when the right mouse button is dragged)
     * - FOCUS_FROM_OBJECT: focus the camera on the object set with CoreCamera::setObjectToFollow(...) at every frame.
     * Note that this mode, on its own, does not imply the object's orientation angles are used for the camera
     * - ANGLES_FROM_OBJECT: orient the camera in the same sense as the object set with CoreCamera::setObjectToFollow(...) at every frame.
     * Note that this mode, on its own, does not imply the object's position is used for the camera
     * - RMB_CYLINDRICAL_ROTATE: Dragging the right mouse button will cause the camera to rotate around the axis
     * of the local coordinate system going into the page.
     * - LOCK_POSITION = LOCK_DISTANCE | LOCK_FIRST_ANGLE | LOCK_SECOND_ANGLE | LOCK_THIRD_ANGLE
     * - LOCK_ALL = LOCK_POSITION | LOCK_PAN
     * @see basicCameraObject
     */
    class CoreCamera : public BaseCamera{
    public:
      CoreCamera();
      ~CoreCamera();
      
      virtual const char *objectType() const{
	return "CoreCamera";
      }
      
      void setMode(int new_mode);      
      void setScaleFactors(GLfloat sx, GLfloat sy, GLfloat sz);
      void setRotationButton(int code);
      void setZoomButton(int code);

      void follow(Frame *frame_to_follow);
      Frame *focus();

      void toggleMode(int mode_mask);
      bool modeEnabled(int mode_mask);
      
      void scaleFactors(GLfloat &sx, GLfloat &sy, GLfloat &sz);      
      int rotationButton();
      int zoomButton();
      void scale(GLfloat rx, GLfloat ry, GLfloat rz = 1);

      void lookAt(Vector at_point, GLfloat dist = -1);
      void lookFrom(Vector at_point, Vector from_point);

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
