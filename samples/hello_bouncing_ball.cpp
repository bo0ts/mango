#include <mango/glut/mango_on_glut.h>
#include <mango/geometry/geometry.h>

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
  ball = new BouncingBall();

  platform->setDimensions(1.0, 0.1, 1.0);
  ball->setRadius(0.2);

  ball->set(RENDER | STEP);
  platform->set(RENDER);
}


int main(int argc, char *argv[]){
  // Setup
  Mango::initialize();
  Mango::OnGlut::initialize(argc, argv);

  // Define scene
  mango_main();

  // Start the main loop
  Mango::OnGlut::start();

  // Teardown
  Mango::finalize();
}
