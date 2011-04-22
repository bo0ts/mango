Vector
======

.. class:: Core.Vector(x, y, z=0)

   Represents a point in 3D space. Components can be accessed using indices, 
   e.g. access the y component of v = Vector(1, 2) by v[1]. Vectors can be
   compared (v == w), added (v + w), subtracted (v - w), inverted (-v), 
   scaled (3*v, v/2).


   .. method:: norm()
      
      Returns the norm of the vector


   .. method:: normSq()
   
      Returns the square of the norm of the vector
   

   .. method:: normalize()

      Normalizes the vector in place (returns None)


   .. method:: dot(w)

      Returns the dot product of the vector with w. Can also be invoked
      by calling the vector as a function, e.g. for vectors v, w, v(w) is
      equivalent v.dot(w)

   
   .. method:: cross(w)

      Returns the cross product of the vector with w