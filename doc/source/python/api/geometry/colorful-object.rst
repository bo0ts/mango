ColorfulObject
==============

.. class:: Geometry.ColorfulObject

   *Inherits from*: :class:`Core.Object`

   An object with a color attribute that functions as the base class
   for all objects in the Geometry module. All color components take
   floating point values between 0 and 1.

   .. method:: setRedComponent(red)
      
      Set the red component of the object's color.


   .. method:: setGreenComponent(green)

      Set the green component of the object's color.


   .. method:: setBlueComponent(blue)   

      Set the blue component of the object's color.


   .. method:: setColor(red, green, blue)

      Set the color of the object. Also accepts a tupple, e.g. 
      setColor((r, g, b))


   .. method:: redComponent()

      Returns the red component of the object's color.


   .. method:: greenComponent()

      Returns the green component of the object's color.


   .. method:: blueComponent()

      Returns the blue component of the object's color.

   
   .. method:: color()

      Returns a tuple (r, g, b) containing all three color components.

