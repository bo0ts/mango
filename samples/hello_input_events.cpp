#include <mango/glut/mango_on_glut.h>
#include <iostream>

using namespace std;
using namespace Mango;

Core::inputEvent UpPressed(KEYBOARD, RELEASE, KEY_UP);
Core::inputEvent LeftButtonPressedOrReleased(MOUSE, ANY, BUTTON_LEFT);

class InputReader: public Core::Triangle{
  void input(Core::inputEvent &e){
    if (e  == UpPressed){
      std::cout << "up key pressed" << std::endl;
    }
    else if (e == LeftButtonPressedOrReleased){
      std::cout << "Left button event" << std::endl;
    }

    if (e.source == KEYBOARD){
      std::cout << "Key ";
      if (e.type == PRESS){
	std::cout << "press ";
      }
      else if(e.type == RELEASE){
	std::cout << "release ";
      }
      else {
	std::cout << "(unknown type)";
      }
      std::cout << e.code << std::endl;
    }
    else if (e.source == MOUSE){
      std::cout << "Button ";
      if (e.type == PRESS){
	std::cout << "click ";
      }
      else if(e.type == RELEASE){
	std::cout << "release ";
      }
      else {
	std::cout << "(unknown type)";
      }
      if (e.code == BUTTON_LEFT){
	std::cout << "left ";
      }
      else if (e.code == BUTTON_RIGHT){
	std::cout << "right ";
      }
      else if (e.code == BUTTON_MIDDLE){
	std::cout << "middle ";
      }
      else{
	std::cout << "unknown button ";
      }
      std::cout << std::endl;
    }
    else{
      std::cout << "Unkown event!" << std::endl;
    }
  }
};


int main(int argc, char *argv[]){
  Core::Object *t;
  
  Mango::initialize();	
  Mango::OnGlut::initialize(argc, argv);	
  	
  t = new InputReader();
  t->set(INPUT | RENDER);
	
  // Start the main loop
  Mango::OnGlut::start();
	
  // Finalize
  Mango::finalize();
}

