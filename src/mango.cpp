/*
 Copyright (c) 2011 Amos Joshua
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/
#include <iostream>
#include <mango/mango.h>


namespace Mango{	       

  const char* full_version_string(){
    return "1.0";
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
