Vectors
=======

Mango uses instances of the class Vector to represent points in three 
dimensional space. For example, to create a vector with the coordinates 
(2, 3, 1):

.. code-block:: python
  
  v = Vector(2, 3, 1.2)

  print(v) # prints "<2.00, 3.00, 1.20>"

Vectors behave like tupples with some additional functionality. You can add
and subtract vectors, multiply them by numbers, and access their components
individually:

.. code-block:: python
  
  v = Vector(1, 3, 0)
  w = Vector(0, 2, 5)

  print(v + w) # prints "<1.00, 5.00, 5.00>"
  print(v - w) # prints "<1.00, 1.00, -5.00>"
  print(2*v)   # prints "<2.00, 6.00, 0.00>"
  print("x-component of v is", v[0]) # prints "x-component of v is 1.0"

Most methods or attributes that take vector arguments also accept tuples in
their stead, which will be implicitly converted into vectors. For instance,
both of the following lines are valid ways of setting an object's position:

.. code-block:: python

  obj = Core.Object()

  obj.position = Vector(1, 2, 3)
  print(obj.position) # prints "<1.00, 2.00, 3.00>"
  
  obj.position = (4, 5, 6)
  print(obj.position) # prints "<4.00, 5.00, 6.00>"

Note in particular that even tough obj.position is set to a tuple in the 
6th line, it has been converted into a vector (this is indicated by the
angular brackets, a tuple would print surrounded by parentheses). 

When working in two dimensions, just leave off the last coordinate - it will
be automatically set to 0:

.. code-block:: python

  obj = Core.Object()
  
  obj.position = Vector(1, 2)
  print(obj.position) # prints "<1.00, 2.00, 0.00>"
  
  obj.position = (4, 5)
  print(obj.position) # prints "<4.00, 5.00, 0.00>"


Vectors also provide methods to normalize a vector or obtain the norm of a 
vector or the dot or cross product of two vectors. Consult the API for
more details.


