#include <iostream>
#include "mango.h"


namespace Mango{
#define MANGO_VERSION 1.0
  char version_str[20];
	
  double version(){
    return MANGO_VERSION;
  }
	
  char* version_string(){	
    sprintf(version_str, "Mango %.1f", version());
    return version_str;
  }
	
  void initialize(bool setup_default_environment){
    if (setup_default_environment){
      GlobalFrame = new Core::Frame(true);
      Engine = new Core::CoreEngine();      
      Keyboard = new Core::CoreKeyboard();
      Mouse = new Core::CoreMouse();
      Camera = new Core::CoreCamera();
      View = new Core::CoreCamera();      
      
      Camera->set(STEP);
      Camera->lookAt(Vector(0, 0, 0), 5);
      
      View->set(STEP);		
      
      Engine->setCameraObject(Camera);
      Engine->setViewObject(View);

      std::cout << "Engine at init is at ||" << (int)&Engine << "||" << std::endl;
    }
  }
  
  void finalize(bool teardown_default_environment){
    if (teardown_default_environment){      
      delete View;
      delete Camera;
      delete Mouse;
      delete Keyboard;
      delete Engine;
      delete GlobalFrame;
    }
  }

}
