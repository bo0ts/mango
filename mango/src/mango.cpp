#include <iostream>
#include "mango.h"


namespace Mango{	       

  char* full_version_string(){
    return PACKAGE_VERSION;
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
      View->setMode(RMB_CYLINDRICAL_ROTATE);
      
      Engine->setCameraObject(Camera);
      Engine->setViewObject(View);
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
