Arrow
=====

.. class:: Geometry.Arrow(length=1, thickness=0.1)

   *Inherits from*: :class:`Geometry.ColorfulObject`

   .. method:: setThickness(thickness)

      Set the thickness of the arrow (width of one side of the square shaft).
      Must be positive.      


   .. method:: setLength(length)

      Set the length of the arrow (must be positive).


   .. method:: setTipPosition(v)

      Set the length and reorient the arrow so that it's tip will be located
      at the point v. v is a vector that is interpreted relative to the 
      parent frame, translated to the position of the arrow (so at the base
      of the arrow but with the parent's orientation). 


   .. method:: thickness()
   
      Returns the thickness of the arrow.


   .. method:: length()

      Returns the length of the arrow.