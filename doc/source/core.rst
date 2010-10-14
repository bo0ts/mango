Core
====


.. module:: Core
   :synopsis: core objects and methods
 
.. class:: Object

   *Inherits from*: :class:`Frame`

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


.. class:: CoreEngine
   
.. class:: CoreCamera

.. class:: CoreMouse

.. class:: CoreKeyboard

.. class:: Error

.. class:: ValueError
 
.. class:: IndexError

.. class:: EnvironmentError

.. class:: Frame
   
   A frame of reference. 

   .. attribute:: position

      The position of the frame, a vector.


   .. attribute:: alpha

      The first orientation angle of the frame, in degrees.

   
   .. attribute:: beta

      The second orientation angle of the frame, in degrees.


   .. attribute:: gamma

      The third orientation angle of the frame, in degrees.


   .. method:: setOrientationAxes(u1, u2, u3)
      
      Set new orientation axes for the frame. u1, u2, and u3 should be 
      vectors. A frame's orientation is determined by translating it to its 
      position [from the GlobalFrame], and rotating it: by the first 
      orientation angle (:attr:`alpha`) around the first orientation axis 
      (u1), then by the second orientation angle (:attr:`beta`) around the 
      second orientation axis (u2), and finally by the third orientation 
      angle (:attr:`gamma`) around the third orientation axis (u3). The 
      default orientation axes are, in order: (0, 1, 0), (1, 0, 0), 
      (0, 1, 0).


   .. method:: setOrientation(alpha, beta, gamma)
      
      Set the orientation of the frame. The orientation of the frame is 
      determined by rotating the frame of reference by :attr:`alpha` around
      the y-axis, then by :attr:`beta` around the z-axis, and finally by 
      :attr:`gamma` around the z-axis (assuming the orientation axes are the 
      default. See :meth:`setOrientationAxes`)


   .. method:: rotate(dalpha, dbeta=0, dgamma=0)

      Rotate the frame of reference by adding dalpha, dbeta and dgamma
      to alpha, beta and gamma respectively.    


   .. method:: translate(v)

      Translate the frame of reference by adding v to the frame's position


   .. method:: rotationFromParent()

      Return a :class:`Matrix` representing the rotation of the frame of
      reference from the global orientation to the local one.


   .. method:: rotationToParent()

      Return a :class:`Matrix` representing the rotation of the frame of
      reference from the global orientation to the local one.


   .. method:: transformToParent(v)

      Transforms the vector v from the local frame of reference to the frame 
      of reference of the parent. That is to say, returns a vector w that 
      represents the same point in space with w's coordinates relative to the
      parent frame of reference as the vector v does with coordinates
      relative to the local frame of reference.


   .. method:: transformToAncestor(v, ancestor_frame)
   
      Transforms the vector v to the frame of reference ancestor_frame, which
      must be an ancestor of the current frame (ValueError raised otherwise)


   .. method:: transformFromParent(v)

      Transforms the vector v from the parent frame of reference to the local
      frame of reference. That is to say, returns a vector w that represents
      the same point in space with w's coordinates relative to the local
      frame of reference as the vector v does with coordinates relative to 
      the parent frame of reference

   
   .. method:: trasnfromFromAncestor(v, ancestor_frame)
   
      Transforms the vector v from the frame of reference ancestor_frame, 
      which must be an ancestor of the current frame (ValueError raised 
      otherwise)


   .. method:: orientationFor(v)

      Returns a tuple (alpha, beta) that represents the first and second
      orientation angles that would align the y-axis of the current frame
      with the vector v (v interpreted relative to the global frame)


   .. method:: pointTo(v)

      Equivalent to:
        frame.alpha, frame.beta = frame.orientationFor(v)


   .. method:: parentFrame()
   
      Returns the parent frame of the current frame. Defaults to the global
      frame for all frames but the global frame, whose parent is None.


   .. method:: setParentFrame(new_parent)

      Set the parent frame of the current frame. new_parent can be a Frame
      instance or any object derived from it (e.g. Core.Object, 
      Geometry.Sphere, etc). Becareful of creating loops (frame A
      is the parent of frame B which is the parent of frame C which is the 
      parent of frame A) and do not try to set the parent frame of the global
      frame (this will cause a loop).


   .. method:: hasFrameAsAncestor(suspect_frame)

      Returns True if suspect_frame is a parent of the current frame, False
      otherwise.


   .. method transform()

      Transforms the current rendering point (using glTranslate and glRotate)
      by translating to the current frame's position and then rotating 
      according to the orientation angles. 

   .. reverseTransform()

      Performs the inverse transformation than that performed by 
      :meth:transform.

.. class:: InputEvent

.. class:: Matrix((a00, a01, a02), (a10, a11, a12), (a20, a21, a22))

   Represents a linear transformation in 3D space. Each argument is a tuple
   containing the three components of one row in the matrix. The constructor
   also accomodates 2D, e.g. m = Matrix((a00, a01), (a10, a11)). 

   Matrices can be compared (A == B), added (A + B), subtracted (a - b), 
   inverted (-A), scaled (3*A, A/2).


   .. method:: transform(K)

      Applies the transformation represented by this matrix instance to K and
      returns the result (algebraically equivalent to multiplying by K on the
      right, e.g. M*K). K may be a vector or another matrix. This may also
      be accomplished by calling the matrix as a function, i.e. M(K) = 
      M.transform(K)


   .. method:: rightTransform(K)

      Applies the transpose of the transformation represented by this matrix
      instance to K and returns the result (algebraically equivalent to
      multiplying by K on the left, e.g. K*M). K may be a vector or another
      matrix. 


   .. method:: tr()
   
      Returns the trace of the matrix


   .. method:: det()

      Returns the determinant of the matrix

      	      	  	            

.. class:: Vector(x, y, z=0)

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