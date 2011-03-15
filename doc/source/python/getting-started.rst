Getting Started
===============
This tutorial will show you the basics of writing Mango simulations.


.. _getting-started-python-box:

A Box
------

Let us try our hand at our first Mango simulation, a "hello world" of sorts. Using your
favorite text editor, save the following script as hello_box.py:

.. code-block:: python
   
   import Geometry

   b = Geometry.Box()
   b.set(RENDER)

You can run this script from the command-line using the following 
command:: 

  mango hello_box.py

When run, the simulation window should appear. Congratulations, you have just written
your first simulation! You might consider showing it to your mom. Use the 
right mouse button to rotate the view around, the left mouse button to pan, and hold
down both and drag to zoom (alternatively, press the 'r' button and drag the left
mouse button to rotate or press the 'z' button and drag the left mouse button to zoom). 
You should be looking at something like:

  .. image:: /images/hello_box1.png
     :width: 360
     :height: 240

Now this is a simple script, but since this is our first, let's break it down:

The first and third lines are probably obvious: the first imports the Geometry module,
while the third creates an instance of the class Geometry.Box. The fourth line is how
events are set in Mango. In particular, the render event is set for the box we have 
created. If it is not clear to you what it might mean to "set" the "render event" for 
the box, for now let us say that setting the render event for the box causes it to be
displayed on the screen. Were this line omitted, the box would not be rendered, and
only an empty window would appear on the screen (the enterprising reader may wish to 
try this).

So, we created a box and told it to render by setting its render event. Simple enough. 
You may notice that we did not create a window, or enter any sort of loop, but 
nonetheless a window has appeared and, although the script completed its execution,
the simulation is still running. This is how Mango works: the script is run once at the
beginning of the simulation, and then a run-loop is entered. In this loop, events that
have been set are executed for the different objects that have been created. Thus our 
box appears on the screen, and will do so until we quit the simulation.

A Tree
-----------

Ok, so the box is cool, but you find yourself wanting more. So let's try another 
simple script that will widen our horizons, if only by a bit. Save the following 
script as hello_tree.py, and run it like you did before:

.. code-block:: python

   import Geometry

   trunk = Geometry.Cylinder()
   trunk.setColor(1.0, 0.5, 0.3)
   trunk.setRadius(0.1)
   trunk.set(RENDER)
   
   leaves = Geometry.Sphere()
   leaves.setColor(0, 1.0, 0)
   leaves.position = (0, 1.0, 0)
   leaves.set(RENDER)

This time we see something like:

  .. image:: /images/hello_tree1.png
     :width: 360
     :height: 240

We see two new classes from the Geometry module, Cylinder and 
Sphere, and we set their attributes to make their combination resemble a tree. If 
you are paying close attention, you may also notice a few other things:

  1. Some attributes we have set using methods, like 'setColor' and 'setRadius', while
     others we have set by accessing the attributes directly ('position'). Most
     attributes are set using setter methods. position and a few others are exceptions.
  2. setColor takes three arguments. These are the red, green and blue components of
     a color and should range from 0 to 1. Not all objects have a color, but all of
     those in the geometry module do.
  3. We never positioned the cylinder. By default, objects are positioned at the 
     origin, that is to say they have position (0, 0, 0).
  4. When we positioned the sphere, we moved it up by changing the y-coordinate of
     its position. In Mango, the y-axis points up.

Peruse the API at your leisure if you are curious as to which attributes may be set for 
which objects.



A Rotating Box
---------------

The previous two scripts showed you how to create a static scene using classes from
the geometry module. Now, static simulations will take you only so far, so let us 
revisit the box and give it some life. In order to do this, we are going to derive
a class that inherits from Geometry.Box and override its 'step' event. The step
event is an event that gets executed approximately 60 times per second. If we rotate
the box just a little bit in every step event, the net effect will be for the box
to rotate continuosly. Something like this should do the trick:

.. code-block:: python

   import Geometry

   class RotatingBox(Geometry.Box):
     def step(self):
       self.rotate(1, 0, 0)

   b = RotatingBox()
   b.set(RENDER | STEP)

A screenshot of this simulation would look very much like our first, but in real time
the box should be rotating. Cool, right? 

The last line is worth noting. We are using the familiar set method, but we are passing
a new value: RENDER | STEP. The operator '|' is a bitwise-or, and it combines the 
constant RENDER and the constant STEP into a value that represents both. This has the
effect of setting both events for the object, and is the equivalent of setting both
individually. 

If you are curious about the rotate method, check out the tutorial on frames.
