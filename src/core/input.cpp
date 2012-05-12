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
#include <mango/core/input.h>
#include <iostream>


namespace Mango{
  namespace Core{

    /*
      CoreKeyboard
    */
		
    /**
     * Creates a CoreKeyboard object with all key states set to KEY_STATE_UP
     */
    CoreKeyboard::CoreKeyboard(){
      for (int i=0; i <= MAX_KEYCODE_INDEX; i += 1){
	keys[i] = KEY_STATE_UP;
	suppressed_keys[i] = false;
      }
    }

    CoreKeyboard::~CoreKeyboard(){
    }
		
    /**
     * Returns true if the key with key code key_code is in the down
     * state (KEY_STATE_DOWN). For printable characters, this is
     * generally identical to the character's ASCII code.  Most
     * nonprintable characters have constants associated with them
     * (see the keyboard constants for more info).
     *
     * @see down
     * @see state
     */
    bool CoreKeyboard::down(int key_code){
      return (keys[key_code] == KEY_STATE_DOWN);
    }
		
    /**
     * Returns KEY_STATE_DOWN or KEY_STATE_UP, depending on the state 
     * of the key with the given code. 
     *
     * @see down
     */
    short int CoreKeyboard::state(int key_code){
      return keys[key_code];
    }
		
    void CoreKeyboard::suppress(int key_code){
      suppressed_keys[key_code] = true;
    }

    /**
     * Return true if a key press has occurred since the last time
     * clearKeyPressOccurredFlag was called. If input events are
     * enabled, the key-press-occurred flag will be cleared after all
     * input events have been issued for the current step (see
     * CoreEngine::EnableInputEvents for more details). If input
     * events are disabled, whether clearKeyPressOccurredFlag is
     * called automatically or not depends on intermediate os layer in
     * use - in particular, mango-on-glut does call it automatically
     * after all other object events have been executed. 
     *
     * @see clearKeyPressOccurredFlag
     * @see keyReleaseOccurred
     * @see clearKeyReleaseOccurredFlag
     */
    bool CoreKeyboard::keyPressOccurred(){
      return key_press_occurred;
    }
		
    /**
     * Clear the key-press-occurred flag, causing keyPressOccurred
     * to return false until a key press occurs. Depending on several
     * factors, this function may or may not be called automatically -
     * see keyPressOccurred for more details.
     *
     * @see keyPressOccurred
     * @see keyReleaseOccurred
     * @see clearKeyReleaseOccurredFlag
     */
    void CoreKeyboard::clearKeyPressOccurredFlag(){
      key_press_occurred = false;
    }
		
    /**
     * Return true if a key release has occurred since the last time
     * clearKeyReleaseOccurredFlag was called. The same
     * considerations apply to this function as to keyPressOccurred.
     *
     * @see clearKeyReleaseOccurredFlag
     * @see keyPressOccurred
     * @see clearKeyPressOccurredFlag
     */
    bool CoreKeyboard::keyReleaseOccurred(){
      return key_release_occurred;	
    }
		
    /**
     * Clear the key-release-occurred flag, causing
     * keyReleaseOccurred to return false until a key release
     * occurs. Depending on several factors, this function may or may
     * not be called automatically - see keyPressOccurred for more
     * details.
     *
     * @see keyReleaseOccurred
     * @see keyPressOccurred		
     * @see clearKeyPressOccurredFlag
     */
    void CoreKeyboard::clearKeyReleaseOccurredFlag(){
      key_release_occurred = false;	
    }
				
				
    /**
     * Register a key press by setting the key state to
     * KEY_STATE_DOWN.  This also (always) sets the key-press-ccurred
     * flag.     
     *
     * @see registerKeyRelease
     */
    void CoreKeyboard::registerKeyPress(int key_code){
      keys[key_code] = KEY_STATE_DOWN;
      if (!suppressed_keys[key_code]){
	pushInputEvent(PRESS, key_code);
      }
      key_press_occurred = true;
    }
		
    /**
     * Register a key release by setting the key state to
     * KEY_STATE_UP. This also (always) sets the key-release-occurred
     * flag.
     *
     * @see registerKeyPress
     */
    void CoreKeyboard::registerKeyRelease(int key_code){		  
      keys[key_code] = KEY_STATE_UP;
      suppressed_keys[key_code] = false;
      key_release_occurred = true;
      pushInputEvent(RELEASE, key_code);      
    }
		
    /**
     * Push an input event.
     * 
     */
    void CoreKeyboard::pushInputEvent(int type, int code){
      inputEvent event;
      event.source = KEYBOARD;
      event.type = type;
      event.code = code;
      eventBuffer.push_back(event);
      if (eventBuffer.size() > INPUT_EVENT_BUFFER_SIZE){
	eventBuffer.pop_front();
      }
    }

    /**
     * Pop an input event.
     */
    inputEvent CoreKeyboard::popInputEvent(){
      inputEvent event = eventBuffer.front();
      return event;
    }


		
		
		
		
		
		
		

    /*
      CoreMouse
    */
		
    /**
     * Create a CoreMouse object with all button states set to
     * BUTTON_STATE_UP and current and previous mouse coordinates set
     * to (0, 0).
     */
    CoreMouse::CoreMouse(){
      mouse_moved = false;
		
      buttons[BUTTON_LEFT] = KEY_STATE_UP;
      buttons[BUTTON_RIGHT] = KEY_STATE_UP;
      buttons[BUTTON_MIDDLE] = KEY_STATE_UP;
		
      x_coordinate = 0;
      y_coordinate = 0;
      previous_x = 0;
      previous_y = 0;
    }
		
    /**
     * Return true if the button with the given code is in
     * the down state (BUTTON_STATE_DOWN).
     *
     * @param button_code      
     *   one of BUTTON_LEFT, BUTTON_RIGHT
     *
     * @see down
     */
    bool CoreMouse::down(int button_code){
      return (buttons[button_code] == BUTTON_STATE_DOWN);
    }
		
    /**
     * Return the state of the button with the given code.
     *
     * @return 
     *   BUTTON_STATE_UP, BUTTON_STATE_DOWN or BUTTON_STATE_CLEAR
     */
    int CoreMouse::state(int button_code){
      return buttons[button_code];
    }
		
    /**     
     * Retrieve the current coordinates of the mouse by assigning them
     * to two variables passed by reference. Mouse coordinates are
     * relative to the top-left corner of the screen.     
     */
    void CoreMouse::coordinates(int &x, int &y){
      x = x_coordinate;
      y = y_coordinate;
    }
		
    /**
     * Retrieve the previous coordinates of the mouse by assigning
     * them to two variables passed by reference. "Previous" means the
     * mouse coordinates as they were prior to the last update
     * performed using updateCoordinates (this function should be
     * called automatically by the intermediate os layer in use).
     */
    void CoreMouse::previousCoordinates(int &prev_x, int &prev_y){
      prev_x = previous_x;
      prev_y = previous_y;
    }
		
    /**
     * Retrieve the change in coordinates of the mouse by assigning
     * them to two variables passed by reference. the change in
     * coordinates is equal, in each component, to the current value
     * minus the previous value.
     */
    void CoreMouse::coordinatesDelta(int &dx, int &dy){
      dx = x_coordinate - previous_x;
      dy = y_coordinate - previous_y;
    }
						
    /**
     * Return true if the mouse has moved in the previous frame. In
     * full generality, this function will return true only if
     * updateCoordinates has been called since the last time
     * clearMouseMovedFlag has been called, and with new
     * coordiantes. Depending on the intermediate os layer in use,
     * clearMouseMovedFlag may be called automatically after every
     * frame, so that this function will return true only if the mouse
     * has moved in the previous frame. This is true of mango-on-glut.
     */
    bool CoreMouse::moved(){
      return mouse_moved;
    }
		
    /**
     * Clear the moues-moved flag, so that subsequent calls to
     * mouseMoved will return false until the mouse is moved
     * again.
     */
    void CoreMouse::clearMovedFlag(){
      mouse_moved = false;
    }

    /**
     * Return true if a button press has occurred since the last time
     * clearButtonPressOccurredFlag was called. Whether
     * clearButtonPressOccurredFlag is called automatically or not
     * depends on the intermediate os layer in use - in particular,
     * mango-on-glut does call it automatically after all other object
     * events have been executed. 
     *
     * @see clearButtonPressOccurredFlag
     * @see buttonReleaseOccurred
     * @see clearButtonReleaseOccurredFlag
     */
    bool CoreMouse::buttonPressOccurred(){
      return button_press_occurred;
    }
		
    /**
     * Clears the button-press-occurred flag, causing
     * buttonPressOccurred to return false until a button press
     * occurs. Depending on several factors, this function may or may
     * not be called automatically - see buttonPressOccurred for
     * more details.
     *
     * @see buttonPressOccurred
     * @see buttonReleaseOccurred	
     * @see clearButtonReleaseOccurredFlag
     */
    void CoreMouse::clearButtonPressOccurredFlag(){
      button_press_occurred = false;
    }
		
    /**
     * Returns true if a button release has occurred since the last
     * time clearButtonReleaseOccurredFlag was called. The same
     * considerations apply to this function as to
     * buttonPressOccurred.
     *
     * @see clearButtonReleaseOccurredFlag
     * @see buttonPressOccurred
     * @see clearButtonPressOccurredFlag
     */
    bool CoreMouse::buttonReleaseOccurred(){
      return button_release_occurred;	
    }
		
    /**
     * Clear the button-release-occurred flag, causing
     * buttonReleaseOccurred to return false until a button release
     * occurs. Depending on several factors, this function may or may
     * not be called automatically - see buttonPressOccurred for
     * more details.
     *
     * @see buttonReleaseOccurred
     * @see buttonPressOccurred
     * @see clearButtonPressOccurredFlag
     */
    void CoreMouse::clearButtonReleaseOccurredFlag(){
      button_release_occurred = false;	
    }


    /**
     * Set the mouse coordinates. The coordinates should be relative
     * to the top-left corner of the window. If the new coordiantes
     * are different than the old coordinates, this causes the
     * mouse-moved flag to be set to true.
     */
    void CoreMouse::updateCoordinates(short int x, short int y){
      previous_x = x_coordinate;
      previous_y = y_coordinate;
      if ((x != x_coordinate) || (y != y_coordinate)){
	mouse_moved = true;
      }
      x_coordinate = x;
      y_coordinate = y;
    }
		
    /**
     * Register a button press by setting the button state to
     * BUTTON_STATE_DOWN. This also (always) sets the
     * button-press-occurred flag.
     *
     * @see registerButtonRelease
     * @see buttonPressOccurred
     */
    void CoreMouse::registerButtonPress(int button_code){
      buttons[button_code] = BUTTON_STATE_DOWN;
      button_press_occurred = true;
      pushInputEvent(CLICK, button_code);
    }
		
    /**
     * Register a button release by setting the button state to
     * BUTTON_STATE_UP. This also (always) sets the
     * button-release-occurred flag.
     *
     * @see registerButtonPress
     * @see buttonReleaseOccurred
     */
    void CoreMouse::registerButtonRelease(int button_code){
      buttons[button_code] = KEY_STATE_UP;
      pushInputEvent(RELEASE, button_code);
    }						

    /**
     * Push an input event.
     * 
     */
    void CoreMouse::pushInputEvent(int type, int code){
      inputEvent event;
      event.source = MOUSE;
      event.type = type;
      event.code = code;
      eventBuffer.push_back(event);
      if (eventBuffer.size() > INPUT_EVENT_BUFFER_SIZE){
	eventBuffer.pop_front();
      }
    }

    /**
     * Pop an input event.
     */
    inputEvent CoreMouse::popInputEvent(){
      inputEvent event = eventBuffer.front();
      return event;
    }
		
  } // Core
} // Mango
		
