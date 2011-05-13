Camera and View
===============

When a simulation begins the scene appears as it would to a viewer staring
down the z-axis at a certain distance from the origin:

  .. image:: /images/global-frame-zoomed.png
     :width: 480
     :height: 360

By default, the user is free to change the viewing angle by interacting with
the simulation using the mouse (and possibly keyboard): they can rotate, pan
or zoom. It is also possible to perform these transformations 
programmatically. The class responsible for this functionality is 
Core.CoreCamera, and two instances are globally available: Camera, which 
controls the 3D scene, and View, which controls the 2D scene.

Changing the Camera's Position
------------------------------

Consider the following script which showcases four fancy
boxes:

.. code-block:: python

  import Geometry
  
  boxes = [Geometry.Box() for i in range(4)]
  positions = [(-1, 0, -1),
               (1, 0, -1),
               (1, 0, 1),
               (-1, 0, 1)]
  colors = [(1, 0, 0),
            (0, 1, 0),
            (0, 0, 1),
            (1, 1, 0)]
  
  for box, pos, color in zip(boxes, positions, colors):
      box.position = pos
      box.setColor(color)
      box.set(RENDER)
  

The initial view onto this scene is:

  .. image:: /images/four-fancy-boxes-default-view.png
     :width: 480
     :height: 360


We can modify this script so that the initial view onto the scene is 
that of a viewer located at position (3, 3, 3) by calling Camera.lookFrom:

.. code-block:: python

  import Geometry
  
  boxes = [Geometry.Box() for i in range(4)]
  positions = [(-1, 0, -1),
               (1, 0, -1),
               (1, 0, 1),
               (-1, 0, 1)]
  colors = [(1, 0, 0),
            (0, 1, 0),
            (0, 0, 1),
            (1, 1, 0)]
  
  for box, pos, color in zip(boxes, positions, colors):
      box.position = pos
      box.setColor(color)
      box.set(RENDER)


  Camera.lookFrom((3, 3, 3))

The added call to Camera.lookFrom positions the camera at (3, 3, 3) and
orients it so that it is looking at the current focus ((0, 0, 0)). Notice that we are
accessing the global CoreCamera instance Camera, which is responsible for
the 3D scene. The result is:

  .. image:: /images/four-fancy-boxes-45-view.png
     :width: 480
     :height: 360

In the previous sample we changed the camera's position, but the focus of
the camera was still at the origin (this fact should be clear if you run the
simulation and rotate the view). In the next sample, we change the focus
of the camera without changing the viewing angle:

.. code-block:: python

  import Geometry
  
  boxes = [Geometry.Box() for i in range(4)]
  positions = [(-1, 0, -1),
               (1, 0, -1),
               (1, 0, 1),
               (-1, 0, 1)]
  colors = [(1, 0, 0),
            (0, 1, 0),
            (0, 0, 1),
            (1, 1, 0)]
  
  for box, pos, color in zip(boxes, positions, colors):
      box.position = pos
      box.setColor(color)
      box.set(RENDER)
  
  Camera.lookAt((1, 0, 1))
  
Camera.lookAt changes the focus of the camera while maintaining the (relative)
viewing angle. In this case, we changed the focus to the center of the blue
box:

  .. image:: /images/four-fancy-boxes-blue-view.png
     :width: 480
     :height: 360

As with the previous sample, rotating the view around should make this fact 
clear. 

The Focus
---------

Positioning of the camera is accomplished via a frame of reference known 
as the focus of the camera. This frame of reference is set as the camera's
parent, with the camera positioned at some distance d on the z-axis 
(pointing towards the relative origin of the focus). 

  .. image:: /images/camera-focus-diagram.png
     :width: 480
     :height: 360

Zooming of the camera is accomplished by moving the camera up and down the
z-axis of the focus, while rotation around the focus is accomplished by
rotating the focus itself (rather the camera).

One consequence of this arrangement is that in order to rotate the view at
which the user is viewing the scene, you will want to rotate the focus 
rather than the camera. For instance, the following script rotates around
the boxes from the previous samples:

.. code-block:: python

  import Geometry
  
  class CameraRotator(Core.Object):
      def step(self):
          Camera.focus().rotate(1, 0, 0)
  
  boxes = [Geometry.Box() for i in range(4)]
  positions = [(-1, 0, -1),
               (1, 0, -1),
               (1, 0, 1),
               (-1, 0, 1)]
  colors = [(1, 0, 0),
            (0, 1, 0),
            (0, 0, 1),
            (1, 1, 0)]
  
  for box, pos, color in zip(boxes, positions, colors):
      box.position = pos
      box.setColor(color)
      box.set(RENDER)
    
  cr = CameraRotator()
  cr.set(STEP)
  
There is nothing stopping you from rotating the camera, but it will have
a different visual effect (namely, that of rotating the camera about its
own axis). 

Another consequence is that in order to cause the camera to focus on a 
particular point you can change the position of the focus to that
location (rather than change the position of the camera. Again, you can do
that too, but it will accomplish something else). Normally you do not have
to do this as the methods Camera.lookAt and Camera.lookFrom are at your
disposal, but it is good to know what is going on underneath. 

Finally, if you set the parent frame of the camera's focus to another object
the camera will "follow" that object around the scene (or simply focus on it
if it is stationary). There is a convenience method, Camera.follow, that
accepts a frame (or object) as an argument and does exactly this. 


Modes
-----

The class Core.CoreCamera supports several modes, which can be set using
the method setMode. For instance, one can prevent panning by setting the
mode LOCK_PAN, or prevent rotation around the y-axis by setting the mode
LOCK_ALPHA. Here's an example that uses both these modes:

.. code-block:: python

  import Geometry
  
  boxes = [Geometry.Box() for i in range(4)]
  positions = [(-1, 0, -1),
               (1, 0, -1),
               (1, 0, 1),
               (-1, 0, 1)]
  colors = [(1, 0, 0),
            (0, 1, 0),
            (0, 0, 1),
            (1, 1, 0)]
  
  for box, pos, color in zip(boxes, positions, colors):
      box.position = pos
      box.setColor(color)
      box.set(RENDER)
  
  
  Camera.setMode(LOCK_PAN | LOCK_ALPHA)


When you run the simulation, note the restricted camera movement: you cannot
pan at all, and can only rotate the viewing angle vertically. 

The View in 2D
--------------

Recall that the CoreCamera instance Camera controls only the 3D scene, and
that there is another instance of this class named View that controls the
2D one. View behaves much in the same way that Camera does, and all
techniques mentioned so far for the camera apply to it as well. One notable
difference is in the default mode: for View it is RMB_CYLINDRICAL_ROTATE.
When in this mode, an instance of CoreCamera will respond to dragging of the
right mouse button by rotating the view around the axis perpendicular to the
screen. This behavior suits 2D scenes, but it may be undesirable in some
instances. If you wish to prevent it, simply change the mode to suit your 
needs. For instance, you may wish to simply lock the camera completely by
setting the mode LOCK_ALL, preventing rotation or zooming of the scene.