Embedding Mango
===============

Mango's modular design allows it to be embedded in other C++
applications, with or without support for a scriptable Python
environment. 

In some trivial fashion, every simulation along the lines of those
described in :doc:`/cpp/rapid-simulation-development` is an embedding
of Mango, but that is not exactly the use to which this section is
dedicated. Suppose instead that Mango is just one component of a
larger project, and that *mango-on-glut* is not configurable enough
(or GLUT is not a feasible component altogether). In this case it is
still possible to use Mango, but some additional work may be necessary
for Mango to play nicely with the rest of the program.

The first and most significatn step is to build (or otherwise obtain)
a new intermediate os-layer, as described in
:doc:`/cpp/extending-mango-os-layers`. This new layer should integrate
with Mango and whatever code is used in your program to create a
window, initialize an OpenGL context, interact with the user, and so
on - a more detailed description of this task is available on that
page.

Once this is done, you just need to account for Mango initialization,
finalization, and actual execution of some code to populate a scene
and set events. If no scriptable Python environment is required,
call the following methods somewhere in your program:

  .. code-block:: c++

     // Program initialization...

     Mango::initialize(); 

     // ...
     // Main program body, with some code to create objects, set
     // events, and a loop somewhere in there
     // ...

     // Program finalization...

     Mango::finalize(); 

It doesn't get much simpler, does it? For these purposes you will need
to include *Mango/mango.h* and link against *lib/libmango.a*. 

If a scriptable Python envrionment is desired, use the MangoPy
routines instead:

  .. code-block:: c++

     // Program initialization...

     MangoPy::initialize(argc, argv); 

     // ...
     // Main program body, with a loop somewhere in there
     // Use MangoPy::runScript(<script path>, <true | false>) to execute
     // a script on disk, or PyRun_SimpleString(<code>) to execute a 
     // string as Python code          
     // ...

     // Program finalization...

     MangoPy::finalize(); 
     
Note that *argc* and *argv* must be passed to the
*MangoPy::initialize*. Also, the second argument to MangoPy::runScript
should be true if the path is relative to the directory containing the
Mango executable, and false otherwise (mostly it would be false). 

Not a big price to pay for a scriptable, object-oriented, event-driven
and OpenGL enabled Python environment in your C++ application. Check
out the source code for *mangopy-on-glut*, the Mango executable, at
*mangopy_on_glut/src/mangopy_on_glut.cpp* - it is a basic
implementation of the concepts described here, and it's relative
simplicty should be encouraging. 

To compile/link in this case, include *Mango/mangopy.h* and link
against *lib/libmango.a*, *lib/libmangopy.a*, and the Python library.
