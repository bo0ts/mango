Rapid Simulation Development
============================

One of the strengths of Mango is its parallel C++ and Python APIs. Since the
APIs are so similar, it is easy to try out ideas in Python and move 
simulations into C++ when a greater need for performance arises. This section
will give a brief demonstration of compiling a simulation in C++ using Mango
and GLUT. If you have not yet read the introduction to using Mango in Python 
you may wish to do so (:doc:`../mangoinpython`) as the conceptual use of 
Mango described there holds in C++ as well.


A Template C++ Mango simulation takes the following form:

  .. code-block:: c++
  
     #include "Mango/mango_on_glut.h" 
     
     using namespace std;
     using namespace Mango;
  
     // Define custom classes here
  
     void design_scene(){
     	// Create objects and set events
  	// ...
     }
  
     void destroy_scene(){
          // Destroy dynamically created classes
  	// ...
     }
     
     int main(int argc, char *argv[]){   
     
       // Setup
       Mango::initialize();
       Mango::OnGlut::initialize(argc, argv);
     		
       // Create scene
       design_scene(); 
  
       // Start the main loop
       Mango::OnGlut::start();
     	
       // Teardown
       destroy_scene();
       Mango::finalize();
     }
     


For instance, to make a hello-world box simulation, save the following as 
hello_box.cpp:

  .. code-block:: c++
  
     #include "Mango/mango_on_glut.h" 
     #include "Mango/geometry.h" 
     
     using namespace std;
     using namespace Mango;
     
     Geometry::Box *b;
  
     void design_scene(){
       // Create a box and set its render event
       b = new Geometry::Box();		
       b->set(RENDER);	
     }
  
     void destroy_scene(){
       delete b;
     }
  
     int main(int argc, char *argv[]){        
       // Setup
       Mango::initialize();
       Mango::OnGlut::initialize(argc, argv);
     		
       // Create scene
       design_scene(); 
     	
       // Start the main loop
       Mango::OnGlut::start();
     	
       // Teardown
       destroy_scene();
       Mango::finalize();
     }



Then from a terminal window, build it in the manner appropriate for your 
platform:

**Linux**
  
  Open a terminal window, navigate to the directory containing your
  simulation source code and execute the following command:

    .. code-block:: bash
    
	$ g++ hello_box.cpp -o hello_box -I/opt/mango/1.0/include/ -L/opt/mango/1.0/lib -lmango -lmong -lgeometry -lglut

  You can then run the simulation with the following command:

    .. code-block:: bash

       $ ./hello_box


**OSX**

  Open a terminal window, navigate to the directory containing your 
  simulation source code and execute the following command:

    .. code-block:: bash
    
       $ g++ hello_box.cpp -o hello_box -arch i386 -framework Mango -framework OpenGL -framework GLUT

  (Remove the flag *-arch i386* to build 64-bit binaries. This requires a 
  64bit build of Mango)

  You can then run the simulation with the following command:

    .. code-block:: bash
    
       $ ./hello_box


**Windows**

  Open a MinGW shell and navigate to the directory containing your
  simulation source code . You can open a MinGW shell by selecting
  "MinGW > MinGW Shell" from the Program Files menu. In order to
  navigate to your source file, note that MinGW will mount the C:
  drive at /c, the D: drive at /d and so on. Once you are at the right
  location, execute the following command:

    .. code-block:: bash

       g++ hello_box.cpp -I/c/Program\ Files/Mango/include -L/c/Program\ Files/Mango/cxxlib -o hello_box -lmango -lmong -lgeometry -lopengl32 -lfreeglut

  You can then run the simulation from the MinGW shell by executing:

    .. code-block:: bash

       hello_box

  If you wish to run the simulation from the standard windows command-prompt,
  or from windows explorer, you may need to copy several dlls to the same
  folder as the simulation executable (or otherwise make them available) in 
  order to avoid errors about missing dlls (this should also be done when 
  redistributing the executable). The dlls that need to be copied are: 
    
    * **freeglut.dll** (*C:\\windows\\system32\\*)
    * **libstdc++-6.dll** (*C:\\MinGW\\bin\\*)
    * **libgcc_s_dw2-1.dll** (*C:\\MinGW\\bin\\*)


Notice the strong parallel between this example and the equivalent simulation
in Python (:ref:`getting-started-python-box`). Other than the template-code 
that must accompany every Mango simulation in C++ - and which comprises most
of the simulation in this case - the code is practically identical, with 
minor syntax changes. Of course, this is a very simple simulation, but the 
parallel often holds for more complex simulations as well.

Here is another example simulating a ball bouncing on a platform:

  .. code-block:: c++
      
    #include "Mango/mango_on_glut.h"
    #include "Mango/geometry.h"  
    
    using namespace Mango;
    
    class BouncingBall: public Geometry::Sphere{
      float t;
    public:
      BouncingBall():Geometry::Sphere(){
        t = 0;
      }
      virtual void step(){
        t += 0.08;
        position = Vector(0, 0.2 + fabs(sin(t)), 0);
      }
    };
    
    
    Geometry::Box *platform;
    BouncingBall *ball;
  
    void design_scene(){      
      platform = new Geometry::Box();
      platform->setDimensions(1.0, 0.1, 1.0);
      ball = new BouncingBall();    
      ball->setRadius(0.2);
    
      ball->set(RENDER | STEP);
      platform->set(RENDER);
    }
    
    void destroy_scene(){
      delete ball;
      delete platform;    
    }
    
    int main(int argc, char *argv[]){
      // Setup
      Mango::initialize();
      Mango::OnGlut::initialize(argc, argv);
        
      // Create scene
      design_scene(); 
    
      // Start the main loop
      Mango::OnGlut::start();
    
      // Teardown
      destroy_scene();
      Mango::finalize();
    }
       

This simulation can be built with the same command as the previous example
after adjusting the source and output file names. Again, notice the strong
parallels with the Python equivalent (first sample in 
:ref:`frames-bouncing-ball-sample`).