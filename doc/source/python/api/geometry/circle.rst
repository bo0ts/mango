Circle
======

.. class:: Geometry.Circle(r=1.0, num_sides=24)

   *Inherits from*: :class:`Geometry.ColorfulObject`

   .. method:: setRadius(r)

      Set the radius of the circle. Must be positive.      


   .. method:: setStyle(rendering_style)
   
      Set the rendering style of the circle. GL_LINE_LOOP, the default, will
      cause only the outline to be rendered whereas GL_POLYGON will cause
      a filled circle to be rendered.


   .. method:: setNumberOfSides(sides)

      Set the number of sides used when rendering the circle.


   .. method:: setRenderReverseOrientation(render_reverse)
      
      If passed True, the circle will render in both orientation (and so it
      will be visible from both sides. This is the default behavior). When
      passed false, only one orientation will be rendered.


   .. method:: radius()

      Returns the radius of the circle.


   .. method:: style()

      Returns the rendering style of the circle.


   .. method:: numberOfSides()

      Returns the number of sides of the circle.


   .. method:: renderReverseOrientation()

      Returns True if the circle is set to render both orientations, False
      otherwise.

      