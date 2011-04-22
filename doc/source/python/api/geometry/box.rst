Box
===

.. class:: Geometry.Box(w=1, h=1, l=1)

   *Inherits from*: :class:`Geometry.ColorfulObject`

   .. method:: setDimensions(w, h, l)

      Set the dimensions of the box. Also accepts a tuple, e.g. 
      setDimensions((w, h, l)). Width is measured along the x-axis, height
      along the y-axis and length along the z-axis.

   .. method:: dimensions()

      Returns a tuple (w, h, l) containing the dimensions of the box.