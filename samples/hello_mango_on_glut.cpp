#include <mango/glut/mango_on_glut.h>
#include <iostream>

using namespace std;
using namespace Mango;

int main(int argc, char *argv[]){
  Core::Triangle *t;
	
  // Setup 
  Mango::initialize();	
  Mango::OnGlut::initialize(argc, argv);
		
  // Create a triangle and set its render event
  t = new Core::Triangle();
  t->set(RENDER);
	
  // Start the main loop
  Mango::OnGlut::start();
	
  // Finalize
  Mango::finalize();
}

