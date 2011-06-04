Building on Windows
===================

Installing Dependencies
-----------------------

Follow the setup steps for building Mango simulations in C++ described
in :ref:`setup-windows-cpp` (it is not necessary to run the Mango installer as
described in the first section). Make sure to install an appropriate
version of Python.
 
Configuring, Building and Installing
------------------------------------

Download the source, say to *C:\\src\\mango.tar.gz* (if using another
location, substitute the containing directory for *C:\\src\\* and the
archive name for *mango.tar.gz* where appropriate). open a MinGW shell
(for instance by selecting "MinGW > MinGW Shell" from the Program
Files menu), cd into */c/src/* and untar the archive with:

  .. code-block:: bash

     $ tar xvf mango.tar.gz

This will extract the source to *C:\\src\\mango*. 

Next we will change into this directory. While it is not strictly
necessary, we will also create a build directory and configure/build
the project there (if you prefer not to do this simply skip those
steps and adjust commands appropriately):

  .. code-block:: bash

     $ cd C:\\src\\mango
     $ mkdir build-windows
     $ cd build-windows

The following command configures Mango:

  .. code-block:: bash

     $ ../configure CXXFLAGS="-I/c/MingGW/include -I/c/Python31/include" LDFLAGS="-L/c/MingGW/lib -L/c/Python31/libs -lopengl32 -lfreeglut -lpython31"

Finally, issue the following to build:

  .. code-block:: bash

     $ make