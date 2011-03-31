Strucure of Framework
=====================

Mango is intended to be a modular framework, with serveral components that 
are designed with each other in mind but nonetheless may be useful 
independently. The names of these components are:

  * mango *(core libraries, not to be confused with the binary of the 
    same name)*
  * mango_on_glut
  * mangopy
  * geometry
  * pygeometry

Putting all of these components together results in the binary that runs 
simulations written in Python, while leveraging Mango to build simulations
in C++ as descried in ":doc:`rapid-simulation-development`" uses only the
components mango, geometry and mango_on_glut. Descriptions of each of these
components follow.


Mango *(Core Libraries)*
------------------------

The Mango core libraries are refferred to simply as 'mango' in the rest of
this section. They define several classes in C++ (encompassed in the 
namespaces Mango::Core and Mango::Draw) that implement object-tracking, 
event registration and event dispatching mechanisms. mango's only dependency 
is OpenGL, and it can (theoretically) be used in any OpenGL application to
encapsulate behaviors in objects (by overriding events in derived classes)
and design scenes by creating instances of these objects and setting events
for them. 

mango also defines keyboard and mouse abstractions that are designed to be
populated with keyboard and mouse state/events by some agent interacting with
the OS (otherwise, in and of themselves, they are passive).

mango does not: create a window with or without an OpenGL context, initialize
an OpenGL scene, capture keyboard or mouse state or maintain an event loop
that triggers events (even for objects it is tracking). These tasks are 
delegated to a different component, one that interacts with the OS and
maintains the event loop.


Mango-On-Glut *(OS layer)*
--------------------------

mango_on_glut is the component that accomplishes the above mentioned tasks
that require interaction with the OS (some of them do, anyway): create a
window, initialize an OpenGL scene, capture user input and maintain an event
loop. This is done by leveraging GLUT, hence the name mango_on_glut (the
naming is borrowed from "Ruby on Rails", of course).

Because the role of this component is a supporting one and GLUT does almost
all of the hard work, its complexity is quite limited: it provids 
initialization routines that set up the GLUT environment (not too different 
from what you would find in most GLUT tutorials), keyboard and mouse 
GLUT-callbacks that populate the keyboard and mouse abstractions (voluminous 
but simple code), and it triggers events from the appropriate GLUT-callbacks.

By using mango_on_glut and mango, simulations can be built in C++ just as in
the previous section. It should be a straightforward matter to create 
equivalent OS-layers (for lack of a better name) that accomplish the same 
tasks but use a library other than GLUT, perhaps a cross-platform GUI like 
WxWidgets. In the event that an enterprising developer ever implements such 
an OS-layer, it can be hoped that they will name it 'mango_on_wxwidgets' and 
that it will be easily swappable with mango_on_glut.

The dependencies of mango_on_glut are mango, OpenGL and GLUT.



MangoPy
-------

Mangopy is a port of mango (the core libraries) to Python. This port has been
coded "manually", without the use of tools such as SWIG or Boost, and it 
contains several optimizations over what a naive "port" would look like
(whether or not it is accomplished with the use of automatic tools).

Mangopy leverages the Python C API to establish a Python environment that
also contains a mango environment, and furthermore this mango environment is
accessible from any scripts run in the initialized Python envrionment. That 
is to say, if a script is run in the Python environment provided by Mangopy
that script has full access to the Python Mango API.

Mangopy depends on mango, OpenGL and Python. It does *not* depend on 
mango_on_glut and in fact is completely independent of it. Mangopy and mango
can be embedded in any OpenGL C++ app to provide an object-oriented, event
based, Python-scriptable environment.



Geometry
--------

Geometry is a static library that is provided as part of Mango (the project).
It extends mango (the core libraries) by implementing several objects with
render events that render simple geometric shapes. It depends on mango and
OpenGL (but nothing else).


Pygeometry
----------

Pygeometry is a port of Geometry to Python, in particular a port that is 
compatible with Mangopy. As such, it can be imported by any script that runs
in a Mangopy environment to provide the same functionality that geometry 
would provide in any (Pythonless and Mangopy-less) mango simulation.

Pygeometry depends on mango, OpenGL, mangopy, Python and geometry.


Combining These Components
--------------------------

By combining the components mango, mango_on_glut and mangopy into a binary
that initializes these components and then runs as a Python
script the first argument passed to it [in the initialized mangopy 
environment] we obtain the 'Mango' binary that runs Mango simulations 
written in Python (the Pygeometry module is made available to it). 
Internally to the project this is another component named 'mangopy_on_glut'. 

At 38 lines, it's source is very simple - check it out in the source
directory mango/mangopy_on_glut/src/mangopy_on_glut.cpp.


