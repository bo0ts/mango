#include <mango/glut/mango_on_glut.h>
#include <mango/geometry/geometry.h>
#include <iostream>
#include <exception>

using namespace std;
using namespace Mango;

int main(int argc, char *argv[]){
  Geometry::Arrow *ag_l, *ag_ll, *al_g, *all_g, *al_ll, *all_l;

  Geometry::CoordinateSystem *gcs, *lcs, *llcs;

  Vector x(1, 0, 0);
  Vector y(0, 1, 0);
  Vector z(0, 0, 1);

  Vector w;
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

  llcs = new Geometry::CoordinateSystem();
  llcs->setParentFrame(lcs);
  llcs->setAxisLength(0.8);
  llcs->setAxisThickness(0.1);
  llcs->position = Vector(2, 2, 2);
  llcs->rotate(80, 30, 45);
  llcs->set(RENDER);

  
  w = llcs->transformToAncestor(z, GlobalFrame);
  ag_ll = new Geometry::Arrow();
  ag_ll->setTipPosition(w);
  ag_ll->set(RENDER);
  
  w = llcs->transformFromAncestor(x, GlobalFrame);
  all_g = new Geometry::Arrow();
  all_g->setParentFrame(llcs);
  all_g->setTipPosition(w);
  all_g->set(RENDER);



  w = lcs->transformToAncestor(x, GlobalFrame);
  ag_l = new Geometry::Arrow();
  ag_l->setTipPosition(w);
  ag_l->setColor(0.0, 1.0, 0.0);
  ag_l->set(RENDER);
  
  w = lcs->transformFromAncestor(z, GlobalFrame);
  al_g = new Geometry::Arrow();
  al_g->setParentFrame(lcs);
  al_g->setTipPosition(w);
  al_g->setColor(0.0, 1.0, 0.0);
  al_g->set(RENDER);


  w = llcs->transformToAncestor(x, lcs);
  al_ll = new Geometry::Arrow();
  al_ll->setParentFrame(lcs);
  al_ll->setTipPosition(w);
  al_ll->setColor(0.0, 0.0, 1.0);
  al_ll->set(RENDER);
    
  w = llcs->transformFromAncestor(z, lcs);
  all_l = new Geometry::Arrow();
  all_l->setParentFrame(llcs);
  all_l->setTipPosition(w);
  all_l->setColor(0.0, 0.0, 1.0);
  all_l->set(RENDER);
  

  // Start the main loop
  Mango::OnGlut::start();
	
  // Teardown
  Mango::finalize();
}

