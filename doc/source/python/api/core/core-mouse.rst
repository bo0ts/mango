CoreMouse
=========


.. class:: Core.CoreMouse
   
   Provides access to mouse state information via the global "Mouse".


   .. method:: down(button_code)

      Returns True if the button represented by button_code is currently
      clicked, False otherwise. Valid button codes are BUTTON_LEFT and
      BUTTON_RIGHT.


   .. method:: state(button_code)

      Returns the state of the button represented by button_code, one of the
      constants BUTTON_STATE_UP or BUTTON_STATE_DOWN

   .. method:: coordinates()

      Returns a tuple (x, y) representing the current coordinates of the
      mouse relative to the top left of the screen.

   .. method:: previousCoordinates()

      Returns a tuple (px, py) representing the coordinates of the mouse
      in the previous frame.

   .. method:: coordinatesDelta()

      Returns a tuple (dx, dy) for which each component is equal to the
      differenfe of the corresponding components in the tuples returned by
      Mouse.coordinates() and Mouse.previousCoordinates()

   .. method:: moved()

      Returns True if the mouse has moved since the last frame, false 
      otherwise

   .. method:: clearMouseMovedFlag()

      Clears the mouse-moved flag, i.e. subsequent calls to Mouse.moved() in
      this frame will return False.