#include <mango/glut/mango_on_glut.h>
#include <mango/geometry/geometry.h>
#include <iostream>
#include <exception>

using namespace std;
using namespace Mango;

class Label: public Core::Object{
  const char *text;

public:
  Label(const char* new_text){
    text = new_text;
  }

  void step(){
    Vector global_camera_pos;
    global_camera_pos = Camera->focus()->transformToParent(Camera->position);
    pointTo(global_camera_pos);
    rotate(0, -90, 0);
  }

  void render(){
    glColor3f(1.0, 0.5, 0);
    transform();
    Draw::text(0, 0.1, text, 0.3);
  }

};

int main(int argc, char *argv[]){
  Geometry::CoordinateSystem *cs;
  Label *x, *y, *z;

  // Setup
  Mango::initialize();
  Mango::OnGlut::initialize(argc, argv);
    	
  // Coordinate System
  cs = new Geometry::CoordinateSystem();  
  cs->setRightHanded(1);
  cs->set(RENDER);    

  // Labels
  x = new Label("x");
  x->position = Vector(1.1, 0, 0);
  x->set(STEP | RENDER);

  y = new Label("y");
  y->position = Vector(0, 1.15, 0);
  y->set(STEP | RENDER);

  z = new Label("z");
  z->position = Vector(0, 0, 1.1);
  z->set(STEP | RENDER);

  // Start the main loop
  Mango::OnGlut::start();
	
  // Teardown
  Mango::finalize();
}

