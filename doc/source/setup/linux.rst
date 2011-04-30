Setup on Linux
==============

Installing Mango on linux requires building it from source, by
executing the standard *./configure*, *make*, *make install*
commands. 

Installing Dependencies
-----------------------

Mango depends on GLUT and Python and requires the standard GNU
toolchain for compilation. On Ubuntu, these dependencies may be
installed by issuing the following command:

  .. code-block:: bash
     
     $ sudo apt-get install g++ freeglut3-dev python3.1-dev

Installing dependencies on other distributions may be slightly
different, but should follow similar lines.

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
     $ mkdir build-linux
     $ cd build-linux

Mango must be configured with the path to the Python include
files. Replace */usr/include/python3.1/* with the correct path on your
system, and execute this command to configure:

  .. code-block:: bash

     $ ../configure CXXFLAGS="-I/usr/include/python3.1/" \
       LDFLAGS="-lglut -lpython3.1" --enable-shared 

And then the following to install:

  .. code-block:: bash

     $ make
     $ sudo make install

You are now ready to run simulations written in Python (see
:doc:`/samples`). To do so, type:

  .. code-block:: bash

     $ mango path/to/script.py

By default, Mango will install at */opt/mango/<version>/* and include
the following components:
    
    * **core**:      
        A directory containing the mango executable. The installer will
        automatically link to it in /usr/bin/mango.

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

    * **inculde**:
        C++ header files. These should be used in conjunction with the
        libraries in *lib*.

    * **lib**:
        Static libraries for mango, mango_on_glut, geometry and
        mangopy. These may linked against when developing simulations
        in C++.
	
You are also ready to build simulation in C++. See
:doc:`/cpp/rapid-simulation-development` for further instructions.