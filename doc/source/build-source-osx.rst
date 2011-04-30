Building on OSX
===============

Installing Dependencies
-----------------------

Follow the setup steps for building Mango simulations in C++ described
in :ref:`setup-osx-cpp` (it is not necessary to run the Mango installer as
described in the first section). Make sure to install an appropriate
version of Python.
 
Configuring, Building and Installing
------------------------------------

Download the source, say to *~/src/mango.tar.gz* (if using another
location, substitute the containing directory for *~/src/* and the
archive name for *mango.tar.gz* where apropriate). open a terminal and
cd into *~/src/*, and untar it with:

  .. code-block:: bash

     $ tar xvf mango.tar.gz

This will extract the source to *~/src/mango*. 

Next we will change into this directory. While it is not strictly
necessary, we will also create a build directory and configure/build
the project there (if you perfer not to do this simply skip those
steps and adjust commands appropriately):

  .. code-block:: bash

     $ cd ~/src/mango
     $ mkdir build-osx
     $ cd build-osx

The following command configures Mango: 

  .. code-block:: bash

     $ ../configure CXXFLAGS="-arch i386" LDFLAGS="-arch i386"  --enable-shared

These instructions assume all components are 32bit, if building for a
64bit architecture leave off *-arch i386* from the command.

Finally, issue the following to build:

  .. code-block:: bash

     $ make