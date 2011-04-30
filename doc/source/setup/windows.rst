Setup on Windows
================

Windows - Running Scripts
-------------------------

Download and run the windows installer. By default, Mango will install at:

  .. code-block:: text
   
     C:\Program Files\Mango\1.0

At this point you are ready to run simulations written in Python (see
:doc:`/samples`). In order to do this, open up a command prompt (you
can find it in the start menu under "Accessories"), and type:

  .. code-block:: text

     mango path\to\script.py

For instance, if you were to save a script as "c:\\test.py", typing the 
following at a command prompt would run the simulation in Mango:

  .. code-block:: text

     mango c:\test.py

Mango program files will be located at *C:\\Program Files\\Mango\\1.0\\*
or *C:\\Program Files (X86)\\Mango\\1.0\\* and include:

  * **core**: 
      A directory containing the mango executable. The installer will
      automatically add this directory to the path.
  
  * **doc**: 
      A copy of the documentation.
  
  * **sample**:
      Sample mango scripts.
  
  * **script**: 
      A directory whose contents are available directly to
      Mango. Scripts or libraries places in this directory can be
      imported by any mango script. Note that it is not intended for
      all of your scripts to live in this directory, only those that
      should be accessible on a system-wide scale.
  
  * **include**:  
      C++ header files. These should be used in conjunction with the
      libraries in *lib*.
  
  * **lib**: 
      Static libraries for mango, mango_on_glut, geometry and
      mangopy. These may linked against when developing simulations in
      C++.

.. _setup-windows-cpp:

Windows - C++ Development
-------------------------

In order to develop Mango simulations in C++, you will need to install
MinGW, MSYS, GLUT and Python (the last two only if you intend to use them).

MinGW is available at http://www.mingw.org. Download and run the automated installer
and when prompted to select components, mark the following: "C++ compiler",
"MSYS Basic System" and "MingW Developer Toolkit". Once the install 
completes you should have MinGW and MSYS installed. 

There are several ways to install GLUT. My perferred method is not to install
it at all, but rather use freeGLUT, which can be found at 
http://freeglut.sourceforge.net. The download page should reference prebuilt
packages for windows - make sure to get the MinGW package. Installation
involves copying header files to *c:\\MinGW\\include*, library files to 
*c:\\MinGW\\lib* and the freeGLUT DLL to *c:\\windows\\system32* (this is 
assuming that MinGW was installed at *c:\\MinGW* and that you want the 
freeGLUT DLL to be globally available).

Once MinGW, MSYS and GLUT are installed, you are ready to start building
simulations written in C++. See :doc:`/cpp/rapid-simulation-development` 
for further instructions on how to do this.

If you require Python, for instance to extend Mango's scriptable Python
environment, to build Mango from source or to embed Mango and Python into 
a C++ application, you may find it at http://www.python.org. Download and
install the appropriate version (see :doc:`dependencies-versions`).  

