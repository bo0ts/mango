Extending Mango: Intermediate OS Layers
=======================================

As is explained in the previous section, the core Mango libraries (*mango*) 
are in and of themselves passive; they do not provide any
functionality to create a window or an OpenGL context, initialize
an OpenGL scene, capture keyboard or mouse state or maintain an event loop
that triggers events. Since these tasks naturally involve platform-specific
code they are delegated to an intermediate OS layer, a component that 
provides the necessary functionality.

In this first distribution of Mango, this abstraction is mostly an 
intellectual exercise: at the time of release there are no alternatives to 
mango_on_glut, the intermediate OS layer provided with Mango. Nonetheless, 
it is in keeping with Mango's modular design and its existence should make
the task of embedding or using Mango without GLUT a relatively 
straightforward manner. 

If you wish to develop an additional intermediate OS layer, your best
reference is the mango_on_glut source file which can be found at
*mango_on_glut/src/mango_on_glut.cpp* relative to the root of the
source-code package. Your code will need to accomplish the same tasks,
while also making calls to the global instances *Engine*, *Mouse* and
*Keyboard* in the following situations:

  * call *Engine->setWindowDimensions(...)* if/when the window dimensions
    change.

  * call *Engine->countFrame()* once per frame for Mango to keep track
    of the frame-rate, and *Engine->limitFps()* once per frame if you wish
    Mango to limit the frame rate (if you provide your own frame-limiting
    functionality, you should respect the value returned by 
    *Engine->windowFPS()*)

  * Clear the OpenGL color buffer once per frame if *Engine->cleraBuffer()*
    evaluates to true.

  * Call *Engine->execute*Events()* to executes events for all objects once
    per frame (or at another frequency if such makes sense).

  * Populate the *Mouse* and *Keyboard* global instances with input data from
    the OS.

  * Force fullscreen (or issue an appropriate warning) if 
    *Engine->windowFullscreen()* evaluates to true.


