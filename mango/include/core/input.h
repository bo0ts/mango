#include <vector>
#include <deque>
#include "constants.h"

#ifndef MANGO_CORE_INPUT
#define MANGO_CORE_INPUT

namespace Mango{
  namespace Core{
    
    //typedef std::pair<int, int> inputEventRecord;
    /*
    typedef struct inputEvent{
      int source;
      int type;
      int code;
    } inputEvent;
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
     * An abstracted keyboad class.
     * An abstracted keyboard class that provides individual key state information. Each framework that wishes to
     * supply keyboard functionality is responsible for calling registerKeyPress(...) and registerKeyRelease(...)
     * when key presses occur.
	   */
    class CoreKeyboard{
    public:
      std::deque<int> typedKeyBuffer;
      std::deque<inputEvent> eventBuffer;

      CoreKeyboard();
      ~CoreKeyboard();

      virtual const char *objectType() const{
	return "CoreKeyboard";
      }
            
      bool down(int key_code);
      short int state(int key_code);
      void suppress(int key_code);

      bool keyPressOccurred();
      void clearKeyPressOccurredFlag();
      bool keyReleaseOccurred();
      void clearKeyReleaseOccurredFlag();
      
      void registerKeyPress(int key_code);
      void registerKeyRelease(int key_code);
      
      void pushInputEvent(int type, int code);
      inputEvent popInputEvent();
      //bool eventOccured();                    // uncomment if needed 
      //void clearEventOccuredFlag(); 		  // uncomment if needed
	    
    private:
      int keys[MAX_KEYCODE_INDEX];
      bool suppressed_keys[MAX_KEYCODE_INDEX];
      bool key_press_occurred;
      bool key_release_occurred;
    };
    
    
    
    
    
    /**
     * An abstracted mouse class.
     * An abstracted mouse class that provides mouse state information. Each framework that wishes to
     * supply mouse functionality is responsible for calling registerButtonPress(...), registerButtonRelease(...)
     * and updateCoordinates(...) when mouse events occur.
     */
    class CoreMouse{
    public:
      std::deque<inputEvent> eventBuffer;

      CoreMouse();
      
      virtual const char *objectType() const{
	return "CoreMouse";
      }
      
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
