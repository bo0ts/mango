Knwon Issues
============

A few surprise features that crept in at the last minute

Memory Management and Reference Counting 
-----------------------------------------

Under certain circumstances, it is possible that the garbage collector will
attempt to deallocate objects prematurely. This happens due to a failure of 
Mango to increment the retain count for objects with events (the retain
count is incremented for the method that Mango intends to call, but not for
the object that owns the method). In order to prevent this, make sure to
keep a reference to every object you create. For instance, the following is
not good practice in this version of Mango:

.. code-block:: python

  import Geometry
 
  for i in range(10):
      sphere = Geometry.Sphere() # Bad practice, each new sphere replaces previous one
      sphere.set(RENDER)

The problem with the above snippet is that no reference is retained to the 
the first 9 sphere objects created. The solution is simple - store the
objects in a list:

.. code-block:: python
   
  import Geometry
 
  spheres = []
  for i in range(10):
      sphere = Geometry.Sphere() 
      sphere.set(RENDER)
      spheres.append(sphere) # All spheres now live in the list 'spheres'

Equivalently:

.. code-block:: python
   
  import Geometry
 
  spheres = [Geometry.Sphere() for i in range(10)] # Again, all spheres live in 'spheres'
  for sphere in spheres:
      sphere.set(RENDER)


Position Components
-------------------

Be careful about setting an object's position: you cannot set an individual
component directly. The following works as expected:

.. code-block:: python

  obj = Core.Object()  
  print(obj.position) # prints "<0.00, 0.00, 0.00>"
  obj.position = (1, 2, 3)
  print(obj.position) # prints "<1.00, 2.00, 3.00>"

But this snippet does not:

.. code-block:: python

  obj = Core.Object()
  print(obj.position) # prints "<0.00, 0.00, 0.00>"
  obj.position[2] = 3
  print(obj.position) # prints "<0.00, 0.00, 0.00>" instead of "<0.00, 0.00, 3.00>"

You will have to do something like this instead:

.. code-block:: python

  obj = Core.Object()
  print(obj.position) # prints "<0.00, 0.00, 0.00>"
  pos = obj.position
  pos[2] = 3
  obj.position = pos
  print(obj.position) # prints "<0.00, 0.00, 3.00>"

or the one-liner:

.. code-block:: python

  obj = Core.Object()
  print(obj.position) # prints "<0.00, 0.00, 0.00>"
  obj.position += (0, 0, -obj.position[2] + 3.00)
  print(obj.position) # prints "<0.00, 0.00, 3.00>"

The problem is with the underlying implementation of the position attribute.
Attempting to set a component directly invokes the position getter first, 
which returns a copy of the Vector instance representing the object's
position for which the specified component is then set. 

