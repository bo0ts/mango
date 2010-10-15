Matrix
======

.. class:: Core.Matrix((a00, a01, a02), (a10, a11, a12), (a20, a21, a22))

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

