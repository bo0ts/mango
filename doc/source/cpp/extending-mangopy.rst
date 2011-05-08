Extending Mango: New Classes
============================

Implementing new Mango classes in Python and C++ is an integral part
of developing simulations. In this sense, Mango can be extended with
the addition of new classes simply by placing the code for derived
classes in a seperate file and importing or including that file into
other simulations, according with the correct practices of each
languages. If this seems unclear, consider reading through the portion
of the documentation that describes simuation development in Python
and/or C++.

It is also possible to extend Mango with Python-accessible classes
that are written in C++. In this way one gets the best of both worlds:
simulations can still be written in Python with parts of the code that
require greater efficiency implemented in C++. The product of such an
extension is a shared library that behaves as a Python module and can
be imported into simulations written in Python with the standard
"import" statement.

Most of the work in this section is basic to creating any Python
extension, and developers may find it enlightning or useful to read
the "Extending and Embedding" portion of the Python
documentation. This is not, however, required - the code presented
here is intended as a skeletal Mango extension that builds "out of the
box". If you're not yet an expert on Python extensions and don't care
or have the time to become one, this code should be enough to just
start hacking away.


Platonic Solids
---------------

Consider the following C++ header file *tetrahedron.h* that implements
a bare-bones platonic solids module:

  .. literalinclude:: /../../mangopy/samples/solids/tetrahedron.h
     :language: c++

We wish to create an extension that will allow Python simulations to
access the Solids::Tetrahedron class. 

A Module is Born
----------------

The first step will be to create a new Python module called Solids. To
do this save the following as *pysolids.cpp*:

  .. literalinclude:: /../../mangopy/samples/solids/pysolids.cpp
     :language: c++

This file defines the Solids module and provides an initialization
routine. The purpose of the initialization routine is to create the
module object, run Mango module initialization, add new types and
constants to the module and return the module. It will be called when
"import Solids" is executed in a simulation, and indicates that an error
occured by returning NULL.

Note that *mpy_TetrahedronType* is used in *mpy_addObjectToModule*,
and that this struct is defined in *pytetrahedron.h*.

Wrapping a Tetrahedron
----------------------

The next step is to wrap the C++ implementation of Solids::Tetrahedron
with Python bindings. This is where the code gets lengthy with a fair
amount of boiler-plate code. Let's start with the header
*pytetrahedron.h*, which is still relatively short:

  .. literalinclude:: /../../mangopy/samples/solids/pytetrahedron.h
     :language: c++

And finally, the implementation of the bindings in
*pytetrahedron.cpp*:

  .. literalinclude:: /../../mangopy/samples/solids/pytetrahedron.cpp
     :language: c++

In general, unless you are attempting something especially fancy, the
dealloc and new methods require very little change - just replace
occurances of Solids::Tetrahdeon with your own module and class (say
Foo::Bar) and leave the rest alone. 

The setters and getters show the basics of wrapping C++ methods.

For setters: parse the incoming arguments using PyArg_ParseTuple(..),
call the corresponding setter in a try-catch block, and finally return
None. 

For getters: retrieve the value of a property from the
corresponding getter in a try-catch block, and then return it as a
Python object using Py_BuildValue(..). 

For methods that are not strictly setters or getters use elements from
both. Note that this is standard Python extension code, and you can
find many resources explaining the how and the why online. Also, look
up PyArg_ParseTuple and Py_BuildValue in the Python documentation for
more information on how to pass different types of data back and
forth. Last, It is encouraged that these functions should only wrap
existing methods, and not implement new functionality that is not
available in the original class.

The Method table is pretty much what it looks like - a list of the
class methods. Note the general form and add an entry for each
additional method implemented. If the method accepts arguments,
METH_VARARGS is an appropriate third element in a method entry,
otherwise use METH_NOARGS.

The last part of the file is the object type structure. Replace the
values for your own class/module where appropriate. Unless you are
extending the class beyond the addition of methods, the rest can be
left alone.

(One thing that is not shown here is how to define class
attributes. You can examine the Mango source or find examples online
on how to accomplish this. In general, Mango tries to maintain close
parallels between its C++ and Python APIs, so that class members will
be exposed either via setters/getters in both languages, or as
attributes in both languages, but not as one in one language and
another in the other).

 .. note::

    Automated tools like SWIG and Boost.Python exist that automate the
    process of wrapping C++ classes for Python. No such tool is used
    in Mango at the moment, but the adventurous reader may wish to try
    one of them to save time, feel good about their superior
    programming ability, or both.      

Building the Extension
----------------------

When all of these files are placed in the same directory they may be
built by executing one of the following commands:

**Linux**

  .. code-block:: bash
  
     $ g++ pysolids.cpp pytetrahedron.cpp -o Solids.so -fpic -shared -I/opt/mango/1.0/include/ -L/opt/mango/1.0/lib -lmango -lmong


**OSX**

  .. code-block:: bash
  
     $ g++ pysolids.cpp pytetrahedron.cpp -o Solids.so -arch i386 -fpic -shared -framework Mango -framework Python -framework OpenGL


**Windows**

  .. code-block:: bash

     $ g++ pysolids.cpp pytetrahedron.cpp -o Solids.pyd  -I/c/Program\ Files/Mango/1.0/include -L/c/Program\ Files/Mango/1.0/lib -o hello_box -lmango -lmong -lopengl32 

(Check out :doc:`/setup` for instructions on setting up a Mango
development environment, and :doc:`/cpp/rapid-simulation-development`
for more detailed instructions on executing build commands)


Four Tetrahedrons
-----------------

Once built, you can use the extension by importing it from a script
residing in the same folder, or place it in the *scripts* directory of
your Mango installation to make it available to all Mango scripts.

For instance, if the following code is saved as pyramids.py and placed
in the same directory as the build product Solids.so (or Solids.pyd):

  .. literalinclude:: /../../mangopy/samples/solids/pyramids.py
     :language: python

Running it with Mango will yield:


  .. image:: /images/pyramids.png
     :width: 480
     :height: 360