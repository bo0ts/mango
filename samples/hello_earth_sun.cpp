#include <mango/glut/mango_on_glut.h>
#include <mango/geometry/geometry.h>
#include <iostream>
#include <exception>

using namespace std;
using namespace Mango;


class Sattelite: public Geometry::Sphere{
  GLfloat r;
  double t;

public:
  Sattelite(){
    r = 2.0;
    t = 0;
  }

  void step(){
    t += 0.04;
    position = Vector(r*cos(-t), 0, r*sin(-t));
  }

};

int main(int argc, char *argv[]){
  Geometry::CoordinateSystem *cs;
  Geometry::Sphere *sun;
  Sattelite *earth;  

  // Setup
  Mango::initialize();
  Mango::OnGlut::initialize(argc, argv);
		
  // Sun
  sun = new Geometry::Sphere();
  sun->setRadius(0.7);
  sun->setColor(1.0, 1.0, 0.0);
  sun->set(RENDER);
  sun->position = Vector(1.0, 0, 1.0);

  // Earth
  earth = new Sattelite();
  earth->setRadius(0.3);
  earth->setColor(0.0, 0.0, 1.0);
  earth->set(RENDER | STEP);
  earth->setParentFrame(sun);
		
  // Coordinate System
  cs = new Geometry::CoordinateSystem();
  cs->position = Vector(-2, 0, -1.6);
  cs->setAxisLength(0.8);
  cs->setAxisThickness(0.1);
  cs->setRightHanded(1);
  cs->set(RENDER);
    
  // Position Camera
  //Camera->follow(sun);
  Camera->follow(earth);

  // Start the main loop
  Mango::OnGlut::start();
	
  // Teardown
  Mango::finalize();
}

