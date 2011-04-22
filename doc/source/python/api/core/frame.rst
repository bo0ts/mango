Frame
=====

.. class:: Core.Frame
   
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