#include <mango/glut/mango_on_glut.h>
#include <mango/geometry/geometry.h>
#include <iostream>
#include <exception>

using namespace std;
using namespace Mango;

int main(int argc, char *argv[]){
  Geometry::Box *b;
  Geometry::Sphere *s;
  Geometry::Cylinder *c;
  Geometry::Shell *sh;
  Geometry::Arrow *a[3];
  Geometry::CoordinateSystem *cs;
  Geometry::VertexArray *va;
  Geometry::Circle *ci[2];
  Geometry::NGon *n[2];
  Geometry::Rectangle *r[2];

  // Setup
  Mango::initialize();
  Mango::OnGlut::initialize(argc, argv);
		
  // Create a box and set its render event
  b = new Geometry::Box();		
  b->set(RENDER);
	
  // Create a sphere and set its render event
  s = new Geometry::Sphere();
  s->setRadius(0.7);
  s->position = Vector(2, 0, 0);
  s->set(RENDER);
	
  // Create a cylinder and set its render event
  c = new Geometry::Cylinder();
  c->position = Vector(0, 0, -2);	
  c->setHeight(1.0);
  c->setRadius(0.5);
  c->set(RENDER);	
	
  // Create a shell and set its render event		
  sh = new Geometry::Shell();		
  sh->position = Vector(2, 0, -2);
  sh->setRadius(0.7);
  sh->setFraction(0.6);
  sh->setThickness(0.05);
  sh->setOrientation(-25, 205, 0);
  sh->set(RENDER);
	
  // Create a few arrows
  a[0] = new Geometry::Arrow();
  a[0]->position = Vector(-2, -0.5, -2);
  a[0]->set(RENDER);
	
  a[1] = new Geometry::Arrow();
  a[1]->position = Vector(-1.6, -0.5, -2);
  a[1]->setLength(0.4);
  a[1]->setBlueComponent(0.8);
  a[1]->set(RENDER);
	
  a[2] = new Geometry::Arrow();
  a[2]->position = Vector(-1.8, -0.5, -1.6);
  a[2]->setLength(1.75);
  a[2]->setThickness(0.3);
  a[2]->setRedComponent(0.6);
  a[2]->set(RENDER);
	
  // Create a coordinate system
  cs = new Geometry::CoordinateSystem();
  cs->position = Vector(2, -0.3, 1.6);
  cs->setAxisLength(0.8);
  cs->setAxisThickness(0.1);
  cs->setRightHanded(1);
  cs->set(RENDER);
	
  // Create a vertex array
  va = new Geometry::VertexArray();	
  va->add(-0.5, 0.0, 0.0);
  va->add(0.0, 0.5, 0.0);
  va->add(0.0, 1.5, 0.0);
	
  va->add(0.0, 0.5, 0.0);
  va->add(0.5, 0.0, 0.0);
  va->add(0.0, 1.5, 0.0);							
	
  va->setRenderReverseOrientation(true);
  va->setStyle(GL_TRIANGLES);
  va->position = Vector(0, -0.5, 2);
  va->set(RENDER);	
	
  // Create circles 
  ci[0] = new Geometry::Circle();
  ci[0]->position = Vector(-2.0, 0, 2.0);
  ci[0]->setRadius(0.7);		
  ci[0]->setGreenComponent(0.9);
  ci[0]->set(RENDER);	
	
  ci[1] = new Geometry::Circle();
  ci[1]->position = Vector(-2.0, 0, 2.0);
  ci[1]->setRadius(0.2);
  ci[1]->setStyle(FILL);
  ci[1]->setOrientation(0, 90, 0);
  ci[1]->setRenderReverseOrientation(true);
  ci[1]->set(RENDER);
	
  // Create ngons
  n[0] = new Geometry::NGon();
  n[0]->position = Vector(-2.0, 0, 0);
  n[0]->setRadius(0.3);
  n[0]->setStyle(FILL);
  n[0]->setNumberOfSides(6);
  n[0]->setRenderReverseOrientation(true);
  n[0]->set(RENDER);
	
  n[1] = new Geometry::NGon();
  n[1]->position = Vector(-2.0, 0, 0);
  n[1]->setOrientation(0, 90, 0);
  n[1]->set(RENDER);
	
  // Create rectangles
  r[0] = new Geometry::Rectangle();
  r[0]->position = Vector(-4.0, 0, 0);
  r[0]->setOrientation(0, 45, 0);
  r[0]->set(RENDER);
	
  r[1] = new Geometry::Rectangle();
  r[1]->position = Vector(-4.0, 0, 0);
  r[1]->setOrientation(0, 135, 0);
  r[1]->setDimensions(0.5, 0.5/1.1618);
  r[1]->setStyle(FILL);
  r[1]->set(RENDER);
	
  // Start the main loop
  Mango::OnGlut::start();
	
  // Teardown
  Mango::finalize();
}

