#include <mango/glut/mango_on_glut.h>
#include <mango/geometry/geometry.h>

using namespace std;
using namespace Mango;

int main(int argc, char *argv[]){
  Geometry::Box *b;

  // Setup
  Mango::initialize();
  Mango::OnGlut::initialize(argc, argv);
		
  // Create a box and set its render event
  b = new Geometry::Box();		
  b->set(RENDER);	
	
  // Start the main loop
  Mango::OnGlut::start();
	
  // Teardown
  Mango::finalize();
}

