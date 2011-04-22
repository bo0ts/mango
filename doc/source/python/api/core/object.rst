Core.Object
===========

.. class:: Core.Object

   *Inherits from*: :class:`Core.Frame`

   The base class for all event-capable objects. The events supported by
   this class are step, render, draw, input (none of them do anything).
   Derived classes should override these methods to control object behavior.
   
   .. method:: set(event_mask)

      Set the events described by event_mask, one or a bitwise-or'ed
      combination of STEP, INPUT, RENDER or DRAW. Setting an event does not 
      affect previously set events. Setting an event that has been set has 
      no effect

   
   .. method:: unset(event_mask)

      Unset the events described by event_mask. See :meth:`set` for a list
      of event constants


   .. method:: toggle(event_mask)

      Toggle the events described by event_mask. Events included in 
      event_mask that are unset will be set, and those that are set will be
      unset

      
   .. method:: executes(event)

      Returns True if event is set, False otherwise.

      
   .. method:: step()
   
      The step event callback, an empty implementation.

      
   .. method:: input()
   
      The step event callback, an empty implementation.

      
   .. method:: render()
   
      The step event callback, an empty implementation.

      
   .. method:: draw()
   
      The step event callback, an empty implementation.


