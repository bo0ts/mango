CoreKeyboard
============


.. class:: Core.CoreKeyboard
   
   Provides access to keyboard state information via the global "Keyboard".


   .. method:: down(key_code)

      Returns True if the key represented by key_code is down, False 
      otherwise.


   .. method:: state(key_code)

      Returns the state of the key represented by key_code, one of the
      constants KEY_STATE_UP or KEY_STATE_DOWN




Key codes for printable characters can be obtained using the builtin method
ord, e.g. ord('a') evaluates to the key-code for 'a' (97). In addition, the 
following key-code constants are available in the global namespace:

KEY_WINDOWS_MENU

KEY_WINDOWS_RIGHT

KEY_WINDOWS_MENU

KEY_WINDOWS_RIGHT

KEY_WINDOWS_LEFT

KEY_NUMPAD_DIVIDE

KEY_NUMPAD_DECIMAL

KEY_NUMPAD_SUBTRACT

KEY_NUMPAD_SEPARATOR

KEY_NUMPAD_ADD

KEY_NUMPAD_MULTIPLY

KEY_NUMPAD_EQUAL

KEY_NUMPAD_DELETE

KEY_NUMPAD_INSERT

KEY_NUMPAD_BEGIN

KEY_NUMPAD_END

KEY_NUMPAD_PAGEDOWN

KEY_NUMPAD_PAGEUP

KEY_NUMPAD_DOWN

KEY_NUMPAD_RIGHT

KEY_NUMPAD_UP

KEY_NUMPAD_LEFT

KEY_NUMPAD_HOME

KEY_NUMPAD_F4

KEY_NUMPAD_F3

KEY_NUMPAD_F2

KEY_NUMPAD_F1

KEY_NUMPAD_ENTER

KEY_NUMPAD_TAB

KEY_NUMPAD_SPACE

KEY_PAGEDOWN

KEY_PAGEUP

KEY_SCROLL

KEY_NUMLOCK

KEY_F24

KEY_F23

KEY_F22

KEY_F21

KEY_F20

KEY_F19

KEY_F18

KEY_F17

KEY_F16

KEY_F15

KEY_F14

KEY_F13

KEY_F12

KEY_F11

KEY_F10

KEY_F9

KEY_F8

KEY_F7

KEY_F6

KEY_F5

KEY_F4

KEY_F3

KEY_F2

KEY_F1

KEY_DIVIDE

KEY_DECIMAL

KEY_SUBTRACT

KEY_SEPARATOR

KEY_ADD

KEY_MULTIPLY

KEY_NUMPAD9

KEY_NUMPAD8

KEY_NUMPAD7

KEY_NUMPAD6

KEY_NUMPAD5

KEY_NUMPAD4

KEY_NUMPAD3

KEY_NUMPAD2

KEY_NUMPAD1

KEY_NUMPAD0

KEY_HELP

KEY_INSERT

KEY_SNAPSHOT

KEY_EXECUTE

KEY_PRINT

KEY_SELECT

KEY_DOWN

KEY_RIGHT

KEY_UP

KEY_LEFT

KEY_HOME

KEY_END

KEY_CAPITAL

KEY_PAUSE

KEY_MENU

KEY_CONTROL

KEY_ALT

KEY_SHIFT

KEY_CLEAR

KEY_MBUTTON

KEY_CANCEL

KEY_RBUTTON

KEY_LBUTTON

KEY_START

KEY_DELETE

KEY_SPACE

KEY_ESCAPE

KEY_RETURN

KEY_ENTER

KEY_TAB

KEY_BACKSPACE
