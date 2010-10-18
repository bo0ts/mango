CoordinateSystem
================

.. class:: Geometry.CoordinateSystem

   *Inherits from*: :class:`Geometry.ColorfulObject`

   .. method:: setAxisThickness(thickness)

      Sets the thickness of each axis. Must be positive.      
   

   .. method:: setAxisLength(length)

      Sets the length of each axis. Must be positive.


   .. method:: setRightHanded(right_handed)

      When passed True, causes the coordinate system to be rendered right 
      handed (the default behavior). When passed false, causes the 
      coordinate system to be rendered left handed.


   .. method:: axisThickness()

      Returns the axis thickness.   


   .. method:: axisLength()

      Returns the axis length.


   .. method:: rightHanded()

      Returns True if the coordinat system is set to render as a right-handed
      coordinate system and False otherwise.
