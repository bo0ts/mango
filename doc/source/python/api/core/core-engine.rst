CoreEngine
==========

.. class:: Core.CoreEngine

   Internally, CoreEngine is the central class in Mango: it keeps track of
   all objects that have events set and is responsible for executing those
   events. There is one instance of CoreEngine available via the global 
   Engine, and it can be used to set various parameters of the simulation.

   .. method:: setWindowDimensions(width, height)

      Sets the dimensions of the window (default to 640x480). Calls to this
      method should execute before the event loop is entered.

   
   .. method:: setWindowFullScreen(is_fullscreen)

      If is_fullscreen is True, Mango will attempt to use an accelerated
      full-screen mode. A windowed mode (the default) will be used otherwise.

   
   .. method:: setWindowFPS(target_framerate)

      Sets the target framerate (default: 60). Calls to this method should
      execute before the event loop is entered.

     
   .. method:: setClearBuffer(clear_buffer)
   
      If clear_buffer is False, the screen won't be cleared between frames
      (this is contrast to the default behavior).

      
   .. method:: setClearColor(r, g, b)

      Set the color used to clear the screen between frames. Defaults to
      black ((0, 0, 0)).

   
   .. method:: windowDimensions()

      Return a tuple (width, height) representing the current window 
      dimensions.


   .. method:: windowFullscreen()

      Returns True if Mango is set to run in full-screen mode, False
      otherwise.

   
   .. method:: windowFps()

      Returns the current target framerate.

      
   .. method::clearBuffer()

      Returns True if Mango is set to clear the buffer between frames, False
      otherwise.

      
   .. method:: actualFps()

      Measures and returns the framerate since the last call to this method.