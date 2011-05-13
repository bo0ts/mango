Frames
=======
all positioning and orienting of objects in Mango is done via a Frame 
object, an instance of the class Core.Frame, which represents a particular 
frame of reference. All frames are positioned and oriented relative to a 
global frame of reference that defines the coordinate system used by all 
other objects in the simulation. Ordinarily there is no visual indication 
of the global frame of reference, but it is easy to change that. Save and 
run the following script:

.. code-block:: python

   import Geometry

   global_cs = Geometry.CoordinateSystem()
   global_cs.set(RENDER)


The result should look like:

  .. image:: /images/global_coordinate_system.png
     :width: 480
     :height: 360
 

The CoordinateSystem class in the Geometry module can be used to visualize 
a coordinate system. By default its position and orientation coincide with
that of the global frame of reference: The y-axis (green) points up, the x-axis (yellow) to the right and the z-axis
(blue) into the screen.

Objects are Frames
-------------------

Frames as instances of the class Core.Frame define frames of reference, but 
these are not the only frames in a simulation. Every object derived from
Core.Object (i.e. any object you can set events on) is itself a frame - it has
all the methods and attributes that a frame has, and it is completely 
interchangeable with frames in every situation. We will take advantage of this
convenient fact and use classes from the Geometry module as frames, because 
they make visualization easier. Keep in mind as you
proceed, however, that everything also applies to instances of the class 
Core.Frame. For instance, the next section shows that frames have a position
attribute, and demonstrates this fact using the class Geometry.Box. We
can conclude, therefore, that instances of Core.Frame also have a 
position attribute and that behaves in the same way.


Position
---------

Every frame has a position attribute, which defines its position relative to 
its parent frame of reference. We will ignore the idea that frames can have
parent frames other than the global frame (the default parent of every frame) 
for the moment, and take up the issue later. That said, the position attribute
behaves as you would expect. For instance, the following script shows a box 
oscillating up and down along the y-axis:

.. code-block:: python

  import Geometry, math

  class OscillatingBox(Geometry.Box):
      t = 0
      def step(self):
          self.t += 0.1
          self.position = (1, math.sin(self.t), 1)
  
  global_cs = Geometry.CoordinateSystem()
  b = OscillatingBox()
  
  global_cs.set(RENDER)
  b.set(STEP | RENDER)

The position attribute of a frame of reference is a vector, an instance of
Core.Vector. Check out the section on vectors (REF) if you are curious about these
objects.

Orientation
------------

Every frame has three parameters called "orientation angles" that define 
its orientation relative to its parent frame. Each angle represents a 
rotation around a particular axis, through the angle equal to the parameter
in value (measured in degrees). The names of these angles and the rotations 
they represent are as follows:

 * alpha - rotation around the y-axis of the parent frame
 * beta - rotation around the z-axis of the frame obtained after applying the rotation represented by alpha
 * gamma - rotation around the y-axis of the frame obtained after applying the rotation represented by beta 

You may know these angles as the Euler angles that represent the orientation
of a rigid body in three dimensions. If this is your first encounter with 
these angles, don't worry if a perfect understanding eludes you at first.
You will gain a better understanding of them as you experiment with orienting 
objects in your simulations. 

The orientation angles are attributes, and can be set just like the position
attribute. For instance, the following script changes the value of alpha
for a box, causing it to rotate around the y-axis, that is in the horizontal
x-z plane:

.. code-block:: python

  import Geometry, math

  class OscillatingBox(Geometry.Box):
      t = 0
      def step(self):
          self.t += 0.02
          self.alpha = 180*math.sin(self.t)
  
  global_cs = Geometry.CoordinateSystem()
  b = OscillatingBox()
  b.position = (1, 0, 1)
  
  global_cs.set(RENDER)
  b.set(STEP | RENDER)



There is a demo script 'angles.py' that might help illuminate the roles of
these three orientation angles. After running it, use the buttons 'q'/'a' to 
modify alpha, 'w'/'s' to modify beta, and finally 'e'/'d' to modify gamma. A 
frame of reference with the resulting orientation is shown, along with arcs
extending through angles representing the rotations defined by alpha, beta
and gamma. A screenshot from this script shows the resulting orientation 
(the thick frame) after modifying alpha (represented by the green arc) and
beta (represented by the dark yellow arc):

  .. image:: /images/demo_angles.png
     :width: 480
     :height: 360


.. _frames-bouncing-ball-sample:

Relative Frames
----------------

Every frame has a parent frame, in relation to which its position and 
orientation are defined. The parent of a frame can be retrieved using
the parentFrame() method, and set using the setParentFrame() method. The
global frame (available globally as GlobalFrame) is the default parent of
every frame, while it itself has no parent (GlobalFrame.parentFrame() will
return None).

Suppose we wish to simulate a ball bouncing up and down on a platform which
is itself moving from left to right. Bouncing a ball up and down is easy:

.. code-block:: python
  
  import Geometry, math
  
  class BouncingBall(Geometry.Sphere):
      t = 0
      def step(self):
          self.t += 0.08
          self.position = (0, 0.2 + abs(math.sin(self.t)), 0)
  
  platform = Geometry.Box()
  platform.setDimensions(1.0, 0.1, 1.0)
  ball = BouncingBall()
  ball.setRadius(0.2)
  
  ball.set(RENDER | STEP)
  platform.set(RENDER)


Now, we *could* move the platform *and* the ball left and right, but we're 
smarter than that. You already know what we're going to do: move the 
platform left and right, and make it the parent frame of the ball:

.. code-block:: python

  import Geometry, math

  class BouncingBall(Geometry.Sphere):
      t = 0
      def step(self):
          self.t += 0.08
          self.position = (0, 0.2 + abs(math.sin(self.t)), 0)
  
  class MovingPlatform(Geometry.Box):
      t = 0
      def step(self):
          self.t += 0.01
          self.position = (math.sin(self.t), 0, 0)
  
  platform = MovingPlatform()
  platform.setDimensions(1.0, 0.1, 1.0)
  ball = BouncingBall()
  ball.setRadius(0.2)
  ball.setParentFrame(platform)
  
  ball.set(RENDER | STEP)
  platform.set(RENDER | STEP)

Now, one thing you want to be careful of: don't create closed loops of 
parent frames. That is, if you set object a's parent to be object b, and
object b's parent to be object a, your simulation will not be happy.