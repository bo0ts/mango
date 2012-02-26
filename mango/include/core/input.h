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
#include <vector>
#include <deque>
#include "constants.h"

#ifndef MANGO_CORE_INPUT
#define MANGO_CORE_INPUT

namespace Mango{
  namespace Core{
    
    /**
     * A class whose instances represent single input events such
     * as keyboard- or mouse- key presses or releases. An input event
     * is characterized by a source, type, and key code. Instances may
     * be compared using the comparison operator '==', where two instances
     * e1 and e2 are equal if all of the following hold: 
     \verbatim embed:rst
     * e1.source == e2.source, or at least one of them is equal to ANY
     * e1.type == e2.type, or at least one of them is equal to ANY
     * e1.code == e2.code, or at least one of them is equal to ANY
     \endverbatim
     */
    class inputEvent{
    public:
      inputEvent(int src = -1, int tp = -1, int cd = -1){
	source = src;
	type = tp;
	code = cd;
      }

      inline bool operator==(const inputEvent &other_event){
	return (((source == -1) || (other_event.source == -1) || (source == other_event.source)) && 
		((type == -1) || (other_event.type == -1) || (type == other_event.type)) && 
		((code == -1) || (other_event.code == -1) || (code == other_event.code)));
      }

      inline bool operator!=(const inputEvent &other_event){
	return (((source != -1) && (other_event.source != -1) && (source != other_event.source)) || 
		((type != -1) && (other_event.type != -1) && (type == other_event.type)) || 
		((code != -1) && (other_event.code != -1) && (code == other_event.code)));
      }

      int source;
      int type;
      int code;
    };

    /**
     * An abstracted keyboard class that provides individual key state
     * information. Each framework that wishes to supply keyboard
     * functionality is responsible for calling registerKeyPress
     * and registerKeyRelease  when key presses and releases
     * occur.
     */
    class CoreKeyboard{
    public:
      //// @cond
      std::deque<int> typedKeyBuffer;
      std::deque<inputEvent> eventBuffer;
      //// @endcond

      CoreKeyboard();
      ~CoreKeyboard();

      //// @cond
      virtual const char *objectType() const{
	return "CoreKeyboard";
      }

      void suppress(int key_code);
      //// @endcond
            
      bool down(int key_code);
      short int state(int key_code);

      bool keyPressOccurred();
      void clearKeyPressOccurredFlag();
      bool keyReleaseOccurred();
      void clearKeyReleaseOccurredFlag();
      
      void registerKeyPress(int key_code);
      void registerKeyRelease(int key_code);
      
      void pushInputEvent(int type, int code);
      inputEvent popInputEvent();
	    
    private:
      int keys[MAX_KEYCODE_INDEX];
      bool suppressed_keys[MAX_KEYCODE_INDEX];
      bool key_press_occurred;
      bool key_release_occurred;
    };
    
    
    
    
    
    /**
     * An abstracted mouse class that provides mouse state
     * information. Each framework that wishes to supply mouse
     * functionality is responsible for calling
     * registerButtonPress, registerButtonRelease and
     * updateCoordinates when mouse events occur.
     */
    class CoreMouse{
    public:
      //// @cond
      std::deque<inputEvent> eventBuffer;
      //// @endcond

      CoreMouse();
      
      //// @cond
      virtual const char *objectType() const{
	return "CoreMouse";
      }
      //// @endcond
      
      bool down(int button_code);
      int state(int button_code);
      
      void coordinates(int &x, int &y);
      void previousCoordinates(int &prev_x, int &prev_y);
      void coordinatesDelta(int &dx, int &dy);
      
      bool moved();
      void clearMovedFlag();
      bool buttonPressOccurred();
      void clearButtonPressOccurredFlag();
      bool buttonReleaseOccurred();
      void clearButtonReleaseOccurredFlag();
      
      void updateCoordinates(short int x, short int y);
      void registerButtonPress(int button_code);
      void registerButtonRelease(int button_code); 
        
      void pushInputEvent(int type, int code);
      inputEvent popInputEvent();
      
    private:
      short int buttons[3];
      
      short int x_coordinate;
      short int y_coordinate;
      short int previous_x;
      short int previous_y;
      
      
      bool mouse_moved;
      bool button_press_occurred;
      bool button_release_occurred;
    };
    
  } // Core
} // Mango


#endif // MANGO_CORE_INPUT
