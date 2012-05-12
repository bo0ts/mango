#include <mango/glut/mango_on_glut.h>
#include <mango/geometry/geometry.h>
#include <iostream>
#include <exception>

using namespace std;
using namespace Mango;

int main(int argc, char *argv[]){
  Geometry::Arrow *la, *ga;
  Geometry::CoordinateSystem *gcs, *lcs;

  Vector v(0, 1, 0);
  Vector w(0, 0, 1);
  // Setup
  Mango::initialize();
  Mango::OnGlut::initialize(argc, argv);
	
  gcs = new Geometry::CoordinateSystem();
  gcs->setAxisLength(0.8);
  gcs->setAxisThickness(0.1);
  gcs->set(RENDER);

  lcs = new Geometry::CoordinateSystem();
  lcs->setAxisLength(0.8);
  lcs->setAxisThickness(0.1);
  lcs->position = Vector(2, 0, 2);
  lcs->rotate(30, 60, 90);
  lcs->set(RENDER);

  v = lcs->transformToParent(v);
  GLfloat v1, v2, v3;
  v1 = v[0];
  v2 = v[1];
  v3 = v[2];
  std::cout << "v: <" << v[0] << ", " << v[1] << ", " << v[2] << ">" << std::endl;
  ga = new Geometry::Arrow();
  ga->setTipPosition(v);
  ga->set(RENDER);


  w = lcs->transformFromParent(w);
  la = new Geometry::Arrow();
  la->setParentFrame(lcs);
  la->setTipPosition(w);
  la->set(RENDER);
  

  // Start the main loop
  Mango::OnGlut::start();
	
  // Teardown
  Mango::finalize();
}

