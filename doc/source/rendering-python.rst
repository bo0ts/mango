Rendering
=========

A Mango simulation is composed of two scenes superimposed onto one another,
a 3-dimensional scene and a 2-dimensional one. Mango comes with a limited 
number of objects with a visual presence (mostly contained in the Geometry 
module). When these objects do not meet your needs, you are free to 
construct your own visual objects. This is done by implementing custom 
render events (for objects in the 3D scene) or custom draw events (for 
objects in the 2D scene). (the designation of these events as "render" and 
"draw" are somewhat arbitrary, but less awkward than "render_3d" and 
"render_2d" or other similar possibilities).

A More Literal Hello World
--------------------------
One of the first things you might find that you want to do in a render
event is put text on the screen. Since Mango does not provide any 
text-rendering objects, this is the best way to show text to the user:

.. code-block:: python
  
  class SimpleText(Core.Object):
      def render(self):
          Draw.text((-2.8, 0.3), "Hello World")
  
  st = SimpleText()
  st.set(RENDER)
  

The first parameter to Draw.text is the position of the text, in this case
chosen to center the text on the screen:

  .. image:: python/simpletext.png
     :width: 480
     :height: 360

Local and Global Frames of Reference
------------------------------------

Anything rendered in a render event is rendered relative to the global
frame of reference. At the start of the simulation the origin (in a 3D 
scene) is located in the middle of the screen with the y-axis pointing up, 
the x-axis to the right, and the z-axis pointing into the screen. Position 
of objects is determined using a "virtual" scale that does not usually 
correspond to pixels on the screen, that is to say, if the x-coordinate of an object's
position is 1, that does not mean 1 pixel to the right of the origin, but
rather one unit which may correspond to many pixels. 

This leads us to a subtlety of render events: unless you purposefully 
enforce the position and orientation of the rendering object, you will be 
rendering relative to the global frame. You can transform to the object's 
frame of reference using the transform method. For instance, the following 
modification causes the text to rotate:

.. code-block:: python
  
  class RotatingText(Core.Object):
      def step(self):
          self.rotate(1, 0, 0)
  
      def render(self):
          self.transform()
          Draw.text((-2.8, 0.3, 0), "Hello World")
  
  rt = RotatingText()
  rt.set(RENDER | STEP)
  
But if you comment out the call to transform on the 6th line, you will
find that the text is stationary - the instance rt of RotatingText is
still being rotated, but the rendering is being done relative to the
global frame because no call to transform has occurred.


Another Example: Lines
----------------------

There are several basic drawing methods available via the Draw module. Here
is another example that uses Draw.line to draw 30 random lines:

.. code-block:: python

  from random import random
  
  def random_pt():
      return (-2 + 4*random(), -2 + 4*random(), -2 + 4*random())
  
  def random_color():
      return (random(), random(), random())
  
  
  class ColorfulSticks(Core.Object):
      lines = [(
              random_pt(),
              random_pt(),
              random_color()
              ) for i in range(30)]
      
      def render(self):
          for pt1, pt2, color in self.lines:
              glColor(color)
              Draw.line(pt1, pt2)
  
  
  cs = ColorfulSticks()
  cs.set(RENDER)
     
The result is:

  .. image:: python/colorful_lines.png
     :width: 480
     :height: 360


Rendering Complex Objects
-------------------------

The methods available in the Draw module are useful, but you may find them
insufficient if you wish to render complex objects. In order to allow
greater flexibility when rendering, a subset of the OpenGL API is 
available. These commands begin with 'gl' - like glColor used in the 
previous section - and their use generally follows this pattern:

.. code-block:: python

  glBegin(rendering-mode)
  #..
  # Render vertices with glVertex()
  # or change color with glColor()
  #..
  glEnd()

rendering-mode can be one of GL_POINTS, GL_LINES, GL_LINE_LOOP,
GL_TRIANGLES, GL_QUADS or GL_POLYGON, among others (see the documentation
for glBegin for a full list). The rendering mode determines what is drawn
based on the calls to glVertex between one glBegin and the next glEnd. For
instance, in order to render single pixels at the corners of a square, one
would use the GL_POINTS rendering mode:

.. code-block:: python

  class FourCorners(Core.Object):
      def render(self):
          glBegin(GL_POINTS)
          glVertex(0, 0, 0)
          glVertex(0, 1, 0)
          glVertex(1, 1, 0)
          glVertex(1, 0, 0)
          glEnd()
  
  fc = FourCorners()
  fc.set(RENDER)

This results in:

  .. image:: python/four-corners.png
     :width: 480
     :height: 360


If instead one wished to render the outline of the square:

.. code-block:: python

  class FourEdges(Core.Object):
      def render(self):
          glBegin(GL_LINE_LOOP)
          glVertex(0, 0, 0)
          glVertex(0, 1, 0)
          glVertex(1, 1, 0)
          glVertex(1, 0, 0)
          glEnd()
  
  fc = FourEdges()
  fc.set(RENDER)

Which looks like:

  .. image:: python/four-edges.png
     :width: 480
     :height: 360

Note that GL_LINES would not have been appropriate for rendering the outline
of a square [without more extensive modifications], for that mode causes
each consecutive disjoint pair of vertices to be rendered as a line, meaning
that only two sides of the square would have been rendered:

  .. image:: python/two-edges.png
     :width: 480
     :height: 360

One interesting feature afforded by OpenGL is color interpolation between vertices
rendered in different colors. Consider the following script that renders a
square:

.. code-block:: python
  
  class ColorfulSquare(Core.Object):
      def render(self):
          glBegin(GL_QUADS)
          # Red vertex
          glColor(1, 0, 0)
          glVertex(1, -1, 0)
          # Green vertex
          glColor(0, 1, 0)
          glVertex(1, 1, 0)
          # Blue vertex
          glColor(0, 0, 1)
          glVertex(-1, 1, 0)
          # Yello vertex
          glColor(1, 1, 0)
          glVertex(-1, -1, 0)
          glEnd()
  
  
  cs = ColorfulSquare()
  cs.set(RENDER)
  

By coloring the corner vertices red, green, blue and yellow and using the
GL_QUADS rendering mode (interprets every 4 consecutive disjoint vertices
as the corners of a quadrilateral) one obtains the following square:

  .. image:: python/colorful-square.png
     :width: 480
     :height: 360

Note a subtlety of modes that render surfaces (like GL_QUADS): only one 
side of the surface is rendered, depending on the order at which you 
specify the vertices. That is, rendering the vertices in this order: 
(1, -1, 0), (1, 1, 0), (-1, 1, 0), (-1, -1, 0) will render one side of a
square, while rendering the vertices in this order: (-1, -1, 0), (-1, 1, 0),
(1, 1, 0), (1, -1, 0) will render the opposite side of the square. If you
wish a surface to be visible from both sides, render it twice specifying the
vertices once in each order. 

Surfaces
--------

Here is an example script that renders a surface, in particular the surface
of the function f(r) = exp(-r**2):

.. code-block:: python

  import Geometry, math
  
  class Surface(Core.Object):
      xrange = (-1.0, 1.0)
      yrange = (-1.0, 1.0)
      delta = 0.1
  
      def render(self):
          self.transform()
          glBegin(GL_QUADS)
          for point in self.points_in_region():
              self.render_f_quad(point[0], point[1])            
          glEnd()
  
      def render_f_quad(self, x, y):
          for pt in self.points_in_quad(x, y): 
              self.render_f_vertex(pt[0], pt[1])
  
      def render_f_vertex(self, x, y):
          green = (x**2 + y**2)**0.4
          glColor(0.0, green, 1.0)
          glVertex(self.s(x, y))
  
      def points_in_quad(self, x, y):
          return [(x, y),
                  (x, y + self.delta),
                  (x + self.delta, y + self.delta),
                  (x + self.delta, y)]
          
      def points_in_region(self):
          for i in range(round((self.xrange[1] - self.xrange[0])/self.delta)):
              for j in range(round((self.yrange[1] - self.yrange[0])/self.delta)):
                  x = self.xrange[0] + i*self.delta
                  y = self.yrange[0] + j*self.delta
                  yield (x, y)                        
  
      def s(self, x, y):
          return (x, self.f(x, y), y)
  
      def f(self, x, y):
          return math.exp(-10*(x**2 + y**2))
          
  
  s = Surface()
  s.set(RENDER)
  

The result:

  .. image:: python/exp-surface.png
     :width: 480
     :height: 360


Drawing
-------

Where render events allow you to render objects in the 3D scene, draw events
may be used to render objects in the 2D scene. While there is nothing 
stopping you from using the render event for 2D graphics by restricting 
yourself to the x-y plane, the virtual scale can be inconvenient. For this
and other reasons the draw event is often a better choice for working with
2D graphics.

The draw event is essentially another render event with a few changes that
make it more appropriate for 2D. For one, the coordinate system is 
different: the origin is at the bottom left of the screen instead of at the
center. The y-axis still points up and the x-axis still points to the right,
but one unit of scale does correspond to one pixel (at least initially). 
Another difference is of perspective: things rendered in a draw event will
not get smaller as they get farther away and larger as they get closer -
instead, they will stay the same size. This is less than ideal for 3D
graphics, but it has no bearing on 2D graphics and in fact at times it can
be useful. 

Code snippets for the draw event are much the same as those for the render
event. Here's one example that draws a chess board:

.. code-block:: python
     
  class SimpleChessBoard(Core.Object):
      def draw(self):        
          self.transform()
          Draw.rectangle((0, 0), (100, 100), True) # First square
          Draw.rectangle((100, 100), (200, 200), True) # Second square
          Draw.rectangle((0, 0), (200, 200), False) # Border
  
  
  scb = SimpleChessBoard()
  scb.position = (220, 140)
  scb.set(DRAW)
  
Ok, so its a simplified chess board:

  .. image:: python/simplified-chess.png
     :width: 480
     :height: 360


