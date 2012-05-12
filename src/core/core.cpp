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
#include <mango/core/core.h>

namespace Mango{
  namespace Core{
				
    /*
      Class Object
    */
		
    /* Static Members */
		
    int Object::nextObjectTypeId = 0;
			       
		
    /**
     * Creates an Object.
     */
    Object::Object():Frame(){
      // Check that a global Engine object has been created
      requirePresenceOfEngine(objectType(), "Object()");
      requirePresenceOfGlobalFrame(objectType(), "Object()");
      
      // Add the object to the global Engine
      ID = -1;
      ID = Engine->addObject(this);
			
      is_visible = true;
		
      for (int i = 0; i < ENGINE_MAX_EVENT_TYPES; i += 1){
	event_indices[i] = -1;
      }
      events = 0;
    }
		
    void Object::__printEventIndices__(){
      for (int i = 0; i < ENGINE_MAX_EVENT_TYPES; i += 1){
	std::cout << event_indices[i] << std::endl;
      }
      std::cout << std::endl << std::endl;
    }
		
    /**
     * Removes the Object from the engine's list.
     */
    Object::~Object(){
      removeObjectFromEngineAndBOCs();
    }
		    
    void Object::removeObjectFromEngineAndBOCs(){
      if (ID > -1 && Engine != NULL){
	Engine->removeObject(ID);
      }

      std::vector<ObjectContainerRecord>::iterator bocRecord;
		
      int current_BOCT_ID = 0;
      for( bocRecord = objectContainers.begin(); bocRecord != objectContainers.end(); bocRecord++){
	current_BOCT_ID += 1;
	if ((*bocRecord).second != NULL){
	  (*bocRecord).second->removeObject(this, current_BOCT_ID);
	}
      }
    }
		
	
    bool Object::toggleVisibility(){
      is_visible = !is_visible;
      return is_visible;
    }
	
    void Object::setVisible(bool should_be_visible){
      is_visible = should_be_visible;
    }
		
    bool Object::visible(){
      return is_visible;
    }
		
    /**
     * Cause the object to execute the event(s) described by an OR'ed
     * bitmask of event constants. Currently supported events are:     
     * - STEP
     * - RENDER
     * - DRAW
     * - INPU
     *
     * @return 
     *   true on success, false on failure
     *
     * @see unset
     * @see executes
     * @see toggle
     */
    bool Object::set(int event_type){
      return Engine->setEvent(this, event_type);
    }
		
    /**
     * Cause the object not to execute the event(s) described by an
     * OR'ed bitmask of event constants. For a list of supproted
     * events see Object::set.
     *
     * @return               true on success, false on failure
     *
     * @see set
     * @see executes
     * @see toggle
     */
    bool Object::unset(int event_type){
      return Engine->removeEvent(this, event_type);
    }
		
    /**
     * Return true if the object executes the event described by
     * event_type, false otherwise. If event_type is an ORed bitmask
     * of event constants, the return value is true if all of them are
     * set and false if at least one isn't.
     *
     * @see set
     * @see unset
     * @see toggle
     */
    bool Object::executes(int event_type){
      return Engine->objectHasEvent(this, event_type);	
    }
		
    /**
     * Inverts the state of execution of the event(s) described by the
     * OR'ed bitmask of event constants event_type, causing each
     * individual event to be executed if it is not currently being
     * executed or not to be executed if it is currently being
     * executed.
     *
     * @see set
     * @see executes
     * @see unset
     */
    void Object::toggle(int event_type){
      Engine->toggleEvent(this, event_type);
    }
		
		
    void Object::setObjectID(int new_objectID){
      ID = new_objectID;
    }
								
    int Object::objectID(){
      return ID;
    }
				
	
    /* Dynamic Methods */
		
    /**
     * The render event callback function. This callback method is
     * called each frame for objects whose render event is set, and
     * can be used to render graphics in a perspective projection;
     * override this method in derived classes to customize how the
     * object is rendered.  Note that the object's local coordinate
     * system is NOT enforced by the engine! This means that you must
     * call transform() before rendering if you wish to render with
     * respect to the local coordinate system. Use openGL functions
     * for rendering. The openGL library is guaranteed to be
     * available but no other extensions are (you will have to include
     * them yourself if you want to use them).
     */
    void Object::render(){
      // skip
    }

    /**
     * The draw event callback function. This callback method is
     * called each fram for objects whose draw event is set, and can
     * be used to render graphics in orthographic projection; override
     * this method in derived classes to customize how the object is
     * rendered.  Note that the object's local coordinate system is
     * NOT enforced by the engine! This means that you must call
     * transform() before rendering if you intend to render with
     * respect to the local coordinate system. Use openGL functions.
     * The openGL library is guaranteed to be available but no other
     * extensions are (you will have to include them yourself if you
     * want to use them).
     */
    void Object::draw(){
      // skip
    }
		
		
    /**
     * The step event callback function. This callback method is
     * called each frame for objects whose step event has been set.
     * This event is appropriate for object "logic".
     */
    void Object::step(){
      // skip
    }
		
		
    /**
     * The input event callback function. When input events are
     * enabled, this callback method is called when a keyboard or
     * mouse key has been pressed or released, for those objects whose
     * input event has been set.
     *
     * @param &event   
     *   an InputEvent instance representing the event that occurred
     */
    void Object::input(inputEvent &event){
      // skip
    }



















		
		
		
		
		
		
    /*
      Engine Object
    */
		
    /* Constructors, Destructors */
		
    /**
     * Create a CoreEngine. The default window settings are 60 FPS,
     * windowed mode with dimensions 640x480. A CoreEngine instance is
     * passive insofar as enforcing these settings - it is a
     * placeholder for the information. It is the job of an
     * intermediate os layer to query these settings and apply them,
     * or update them with correct values if the default ones are
     * incorrect.
     */
    CoreEngine::CoreEngine(){
      for (int i = 0; i < ENGINE_MAX_EVENT_TYPES; i += 1){
	events[i].reserve(ENGINE_INIT_EVENTS_STACK);
      }
		
		
      // Window Properties
      setWindowDimensions(640, 480);
      setWindowFullscreen(0);
      setClearBuffer(1);
      setWindowFps(60);
		    
      // Initialize member pointers
      camera = NULL;
      view = NULL;

      // Initialize Fps members
      last_render_time = elapsed_time_in_milliseconds();
      frame_count = 0;
    }
		
    /**
     * Deletes all objects that have been registered with the engine.
     */
    CoreEngine::~CoreEngine(){
      objects.clear();
    }
		
		
		
    /* Object Methods */

    /**
     * Adds an object to the engine's list of objects. This sets the
     * object's CoreEngine *engine member pointer to this engine
     * (until this is done that pointer is NULL and should not be
     * used) and assigns it an ID. Every object MUST be added before
     * it is set to have event callback (in general, this happens
     * automatically in an Object's constructor). 
     *
     * @return objectID   the object's assigned ID, or -1 on failure.
     */
    int CoreEngine::addObject(Object* object){
      objects.push_back(object);
      return objects.size() - 1;
    }
		
    /**
     * Returns a pointer to a the Object with the given ID, or NULL on
     * failure
     */
    Object* CoreEngine::object(int objectID){
      return objects[objectID];
    }
		
    /**
     * Remove an object from the engine's list of objects based on
     * ID. Returns a pointer to the object that was removed. If no
     * object with the given ID exists the return value will be NULL.
     */
    Object* CoreEngine::removeObject(int objectID){
      Object* discarded_object;
      if (objectID < 0){
	throw Error(objectType(), "removeObject", "object ID cannot be negative");
      }
      if (objectID >= objects.size()){
	throw Error(objectType(), "removeObject", "object ID larger than internal object vector");	
      }
	    	
      removeEvent(objects[objectID], ALL_EVENTS);
      int s = objects.size();
      discarded_object = objects[objectID];
      objects[objectID] = objects[s-1];
      objects[objectID]->ID = objectID;		
      objects.pop_back();
      return discarded_object;
    }
		
												
    /* Event Methods */
		
    /**
     * Set event(s) for an object based on a OR'ed bitmask of event
     * constants. Objects that are set to have events trigerred for
     * them should be added to the engine prior to this call using
     * CoreEngine::addObject()  (Normally this is done automatically
     * in the Object default constructor).  Note that the engine
     * will trigger a particular event for all objects for which the
     * event is set only when CoreEngine::executeEvent() is called
     * (this is only of relevance when implementing an intermediate
     * layer to interact with the operating system).  Currently
     * supported events are: RENDER, DRAW, STEP, INPUT.
     *
     * @return true on success, false on failure
     *
     * @see setEvent
     * @see removeEvent
     * @see toggleEvent
     * @see objectHasEvent
     */
    bool CoreEngine::setEvent(Object* object, int event_type){
      if (object == NULL){
	throw ValueError(objectType(), "setEvent", "first argument cannot be NULL");
      }
		
      int j = 1; // j is the event_type, corresponds to constants defined in e3_constants.h
      for (int i = 0; i < ENGINE_MAX_EVENT_TYPES; i += 1){
	if (((event_type & j) == j) && (object->event_indices[i] == -1)){
	  events[i].push_back(object);
	  object->events = object->events | j;
	  object->event_indices[i] = events[i].size()-1;
	}
	j = j << 1;
      }
      return true;
    }
		
    /**
     * Removes event(s) set for an object, based on an OR'ed bitmask
     * of event constants. Removing an event that was never set for an
     * object simply does nothing.
     *
     * @return              true on success, false on failure.
     *
     * @see setEvent
     * @see toggleEvent
     * @see objectHasEvent
     */
    bool CoreEngine::removeEvent(Object* object, int event_type){
      if (object == NULL){
	throw ValueError(objectType(), "removeEvent", "first argument cannot be NULL");
      }
		
      int j = 1; // j is the event_type, corresponds to constants defined in constants.h
      for (int i = 0; i <= ENGINE_MAX_EVENT_TYPES; i += 1){
	if (((event_type & j) == j) && (object->event_indices[i] > -1)){
	  events[i][object->event_indices[i]] = events[i][events[i].size()-1];
	  events[i].pop_back();
	  object->event_indices[i] = -1;
	  object->events = object->events & (~j);
	}
	j = j << 1;
      }
      return true;
    }
		
    /**
     * Modifies the event(s) for an object based on a OR'ed bitmask of
     * event constants. If the object's event was set it is unset, and
     * if it was unset it is set
     *
     * @return                   true on success, false on failure
     *
     * @see setEvent
     * @see removeEvent
     * @see objectHasEvent
     */
    bool CoreEngine::toggleEvent(Object* object, int event_type){
      if (object == NULL){
	throw ValueError(objectType(), "setEvent", "first argument cannot be NULL");
      }
		
      int j = 1; // j is the event_type, corresponds to constants defined in constants.h
      for (int i = 0; i < ENGINE_MAX_EVENT_TYPES; i += 1){
	if ((event_type & j) == j){
	  // If the object has no event set, set one
	  if (object->event_indices[i] == -1){
	    events[i].push_back(object);
	    object->events = object->events | j;
	    object->event_indices[i] = events[i].size()-1;
	  }
	  // Otherwise it has one, unset it
	  else {
	    events[i][object->event_indices[i]] = events[i][events[i].size()-1];
	    events[i].pop_back();
	    object->event_indices[i] = -1;
	    object->events = object->events & (~j);
	  }
	}
	j = j << 1;
      }
      return true;
    }
		
    /**
     * Check if the event described by event_type is set for the given
     * object. Returns true if it is and false otherwise. If
     * event_type is a mask of events, the return value is true if all
     * of them are set and false otherwise (i.e. it is false even if
     * only one is unset).
     *
     * @return                   
     *   true if all events descrbed by the bit mask are now set, 
     *   false otherwise
     *
     * @see setEvent
     * @see removeEvent
     * @see toggleEvent
     */
    bool CoreEngine::objectHasEvent(Object* object, int event_type){
      if (object == NULL){
	throw ValueError(objectType(), "setEvent", "first argument cannot be NULL");
      }
		
      return ((object->events & event_type) == event_type);
    }
					
		
		
    /**
     * Execute the step event for all objects set to have that event.
     * The order in which the events are executed for individual
     * objects is not necessarily in the order in which they were
     * added.
     *
     * @see executeRenderEvents()
     * @see executeDrawEvents()
     * @see executeInputEvents()
     */
    void CoreEngine::executeStepEvents(){
      evt_step();
    }
		
		
    /**
     * Executes the render event for all objects set to have that
     * event. The render events of distinct objects do not interact
     * via the OpenGL state machine. The order in which the events are
     * executed for individual objects is not necessarily in the order
     * in which they were added.
     *
     * @see executeStepEvents()
     * @see executeDrawEvents()
     * @see executeInputEvents()
     */
    void CoreEngine::executeRenderEvents(){
      evt_render();
    }
		
    /**
     * Executes the draw event for all objects set to have that event.
     * The order in which the events are executed for individual
     * objects is not necessarily in the order in which they were
     * added.
     *
     * @see executeStepEvents()
     * @see executeRenderEvents()
     * @see executeInputEvents()
     */
    void CoreEngine::executeDrawEvents(){
      evt_draw();
    }
		
    /**
     * Executes the input event for all objects set to have that
     * event.  The order in which the events are executed for
     * individual objects is not necessarily in the order in which
     * they were added.  
     *
     * @see executeStepEvents() 
     * @see executeRenderEvents() 
     * @see executeDrawEvents()
     */
    void CoreEngine::executeInputEvents(){
      evt_input();
    }
				
		
    /**
     * Set the camera object of the engine. The camera object should
     * be a derived class of BaseCamera that overrides
     * BaseCamera::manipulateCamera(). This method is called at a
     * particular point during the rendering process that makes the
     * camera object uniquely suited for modifying the rendering
     * process based on input or other parameters (for instance
     * changing the angle at which the scene is viewed based on the
     * mouse position). CoreCamera is a class that implements some
     * common functions for a camera object.
     */
    void CoreEngine::setCameraObject(BaseCamera* cam){
      camera = cam;
    }
		
    /**
     * Set the view object of the engine. Mango renders two scenes, a
     * 2-dimensional one suprimposed ontop of a 3-dimensional one, and
     * the view is the "camera" object for the 2d scene. The view
     * object should be a derived class of BaseCamera that overrides
     * BaseCamera::manipulateCamera(). This method is called at a
     * particular point during the drawing process that makes the
     * view uniquely suited for modifying the scene
     * based on input or other parameters (for instance changing the
     * angle at which the scene is viewed based on the mouse
     * position). CoreCamera is a class that implements the most
     * common functions for a view object.
     */
    void CoreEngine::setViewObject(BaseCamera* vw){
      view = vw;
    }
		
		
    void CoreEngine::evt_render(){
      std::vector<Object*>::iterator current_object;
      glEnable(GL_LIGHTING);

      // If we have a camera, let it do its thing
      if (camera != NULL){
	camera->manipulateCamera();
      }
		
      for (current_object = events[EVT_TYPE_RENDER].begin(); current_object < events[EVT_TYPE_RENDER].end(); current_object++){
	glPushMatrix();
	(*current_object)->render();
	glPopMatrix();
      }
    }
		
		
    void CoreEngine::evt_draw(){						
      // Set up an orthographic projection
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();
      glOrtho(0.0f, window_width, 0.0f, window_height, -1.0f, 1.0f);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glDisable(GL_LIGHTING);
      glClear(GL_DEPTH_BUFFER_BIT);

      // If we have a view, let it do its thing
      if (view != NULL){
	view->manipulateCamera();
      }
		
      std::vector<Object*>::iterator current_object;
		
      for (current_object = events[EVT_TYPE_DRAW].begin(); current_object < events[EVT_TYPE_DRAW].end(); current_object++){
	glPushMatrix();
	(*current_object)->draw();
	glPopMatrix();
      }
		
		
      // Restore the perspective projection
      glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      glMatrixMode(GL_MODELVIEW);
    }
		
		

		
		
    void CoreEngine::evt_step(){
      std::vector<Object*>::iterator current_object;
		
      for (current_object = events[EVT_TYPE_STEP].begin(); current_object < events[EVT_TYPE_STEP].end(); current_object++){
	(*current_object)->step();
      }
    }
		
		
		
		
    void CoreEngine::evt_input(){
      std::vector<Object*>::iterator current_object;
      std::deque<inputEvent>::iterator current_event;

      for (current_event = Keyboard->eventBuffer.begin(); current_event < Keyboard->eventBuffer.end(); current_event ++){		      	       		     
	for (current_object = events[EVT_TYPE_INPUT].begin(); current_object < events[EVT_TYPE_INPUT].end(); current_object++){
	  (*current_object)->input((*current_event));
	}
      }	  
      Keyboard->eventBuffer.clear();

      for (current_event = Mouse->eventBuffer.begin(); current_event < Mouse->eventBuffer.end(); current_event ++){		      	       		     
	for (current_object = events[EVT_TYPE_INPUT].begin(); current_object < events[EVT_TYPE_INPUT].end(); current_object++){
	  (*current_object)->input((*current_event));
	}
      }
      Mouse->eventBuffer.clear();
    }


    /* Window Settings Methods */
		
    /**
     * Set the width and height of the window, in pixels. Changes to
     * these dimensions are meaningful only if made before window
     * intialization is performed.
     *
     * @see windowDimensions
     * @see windowHeight
     * @see windowWidth
     */
    void CoreEngine::setWindowDimensions(int width, int height){
      if (width <= 0 || height <= 0){
	throw ValueError(objectType(), "setWindowDimensions", "both window dimensions must be positive");
      }
		
      window_width = width;
      window_height = height;
    }
		
    /**
     * Set the window full screen mode (the default is windowed
     * mode). Changes to this value are meaningful only if made before
     * window intialization is performed. 
     *
     * @param mode      false for windowed, true for fullscreen
     *
     * @see windowFullscreen
     */
    void CoreEngine::setWindowFullscreen(bool mode){
      full_screen_mode = mode;
    }
		
    /**
     * Set the maximum number of frames-per-second used to render the
     * scene (the default is 60). The actual FPS may be less if the
     * rendering is slow.  Changes to this value are meaningful only
     * if made before window intialization is performed. 
     *
     * @see windowFps
     */
    void CoreEngine::setWindowFps(int fps){
      if (fps <= 0){
	throw ValueError(objectType(), "setWindowFps", "desired fps must be positive");
      }
		
      desired_fps = fps;
      milliseconds_per_frame = round(1000.0 / desired_fps);
    }
		
    /**
     * Set whether the buffer should be cleared at the beginning of
     * every frame. The clear color defaults to black.
     *
     * @see setClearColor
     * @see clearColor
     * @see clearBuffer
     */
    void CoreEngine::setClearBuffer(bool should_clear){
      clear_buffer = should_clear;
    }
		
    /**
     * Set the color that is used to clear the buffer every
     * frame. Defaults to black. Color components should be 
     * between 0 and 1.
     *
     * @see setClearBuffer
     * @see clearColor
     */
    void CoreEngine::setClearColor(GLfloat cl_r, GLfloat cl_g, GLfloat cl_b){
      glClearColor(cl_r, cl_g, cl_b, 0.0);
    }
		
    /**
     * Retrieve the window dimensions (in pixels) by assigning them to
     * two integer variables passed by reference.
     *
     * @see setWindowDimensions
     * @see windowWidth
     * @see windowHeight
     */
    void CoreEngine::windowDimensions(int &width, int &height){
      width = window_width;
      height = window_height;
    }
		
    /**
     * Returns the window's width in pixels.
     *
     * @see setWindowDimensions
     * @see getWindowDimensions
     * @see windowHeight
     */
    int CoreEngine::windowWidth(){
      return window_width;
    }
		
    /**
     * Returns the window's height in pixels.
     *
     * @see setWindowDimensions
     * @see getWindowDimensions
     * @see windowWidth
     */
    int CoreEngine::windowHeight(){
      return window_height;
    }
		
    /**
     * Returns the window's fullscreen mode (true if in fullscreen,
     * false if windowed).
     *
     * @see setWindowFullscreen
     */
    bool CoreEngine::windowFullscreen(){
      return full_screen_mode;
    }
		
    /**
     * Returns the desired FPS.
     *
     * @see setWindowFPS
     */
    int CoreEngine::windowFps(){
      return desired_fps;
    }
		
    /**
     * Returns true if the buffer is set to be cleared every frame.
     *
     * @see setClearBuffer
     * @see clearColor
     * @see setClearColor
     */
    bool CoreEngine::clearBuffer(){
      return clear_buffer;
    }
		
    /**
     * Retrieve the color that is used to clear the buffer every frame
     * by assigning it to cl_r, cl_g, cl_b and cl_alpha
     *
     * @see setClearBuffer
     * @see clearBuffer
     * @see setClearColor
     */
    void CoreEngine::clearColor(GLfloat &cl_r, GLfloat &cl_g, GLfloat &cl_b){
      GLfloat clear_colors[4];
      glGetFloatv(GL_COLOR_CLEAR_VALUE, clear_colors);
      cl_r = clear_colors[0];
      cl_g = clear_colors[1];
      cl_b = clear_colors[2];
    }
		
    /**
     * Limit the frame rate, by sleeping for an amount of milliseconds
     * appropriate for maintaining the current desired FPS     
     */
    void CoreEngine::limitFps(){
      int now, time_taken;
      float dt;

      now = elapsed_time_in_milliseconds();
      time_taken = now - last_render_time;
      if (time_taken < milliseconds_per_frame - 1){
	dt = (milliseconds_per_frame - time_taken - 1) / 1000.0;
	seconds_sleep(dt);
      }
      last_render_time = elapsed_time_in_milliseconds();
    }

    /**
     * Count the current frame. This method should be called once per
     * frame if actualFps() is to return any meaningful results (this
     * is generally done by the intermediate os layer; mango-on-glut
     * does).
     */
    void CoreEngine::countFrame(){      
      frame_count += 1;
    }

    /**
     * Return the average FPS acheived. For the value returned by this method
     * to have any meaning, countFrame() should be called every frame.
     */
    double CoreEngine::actualFps(){
      int now, dt;

      if (frame_count > 60){
	now = elapsed_time_in_milliseconds();
	dt = now - last_fps_calc;
	actual_fps = 1000 * (float)frame_count / (float)dt;
	last_fps_calc = now;
	frame_count = 0;
      }

      return actual_fps;
    }



		
		




				
    /* 
       BaseCamera Methods 
    */
		
    /**
     * BaseCamera constructor, an empty method.
     */
    BaseCamera::BaseCamera() : Object(){
    }
		
    /**
     * BaseCamera destructor, an empty method.
     */
    BaseCamera::~BaseCamera(){
    }
		
    /**
     * A pre-render event method trigerred before the render events
     * for all objects (assuming that the object is set as the CoreEngine's
     * camera object). Derived classes should override this
     * method to specialize camera object functionality.
     */
    void BaseCamera::manipulateCamera(){
      // pass
    };					
		
		









		
    /*
      CoreCamera
    */
		
    /**
     * CoreCamera constructor. Initializes the CoreCamera to the
     * default mode allowing generic 3D-scene navigation.
     */
    CoreCamera::CoreCamera():BaseCamera(){
      requirePresenceOfMouse(objectType(), "CoreCamera");

      mode = CAMERA_DEFAULT_MODE;      
      focus_frame = new Frame();
      Vector z1(0.0, 1.0, 0.0);
      Vector z2(1.0, 0.0, 0.0);
      Vector z3(0.0, 0.0, 1.0);
      focus_frame->setOrientationAxes(z1, z2, z3);
      setParentFrame(focus_frame);
      prev_mouse_x = 0;
      prev_mouse_y = 0;
      scale_x = 1.0;
      scale_y = 1.0;
      scale_z = 1.0;
      rotate_camera_button_code = 114; // 'r'
      zoom_camera_button_code = 122; // 'z'
    }
		
    /**
     * CoreCamera destructor.
     */
    CoreCamera::~CoreCamera(){
      delete focus_frame;
    }
					
    /**
     * Set the camera mode. See CoreCamera for a detailed description
     * of the different modes.
     *
     * @see CoreCamera
     * @see modeEnabled
     */
    void CoreCamera::setMode(int new_mode){
      mode = new_mode;
    }
		
    /**
     * Set the scale factors for the camera, in each axis
     * independently. These are used to glScale the scene before
     * rendering.
     *
     * @see scaleFactors
     * @see scale
     */
    void CoreCamera::setScaleFactors(GLfloat sx, GLfloat sy, GLfloat sz){
      if ((sx == 0) || (sy == 0) || (sz == 0)){
	throw ValueError(objectType(), "setScaleFactors", "Scale factors must be nonzero");
      }
      scale_x = sx;
      scale_y = sy;
      scale_z = sz;
    }	       
		
    void CoreCamera::setRotationButton(int code){
      rotate_camera_button_code = code;
    }

    void CoreCamera::setZoomButton(int code){
      zoom_camera_button_code = code;
    }

    /**
     * Return the focus frame of the camera. This is the frame of reference
     * that a CoreCamera is always pointing at. 
     */
    Frame *CoreCamera::focus(){
      return focus_frame;
    }

    
    /**
     * Set the parent frame of the focus frame of the camera. This has
     * the effect that the camera "follows" the given frame. 
     */
    void CoreCamera::follow(Frame *frame_to_follow){
      focus_frame->setParentFrame(frame_to_follow);
    }

    /**
     * Toggle a camera mode on or off
     */
    void CoreCamera::toggleMode(int mode_mask){
      mode = (mode ^ mode_mask);
    }

    /**
     * Check if the given camera mode is enabled
     */
    bool CoreCamera::modeEnabled(int mode_mask){
      return ((mode & mode_mask) == mode_mask);
    }

    /**
     * Retrieve the scale factors for the camera by assigning them to
     * the GLfloats sx, sy, sz that are passed by reference.
     *
     * @see setScaleFactors
     * @see scale
     */
    void CoreCamera::scaleFactors(GLfloat &sx, GLfloat &sy, GLfloat &sz){
      sx = scale_x;
      sy = scale_y;
      sz = scale_z;
    }


    int CoreCamera::rotationButton(){
      return rotate_camera_button_code;
    }

    int CoreCamera::zoomButton(){
      return zoom_camera_button_code;
    }
		
    /**
     * Scale the current scale factors by rx, ry, rz. This has the
     * effect of multiplying the camera's x scale-factor by rx, the y
     * scale-factor by ry and the z scale-factor by rz.
     *
     * @see setScaleFactors
     * @see scaleFactors
     */
    void CoreCamera::scale(GLfloat rx, GLfloat ry, GLfloat rz){
      if ((rx == 0) || (ry == 0) || (rz == 0)){
	throw ValueError(objectType(), "scale", "Cannot scale by 0");
      }
      scale_x = scale_x*rx;
      scale_y = scale_y*ry;
      scale_z = scale_z*rz;
    }
			
	
    // look* Functions
		
    /**
     * Position and orient the camera so as to be pointing at a
     * particular point from a given distance.
     *
     * @see lookFrom
     */
    void CoreCamera::lookAt(Vector at_point, GLfloat dist){
      if (dist > 0){
	Vector v(0, 0, dist);
	position = v;
      }
      focus_frame->position = at_point;
    }

    /**
     * Position and orient the camera so that it is looking from one
     * point at another point.
     *
     * @see lookAt
     */
    void CoreCamera::lookFrom(Vector from_point, Vector at_point){
      focus_frame->position = at_point;
      lookFrom(from_point);
    }

    /**
     * Move the camera to a given position, but reorient it so that
     * the position it is pointing at does not change.
     *
     * @see lookAt
     */
    void CoreCamera::lookFrom(Vector from_point){
      GLfloat alef, bet;
      Vector v(0, 0, from_point.norm());
      position = v;
      focus_frame->orientationFor(from_point, alef, bet);
      focus_frame->setOrientation(alef, bet - 90, 0);
    }
				
    /**
     * Parses the input necessary to control the camera and sets the
     * appropriate internal variables.
     */
    void CoreCamera::step(){
      int mouse_x, mouse_y;
      int mdx, mdy;
      int window_width, window_height, window_mid_x, window_mid_y;
      GLfloat dx, dy, dz, dalpha, dbeta, dgamma;
      dx = 0;
      dy = 0;
      dz = 0;
      dalpha = 0;
      dbeta = 0;
      dgamma = 0;
      
      if (!modeEnabled(LOCK_ALL)){
	Mouse->coordinates(mouse_x, mouse_y);
	Engine->windowDimensions(window_width, window_height);
		
	mdx = mouse_x - prev_mouse_x;
	mdy = mouse_y - prev_mouse_y;
		
	window_mid_x = (int)round(window_width / 2);
	window_mid_y = (int)round(window_height / 2);
		
		
	if ((Mouse->down(BUTTON_RIGHT) || (Mouse->down(BUTTON_LEFT) && Keyboard->down(zoom_camera_button_code))) && Mouse->down(BUTTON_LEFT)){	  
	  if (modeEnabled(ZOOM_SCALES)){
	    float d_scale = mdy / 25.0f;
	    scale_x -= d_scale;
	    scale_y -= d_scale;
	    scale_x = (scale_x < 0.1 ? 0.1 : scale_x);
	    scale_y = (scale_y < 0.1 ? 0.1 : scale_y);
	  }
	  else{
	    dz += (mdx + mdy) / 20.0f;
	  }
	}
	else if (Mouse->down(BUTTON_RIGHT) || (Mouse->down(BUTTON_LEFT) && Keyboard->down(rotate_camera_button_code))){
	  if (modeEnabled(RMB_CYLINDRICAL_ROTATE)){
	    // If the mouse is to the left of the center of the screen, we have a problem b/c atan2 
	    // is discontinuous there whenever y crosses the real line. The solution: if we're on the left, 
	    // reflect the x coordinate, then reflect the resulting angle
	    int reflection = ((mouse_x - window_mid_x) > 0 ? 1 : -1);
	    dgamma = reflection *(atan2(mouse_y-window_mid_y + mdy, reflection * (mouse_x-window_mid_x + mdx)) - atan2(mouse_y - window_mid_y, reflection*(mouse_x-window_mid_x)))*100;
	  }
	  else{
	    dalpha -= (mdx * 180.0f) / 500.0f;
	    dbeta -= (mdy * 180.0f) / 500.0f;	    
	  }
	}
	else if (Mouse->down(BUTTON_LEFT)){
	  float scale = (modeEnabled(RMB_CYLINDRICAL_ROTATE) ? 1.0f : 50.0f) * ((scale_x + scale_y)/2.0f);
	  dx -= (mdx/scale);
	  dy += (mdy/scale);
	}
		
	dalpha = (modeEnabled(LOCK_ALPHA) ? 0 : dalpha);
	dbeta = (modeEnabled(LOCK_BETA) ? 0 : dbeta);
	dgamma = (modeEnabled(LOCK_GAMMA) ? 0 : dgamma);
	dx = (modeEnabled(LOCK_PAN) ? 0 : dx);
	dy = (modeEnabled(LOCK_PAN) ? 0 : dy);
	dz = (modeEnabled(LOCK_DISTANCE) ? 0 : dz);
		
		
	if (modeEnabled(RMB_CYLINDRICAL_ROTATE) || modeEnabled(LMB_DRAG_FOCUS)){
	  Vector vdx, vdy;
	  Matrix rotation = focus_frame->rotationToParent();
	  vdx = rotation.transform(Vector(dx, 0, 0));
	  vdy = rotation.transform(Vector(0, dy, 0));
	  focus_frame->translate(vdx);
	  focus_frame->translate(vdy);
	  translate(0, 0, dz);
	}
	else{
	  translate(dx, dy, dz);
	}

	focus_frame->rotate(dalpha, dbeta, dgamma);
			
	prev_mouse_x = mouse_x;
	prev_mouse_y = mouse_y;
      }
		      
    }
		
    /**
     * Translates and rotates the point from which the scene is
     * viewed, in accordance with input from the mouse and the set
     * camera mode.
     */
    void CoreCamera::manipulateCamera(){
      glScalef(scale_x, scale_y, scale_z);
                  
      reverseTransform();	
    }

  } // End namespace Core

  Core::CoreEngine *Engine;
  Core::CoreKeyboard *Keyboard;
  Core::CoreMouse *Mouse;
  Core::CoreCamera *Camera;
  Core::CoreCamera *View;
  Core::Frame *GlobalFrame;

  /**
   * Throw a Core::EnvironmentError if no global Engine has been initialized.
   */
  void requirePresenceOfEngine(const char *object, const char *method){
    if (Engine == NULL){
      throw Core::EnvironmentError(object, method, "Global variable Mango::Engine is NULL");
    }
  }

  /**
   * Throw a Core::EnvironmentError if no global frame has been initialized.
   */
  void requirePresenceOfGlobalFrame(const char *object, const char *method){
    if (GlobalFrame == NULL){
      throw Core::EnvironmentError(object, method, "Global variable Mango::GlobalFrame is NULL");
    }
  }

  /**
   * Throw a Core::EnvironmentError if no global keyboard has been initialized.
   */
  void requirePresenceOfKeyboard(const char *object, const char *method){
    if (Keyboard == NULL){
      throw Core::EnvironmentError(object, method, "Global variable Mango::Keyboard is NULL");
    }
  }

  /**
   * Throw a Core::EnvironmentError if no global mouse has been initialized.
   */
  void requirePresenceOfMouse(const char *object, const char *method){
    if (Mouse == NULL){
      throw Core::EnvironmentError(object, method, "Global variable Mango::Mouse is NULL");
    }
  }

  /**
   * Throw a Core::EnvironmentError if no global camera has been initialized.
   */
  void requirePresenceOfCamera(const char *object, const char *method){
    if (Camera == NULL){
      throw Core::EnvironmentError(object, method, "Global variable Mango::Camera is NULL");
    }
  }

  /**
   * Throw a Core::EnvironmentError if no global view has been initialized.
   */
  void requirePresenceOfView(const char *object, const char *method){
    if (View == NULL){
      throw Core::EnvironmentError(object, method, "Global variable Mango::View is NULL");
    }
  }


} // End namespace Mango
