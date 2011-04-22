Rectangle
=========

.. class:: Geometry.Rectangle(width=1, length=1.618)

   *Inherits from*: :class:`Geometry.ColorfulObject`

   .. method:: setWidth(width)
      
      Set the width of the rectangle (measured along the x-axis). Must be
      positive.


   .. method:: setLength(length)

      Set the length of the rectangle (measured along the y-axis). Must be
      positive.


   .. method:: setDimensions(width, length)

      Set the width and length of the rectangle.


   .. method:: setStyle(rendering_style)
   
      Set the rendering style of the rectangle. GL_LINE_LOOP, the default, 
      will cause only the outline to be rendered whereas GL_POLYGON will 
      cause a filled rectangle to be rendered.


   .. method:: setRenderReverseOrientation(render_reverse)

      If passed True, the rectangle will render in both orientation (and so 
      it will be visible from both sides. This is the default behavior). When
      passed false, only one orientation will be rendered.


   .. method:: width()

      Returns the width of the dress.


   .. method:: length()

      Returns the length of the dress.


   .. method:: style()

      Returns the rendering style of the rectangle.


   .. method:: renderReverseOrientation()

      Returns True if the rectangle is set to render both orientations, False
      otherwise.