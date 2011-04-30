VertexArray
===========

.. class:: Geometry.VertexArray

   *Inherits from*: :class:`Geometry.ColorfulObject`

   An array of vertices that are rendered in order. The rendering style
   determines the final result. For instance to render a collection of points
   use GL_POINTS, to render a continuous line use GL_LINE_STRIP while
   GL_POLYGON can be used to render a polygon.


   .. method:: add(vertex)

      Add a vertex to the array. vertex should be a Vector or tuple of 
      doubles.


   .. method:: removeAt(index)

      Remove the vertex at the given index.


   .. method:: insertAt(index, vertex)

      Insert a vertex at the given index. vertex should be a Vector or tuple
      of doubles.


   .. method:: size()

      Returns the size of the array.      


   .. method:: setStyle(rendering_style)

      Set the rendering style of the array. See :meth:`OpenGL.glBegin` for a
      list of available rendering styles. The default style is GL_LINE_STRIP.


   .. method:: setRenderReverseOrientation(render_reverse)

      If passed True, the array will render in both orientation (and so it
      will be visible from both sides. This is the default behavior). When
      passed false, only one orientation will be rendered.


   .. method:: style()

      Returns the rendering style of the vertex array.


   .. method:: renderReverseOrientation()

      Returns True if the vertex array is set to render both orientations, 
      False otherwise.
