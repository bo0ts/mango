/*
 Copyright (c) 2011, 2012 Amos Joshua
 
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
#include <mango/glut/mango_on_glut.h>
#include <iostream>

namespace Mango{  
  static int frame_count;
  static int last_f;
  namespace OnGlut{
	
    static void resize(int width, int height)
    {
      const float ar = (float) width / (float) height;
	
      glViewport(0, 0, width, height);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      Engine->setWindowDimensions(width, height);
    }
	
    static void display(void)
    {		
#ifdef __APPLE__
      try{
#endif

      Engine->limitFps();
      Engine->countFrame();

      int clear_mask = GL_DEPTH_BUFFER_BIT;
      if (Engine->clearBuffer()){
	clear_mask = clear_mask | GL_COLOR_BUFFER_BIT;
      }
      glClear(clear_mask);
	
      glPushMatrix();
      Engine->executeStepEvents();
      Engine->executeRenderEvents();
      Engine->executeDrawEvents();	
      Engine->executeInputEvents();    	
      glPopMatrix();
	
      glutSwapBuffers();	     

#ifdef __APPLE__
      }
      catch(Mango::Core::Error &e){
	e.trace();
	std::cerr << std::endl << std::endl;
	exit(1);
      }
      catch(std::exception &e){
	e.what();
	exit(2);
      }      
#endif
    }
	
	
    static void mouse_button_callback(int button, int state, int x, int y){
      // Note: GLUT mouse values for 'button' argument match the value for the BUTTON_* constants, in general might not be the case
      if (state == 0){
	Mouse->registerButtonPress(button);
      }
      else if(state == 1){
	Mouse->registerButtonRelease(button);
      }
      Mouse->updateCoordinates(x, y);
    }
	
    static void mouse_move_callback(int x, int y){
      Mouse->updateCoordinates(x, y);
    }
	
    static void keyboard_key_down_callback(unsigned char key, int x, int y){
      Keyboard->registerKeyPress(key);
    }
	
    static void keyboard_key_up_callback(unsigned char key, int x, int y){
      Keyboard->registerKeyRelease(key);
    }
	
    static void keyboard_special_key_up_callback(int key, int x, int y){
      switch (key){
      case 1:
	Keyboard->registerKeyRelease(KEY_F1);
	break;
      case 2:
	Keyboard->registerKeyRelease(KEY_F2);
	break;
      case 3:
	Keyboard->registerKeyRelease(KEY_F3);
	break;
      case 4:
	Keyboard->registerKeyRelease(KEY_F4);
	break;
      case 5:
	Keyboard->registerKeyRelease(KEY_F5);
	break;
      case 6:
	Keyboard->registerKeyRelease(KEY_F6);
	break;
      case 7:
	Keyboard->registerKeyRelease(KEY_F7);
	break;
      case 8:
	Keyboard->registerKeyRelease(KEY_F8);
	break;
      case 9:
	Keyboard->registerKeyRelease(KEY_F9);
	break;
      case 10:
	Keyboard->registerKeyRelease(KEY_F10);
	break;
      case 11:
	Keyboard->registerKeyRelease(KEY_F11);
	break;
      case 12:
	Keyboard->registerKeyRelease(KEY_F12);
	break;
	
      case 100:
	Keyboard->registerKeyRelease(KEY_LEFT);
	break;
      case 101:
	Keyboard->registerKeyRelease(KEY_UP);
	break;
      case 102:
	Keyboard->registerKeyRelease(KEY_RIGHT);
	break;
      case 103:
	Keyboard->registerKeyRelease(KEY_DOWN);
	break;
	
      case 104:
	Keyboard->registerKeyRelease(KEY_PAGEUP);
	break;
      case 105:
	Keyboard->registerKeyRelease(KEY_PAGEDOWN);
	break;
      case 106:
	Keyboard->registerKeyRelease(KEY_HOME);
	break;
      case 107:
	Keyboard->registerKeyRelease(KEY_END);
	break;
      case 108:
	Keyboard->registerKeyRelease(KEY_INSERT);
	break;
      }
    }
	
    static void keyboard_special_key_down_callback(int key, int x, int y){
      switch (key){
      case 1:
	Keyboard->registerKeyPress(KEY_F1);
	break;
      case 2:
	Keyboard->registerKeyPress(KEY_F2);
	break;
      case 3:
	Keyboard->registerKeyPress(KEY_F3);
	break;
      case 4:
	Keyboard->registerKeyPress(KEY_F4);
	break;
      case 5:
	Keyboard->registerKeyPress(KEY_F5);
	break;
      case 6:
	Keyboard->registerKeyPress(KEY_F6);
	break;
      case 7:
	Keyboard->registerKeyPress(KEY_F7);
	break;
      case 8:
	Keyboard->registerKeyPress(KEY_F8);
	break;
      case 9:
	Keyboard->registerKeyPress(KEY_F9);
	break;
      case 10:
	Keyboard->registerKeyPress(KEY_F10);
	break;
      case 11:
	Keyboard->registerKeyPress(KEY_F11);
	break;
      case 12:
	Keyboard->registerKeyPress(KEY_F12);
	break;
	
      case 100:
	Keyboard->registerKeyPress(KEY_LEFT);
	break;
      case 101:
	Keyboard->registerKeyPress(KEY_UP);
	break;
      case 102:
	Keyboard->registerKeyPress(KEY_RIGHT);
	break;
      case 103:
	Keyboard->registerKeyPress(KEY_DOWN);
	break;
	
      case 104:
	Keyboard->registerKeyPress(KEY_PAGEUP);
	break;
      case 105:
	Keyboard->registerKeyPress(KEY_PAGEDOWN);
	break;
      case 106:
	Keyboard->registerKeyPress(KEY_HOME);
	break;
      case 107:
	Keyboard->registerKeyPress(KEY_END);
	break;
      case 108:
	Keyboard->registerKeyPress(KEY_INSERT);
	break;
      }
    }
	
    static void idle(void)
    {
      glutPostRedisplay();
    }
	
	
    /* Lighting Settings */
	
    const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
	
    const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };
	
	
    void initialize(int argc, char *argv[]){
      requirePresenceOfEngine("Mango::OnGlut", "initialize");

      glutInit(&argc, argv);
      glutInitWindowSize(Engine->windowWidth(), Engine->windowHeight());
      glutInitWindowPosition(10,10);
      glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	
      glutCreateWindow("Mango");
	
      glutReshapeFunc(resize);
      glutDisplayFunc(display);

      if (Keyboard != NULL){
	glutKeyboardFunc(keyboard_key_down_callback);
	glutKeyboardUpFunc(keyboard_key_up_callback);
	glutSpecialFunc(keyboard_special_key_down_callback);
	glutSpecialUpFunc(keyboard_special_key_up_callback);
      }
	
      if (Mouse != NULL){
	glutMouseFunc(mouse_button_callback);
	glutMotionFunc(mouse_move_callback);
	glutPassiveMotionFunc(mouse_move_callback);
      }
	
      glutIdleFunc(idle);
	
      glEnable(GL_CULL_FACE);
      glCullFace(GL_BACK);
	
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LESS);
	
      //glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
      //glDisable(GL_BLEND);
      //glEnable(GL_ALPHA_TEST);
      //glAlphaFunc(GL_GEQUAL, 0.5);
      //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    	    
		
      glEnable(GL_LIGHT0);
      glEnable(GL_NORMALIZE);
      glEnable(GL_COLOR_MATERIAL);
      glEnable(GL_LIGHTING);
	
      glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
      glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
      glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
      glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	
      if (Engine->windowFullscreen()){
	glutGameModeString("800x600:32");
	if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)){
	  glutEnterGameMode();
	}
	else{
	  std::cout << "Error: attempted fullscreen mode, but could not enter glut game mode with string '800x600:32'";
	}
      }      
    }
	
    void start(){
      try{
	startWithoutCatchingErrors();
      }
      catch(Core::Error &e){
	e.trace();        	    
      }	
    }

    void startWithoutCatchingErrors(){
      glutMainLoop();
    }
	
  } // OnGlut
} // Mango


