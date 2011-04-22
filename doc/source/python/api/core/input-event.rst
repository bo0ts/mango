Input Event
===========

.. class:: Core.InputEvent(source, code, type)
   
   Encapsulates an input event. InputEvent instances can 
   be compared, where two input events match if and only if their sources, 
   codes and types match and a value of ANY functions as a wild card.

   .. attribute:: source

      Should equal one of KEYBOARD, MOUSE or ANY


   .. attribute:: code
   
      A key-code (keyboard) or button-code (mouse), or ANY. See 
      :class:`Core.CoreKeyboard` for valid key-codes and 
      :class:`Core.CoreMouse` for valid button-codes. 


   .. attribute:: type

      Should equal one of PRESS (alias CLICK), RELEASE or ANY