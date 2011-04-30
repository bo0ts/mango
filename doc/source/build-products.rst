Build Products
==============

Building from source will result in the following executables and libraries
being built, relative to the root of the build directory:

  * **mango**
      main Mango executable (OSX and Linux)
  * **.libs/mango.exe**
      main Mango executable (Windows)
  * **.libs/Geometry.so**
      Mango Geometry module
  * **.libs/libmango.a**
      static mango library
  * **.libs/libgeometry.a**
      static geometry library
  * **.libs/libmong.a**
      static mango-on-glut library 
  * **.libs/libmangopy.a**
      static mangopy library

  .. note::
   
     On windows, an executable named *mango.exe* is generated at the
     root of the build directory, however it is not the executable of
     interest and should be ignored. The correct executable is
     *.libs/mango.exe*.