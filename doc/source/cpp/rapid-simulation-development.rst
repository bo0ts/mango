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

   #include "mango_on_glut.h"
   
   using namespace std;
   using namespace Mango;

   // Define custom classes here

   void mango_main(){
   	// Design scene here
	// ...
   }
   
   int main(int argc, char *argv[]){   
   
     // Setup
     Mango::initialize();
     Mango::OnGlut::initialize(argc, argv);
   		
     mango_main(); // Design scene

     // Start the main loop
     Mango::OnGlut::start();
   	
     // Teardown
     Mango::finalize();
   }
   


For instance, to make a hello-world box simulation, save the following as 
hello_box.cpp:

.. code-block:: c++

   #include "mango_on_glut.h"
   #include "geometry.h"
   
   using namespace std;
   using namespace Mango;
   
   void mango_main(){
     // Create a box and set its render event
     b = new Geometry::Box();		
     b->set(RENDER);	
   }

   int main(int argc, char *argv[]){
     Geometry::Box *b;
   
     // Setup
     Mango::initialize();
     Mango::OnGlut::initialize(argc, argv);
   		
     mango_main(); // Design scene
   	
     // Start the main loop
     Mango::OnGlut::start();
   	
     // Teardown
     Mango::finalize();
   }


Then from a terminal window, build it with:

TODO: linux and windows build commands

.. code-block:: bash
 
   $ g++ hello_box.cpp -L/usr/local/mango/lib -I/usr/local/mango/include/mango -I/usr/local/mango/include/mango_on_glut -I/usr/local/mango/include/geometry -framework OpenGL -framework GLUT -lmgeo -lmong -lmango -o hello_box -arch i386  -pg -g3


You may now run the simulation by running the resulting binary hello_box.

Notice the strong parallel between this example and the equivalent simulation
in Python (:ref:`getting-started-python-box`). Other than the template-code 
that must accompany every Mango simulation in C++ - and which comprises most
of the simulation in this case - the code is practically identical, with 
minor syntax changes. Of course, this is a very simple simulation, but the 
parallel often holds for more complex simulations as well.

Here is another example simulating a ball bouncing on a platform:

.. code-block:: c++

  #include "mango_on_glut.h"
  #include "geometry.h"
  
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
  
  void mango_main(){
    Geometry::Box *platform;
    BouncingBall *ball;
  
    platform = new Geometry::Box();
    platform->setDimensions(1.0, 0.1, 1.0);
    ball = new BouncingBall();    
    ball->setRadius(0.2);
  
    ball->set(RENDER | STEP);
    platform->set(RENDER);
  }
  
  
  int main(int argc, char *argv[]){
    // Setup
    Mango::initialize();
    Mango::OnGlut::initialize(argc, argv);
      
    mango_main(); // Design scene
  
    // Start the main loop
    Mango::OnGlut::start();
  
    // Teardown
    Mango::finalize();
  }
     

This simulation can be built with the same command as the previous example
after adjusting the source and output file names. Again, notice the strong
parallels with the Python equivalent (first sample in 
:ref:`frames-bouncing-ball-sample`).