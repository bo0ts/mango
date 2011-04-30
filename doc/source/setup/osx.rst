Setup on OSX
============

OSX - Running Scripts
---------------------

Download and run the OSX installer. By default, Mango will install as a 
framework in:

  .. code-block:: text

     /Library/Frameworks/Mango.framework

Once installed, you are ready to run simulations written in Python
(see :doc:`/samples`). To do so, fire up a terminal window (you can
find it by typing 'Terminal' in spotlight) and type:
 
  .. code-block:: text

     mango path/to/script.py

For instance, if you saved a script in your home directory under 
scripts/test.py, you can run it by typing:

  .. code-block:: text

     mango ~/scripts/test.py

Framework files will be located at
*/Library/Frameworks/Mango.framework/Versions/Current/* and include:

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


.. _setup-osx-cpp:

OSX - C++ Development
---------------------

In order to develop C++ applications with Mango, you will need to install
XCode (generally available from http://developer.apple.com/). Python is 
necessary only if you wish to extend Mango's scriptable Python environment
with C++, if you wish to build Mango from source, or if you intend to embed
Mango and Python into your own application. If so you may
need to install Python if the version provided by OSX is significantly
different than the one supported by Mango (to check, fire up the terminal 
and type "python --version", then compare the value to that in 
:doc:`dependencies-versions`).

Regardless of Python, once XCode is installed you can build simulations
written in C++ [that don't involve Python]. See the section 
:doc:`/cpp/rapid-simulation-development` for more information. 

If you require Python and do not an appropriate version installed (see 
:doc:`dependencies-versions`), download and install one from 
http://www.python.org.

  .. note::
  
    A possible problem may arise when several versions of the Python
    framework are installed in multiple locations. In particular, system-provided
    versions may reside in 
    
      */System/Library/Frameworks/Python.framework*
    
    while user-installed ones in 
    
      */Library/Frameworks/Python.framework* 
    
    This was the 
    case on a particular build machine, with 2.6 installed in the former and 3.1
    in the latter. When passing the argument "-framework Python" to g++, version 2.6
    was always used. I was unable to find a way to force use of version 3.1, 
    except by modifying 
    
      */System/Library/Frameworks/Python.framework/Versions/Current* 
    
    to point to
    
      */Library/Frameworks/Python.framework/Versions/Current*
    
    If you find yourself
    in the same position you may need to make the same modification. If you are
    aware of a better solution I would be interested to know about it.
  
