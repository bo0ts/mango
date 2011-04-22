Tips and Tricks
===============

This section details a few tips and tricks that may prove useful when
writing simulations.

Object Initialization
---------------------
Sometimes it is convenient or necessary to override the __init__ method of
a class. When doing so, be sure to call the parent's __init__ method, 
otherwise Bad Things may happen:

.. code-block:: python

  class Person(Core.Object):
  	def __init__(self, name):
	    Core.Object.__init__(self) # Invoke parent's init passing self
	    self.name = name	    	    	    

  great_columnist = Person("Dave Barry")

Grouping Objects
----------------
With just a little bit of extra code it is possible to create an object
that is composed of several other objects but behaves as one cohesive 
"group". The key points are:

 * Override the init method of the parent object and create the child
   components, setting the parent object as the parent frame of each 
   component
 * Override the parent's method set, so that events set for the parent are
   propagated to the child components

Let's try out hand at making a tree:

.. code-block:: python
   
  import Geometry
  
  class Tree(Core.Object):
      trunk = Geometry.Cylinder()
      foliage = Geometry.Sphere()
  
      def __init__(self, trunk_height = 1.0, foliage_radius = 1.0):
          Core.Object.__init__(self)
          
          self.trunk.setColor(0.5, 0.25, 0)
          self.trunk.setRadius(trunk_height / 10.0)
          self.trunk.setHeight(trunk_height)
          
          self.foliage.setColor(0.0, 0.8, 0.0)
          self.foliage.setRadius(foliage_radius)
          self.foliage.position = (0, trunk_height/2.0 + foliage_radius, 0)
          
          self.trunk.setParentFrame(self)
          self.foliage.setParentFrame(self)
  
      def set(self, mask):
          Core.Object.set(self, mask)
          self.trunk.set(mask)
          self.foliage.set(mask)    
  
  t = Tree()
  t.set(RENDER)
  
Viola, a tree:

  .. image:: /images/group-tree-example.png
     :width: 480
     :height: 360

A more complete implementation also overrides the methods unset and toggle,
otherwise the parent object will behave inconsistently: set will set an
event for the parent and children, while unset/toggle will only act on the
parent. Here is the full version:


.. code-block:: python
   
  import Geometry
  
  class Tree(Core.Object):
      trunk = Geometry.Cylinder()
      foliage = Geometry.Sphere()
  
      def __init__(self, trunk_height = 1.0, foliage_radius = 1.0):
          Core.Object.__init__(self)
          
          self.trunk.setColor(0.5, 0.25, 0)
          self.trunk.setRadius(trunk_height / 10.0)
          self.trunk.setHeight(trunk_height)
          
          self.foliage.setColor(0.0, 0.8, 0.0)
          self.foliage.setRadius(foliage_radius)
          self.foliage.position = (0, trunk_height/2.0 + foliage_radius, 0)
          
          self.trunk.setParentFrame(self)
          self.foliage.setParentFrame(self)
  
      def set(self, mask):
          Core.Object.set(self, mask)
          self.trunk.set(mask)
          self.foliage.set(mask)    
 
      def unset(self, mask):
          Core.Object.unset(self, mask)
          self.trunk.unset(mask)
          self.foliage.unset(mask)    
 
      def toggle(self, mask):
          Core.Object.toggle(self, mask)
          self.trunk.toggle(mask)
          self.foliage.toggle(mask)    
 
  t = Tree()
  t.set(RENDER)


Modularization
--------------

The design of Mango is intended to encourage modularization. For instance,
if we take the implementation of the Tree class from the previous example 
and save it as tree.py (everything but the last two lines which instantiate
a tree and set its render event), we can then import the tree module from
another script:

.. code-block:: python

  from tree import Tree
  from random import random
  
  num = 25
  positions = [(-2.5 + 5*random(), 0, -2.5 + 5*random()) 
               for i in range(num)]
  trunk_sizes = [0.5 + 0.2 * random() for i in range(num)]
  foliage_sizes = [0.2 + 0.2 * random() for i in range(num)]
  
  forest = []
  for pos, height, radius in zip(positions, trunk_sizes, foliage_sizes):
      tree = Tree(height, radius)
      tree.position = pos
      tree.set(RENDER)
      forest.append(tree)
  
  Camera.lookFrom((0, 0, 0), (0, 2, 7))
    
And here is a nice forest:

  .. image:: /images/forest.png
     :width: 480
     :height: 360

Linear Transformations
----------------------

Mango contains an implementation of matrices. It is not particularly fast or
extensive, but it covers the basics:

.. code-block:: python

  m = Core.Matrix([0, -1, 0], 
                  [1, 0, 0], 
                  [0, 0, 1])
  v = Vector(1, 2, 3)
  print(m(v)) # prints "<-2.00, 1.00, 3.00>"
  
Note that m is used as a function, with the vector v passed in as an
argument. 

