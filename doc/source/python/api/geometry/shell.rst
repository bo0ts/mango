Shell
=====

.. class:: Geometry.Shell(radius=1, thickness-0.1, fraction=0.3, sides=24)

   *Inherits from*: :class:`Geometry.ColorfulObject`

   A (fractional) spherical shell.	


   .. method:: setRadius(radius)
   
      Set the radius of the shell. Must be positive.


   .. method:: setThickness(thickness)
   
      Set the thickness of the shell. Must be positive.


   .. method:: setFraction(fraction)

      Set the fraction of the spherical shell that should be rendered. This 
      parameter takes on floating point values between 0 and 1 and 
      represents the fraction of the sphere (measured from the top of the 
      sphere) that is rendered.


   .. method:: setNumberOfSides(sides)

      Set the number of sides used when rendering the shell.


   .. method:: radius()

      Returns the radius of the shell.


   .. method:: thickness()

      Returns the thickness of the shell.


   .. method:: fraction()
   
      Returns the fraction of the spherical shell that will be rendered as a 
      fraction between 0 and 1 (measured from the top of the shell).


   .. method:: numberOfSides()

      Returns the number of sides used when rendering the shell.
