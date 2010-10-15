CoreCamera
==========

.. class:: Core.CoreCamera

   *Inherits from*: :class:`Core.Object`

   An object that represents the user's view onto the scene. Two instances
   are available as globals, Camera (controls the 3D scene) and View 
   (controls the 2D scene).

   .. method:: setMode(new_mode)

      Sets the mode of the camera to new_mode, overwriting the previous
      mode. Valid modes are: 

        * CAMERA_DEFAULT_MODE - left mouse button pans, right mouse button 
          (or 'r' plus left button) rotates aroud focus, left and right
	  simultaneously (or 'z' plus left button) zoom.
	* LOCK_PAN            - prevent panning
	* LOCK_DISTANCE       - prevent zooming
	* LOCK_ALPHA 	      - prevent changes to the first angle 
	  (effectively prevents horizontal rotation of the view when in the 
	  default mode)
	* LOCK_BETA	      - prevent changes to the second angle 
	  (effectively prevents vertical rotation of the view when in the
	  default mode)
	* LOCK_GAMMA          - prevent changes to the third angle
	  (effectively prevents rotation of the view when in the mode
	  RMB_CYLINDRICAL_ROTATE)
	* RMB_CYLINDRICAL_ROTATE - rotation happens around the axis
  	  perpendicular to the screen, rather than around the focus.
	* LMB_DRAG_FOCUS - left mouse button moves the focus, rather than
	  panning the view.
        * LOCK_POSITION - equivalent to LOCK_DISTANCE | LOCK_ALPHA | 
	  LOCK_BETA | LOCK_GAMMA
	* LOCK_ALL - equivalent to LOCK_POSITION | LOCK_PAN				


   .. method:: setScaleFactors(sx, sy, sz)

      Set the scale factors (for each dimensions). This will cause everything
      to be rendered in different proportions.


   .. method:: setRotationButton(rotation_button_code)

      Set a different button to use than 'r' for rotation using the left
      mouse button.


   .. method:: setZoomButton(zoom_button_code)

      Set a different button to use than 'z' for zoom using the left mouse
      button.


   .. method:: follow(frame)

      Set the parent of the camera's focus. This will cause the focus of the
      camera to follow the frame (or object).


   .. method:: focus()

      Returns the frame of reference that is the focus of the camera (same as
      the camera's parent frame)


   .. method:: toggleMode(new_mode)

      Toggles new_mode on or off in the camera's current mode.


   .. method:: modeEnabled(mode)

      Returns True of mode is currently enabled. mode may be an or'ed
      combination of modes.


   .. method:: scaleFactors()

      Returns a tuple (kx, ky, kz) representing the current scale factors
      used by the camera.

   
   .. method:: rotationButton()
   
      Returns the current key-code used for the key-press + left mouse button
      rotation combination (by default ord('r'))

   
   .. method:: zoomButton()

      Returns the current key-code used for the key-press + left mouse button
      zoom combination (by default ord('z'))


   .. method:: scale(kx, ky, kz)

      Multiplies the current scale factors sx, sy, and sz by kx, ky, and kz, 
      respectively.


   .. method:: lookAt(at_point[, distance])

      Moves the focus of the camera to point represented by the vector
      at_point (relative to the global frame). If the optional distance 
      parameter is provided, the camera's zoom is modified so that the camera
      is at a distance equal to that parameter from the focus (the 
      orientation of the camera is maintained).


   .. method:: lookFrom(from_point[, at_point])

      With only one parameter passed, re-orients the camera so that it is
      looking at the same focus but from the point from_point (relative to 
      the focus). When two parameters are passed, the focus is first 
      translated to at_point (interpreted relative to the global frame) and
      then the camera is re-oriented. 
