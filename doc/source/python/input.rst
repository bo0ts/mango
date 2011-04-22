Input
=====

Python provides two classes that facilitate handing input (Core.Keyboard 
and Core.Mouse). There is only ever one instance of each of these classes 
and these instances are available globally via the variables Keyboard 
and Mouse. 

There are also two different ways to handle input: querying state and 
responding to input events.

Querying State
--------------
The state of the keyboard and/or mouse can be queried by accessing the
down methods of the Keyboard and Mouse objects. These methods
expect a code representing a key or button, and return true or false
based on the current state of the key (or button): true if the key is 
currently pressed (button is clicked) and false otherwise.

Lets test this with a simulation of a bouncing ball, where the "speed" of
the bouncing can be adjusted using the keyboard:

.. code-block:: python

  import Geometry, math
  
  class BouncingBall(Geometry.Sphere):
      t = 0
      delta = 0.1
      def step(self):
          self.handle_input()
          self.bounce()      
  
      def bounce(self):
          self.t += self.delta
          self.position = (0, 0.2 + abs(math.sin(self.t)), 0)
  
      def handle_input(self):
          if Keyboard.down(KEY_UP):
              self.delta += 0.01
          elif Keyboard.down(KEY_DOWN):
              self.delta -= 0.01
  
  platform = Geometry.Box()
  platform.setDimensions(1.0, 0.1, 1.0)
  ball = BouncingBall()
  ball.setRadius(0.2)
  
  ball.set(RENDER | STEP)
  platform.set(RENDER | STEP)
  
You can adjust the speed at which the ball bounces using the up and down 
arrow keys on the keyboard.

The method down expects a code that represents the key whose state is being
queried. For most printable characters in the ASCII range, the key code 
corresponds to the ASCII code of the character and so the built-in Python 
method ord can be used to retrieve the code. In order to query the state
of non-printable characters, use one of the constants KEY_* as in this 
example. 

The state of the mouse buttons can be queried similarly via Mouse.down using
one of the constants BUTTON_LEFT and BUTTON_RIGHT.

Sometimes, querying the instantaneous state of the mouse or keyboard is not
so useful. In such situations, input events usually do the trick.

Input Events
------------

The second way of interacting with the keyboard and mouse is through input
events: an object whose INPUT event is set will have the input callback
executed once for every input event that occurs. The totality of these 
events is comprised of (keyboard) key presses and releases and (mouse) 
button presses and releases. There is no event associated with the 
movement of the mouse.

When the input event callback is executed, it is passed an instance of
Core.InputEvent that represents the event that occurred. Instances of
InputEvent have three attributes: source, type and code.

Source is always equal to one of MOUSE or KEYBOARD. type is always one of
PRESS or RELEASE (CLICK is an alias of PRESS), while code is equal to the
code of the key or button associated with the event. 

Let's see this in action:

.. code-block:: python

  class InputPrinter(Core.Object):
      def input(self, event):
          print(event)
  
  
  ip = InputPrinter()
  ip.set(INPUT)
  
You should see an empty black window when you run this script. If you press
keys on the keyboard or click on the window with the mouse, you should see
lines printed out in the console window from which you launched the 
simulation. Each line represents, and describes, one input event. 

Let's add a pause feature to the bouncing ball simulation with adjustable 
speed: if the user presses and releases the space bar, the bouncing of
the ball will be paused. If the user presses and releases it again, it will
resume. Input events are better suited to this task because we can easily
target the release of the space bar, which is harder to do with state
querying. The code looks like this:

.. code-block:: python

  import Geometry, math
  
  class BouncingBall(Geometry.Sphere):
      t = 0
      delta = 0.1
      paused = False
  
      def step(self):
          self.handle_input()
          self.bounce()      
  
      def bounce(self):
          self.t += (self.delta if not self.paused else 0)
          self.position = (0, 0.2 + abs(math.sin(self.t)), 0)
  
      def handle_input(self):
          if Keyboard.down(KEY_UP):
              self.delta += 0.01
          elif Keyboard.down(KEY_DOWN):
              self.delta -= 0.01
  
      def input(self, event):
          if event == Core.InputEvent(KEYBOARD, RELEASE, KEY_SPACE):            
              self.paused = not self.paused
  
  platform = Geometry.Box()
  platform.setDimensions(1.0, 0.1, 1.0)
  ball = BouncingBall()
  ball.setRadius(0.2)
  
  ball.set(RENDER | STEP | INPUT)
  platform.set(RENDER | STEP)


Notice how we determine which event occurred by comparing it to an instance
of InputEvent that we create with the parameters we want. It is also 
possible to create wildcard events by passing ANY as one of the parameters. 
For instance, Core.InputEvent(KEYBOARD, PRESS, ANY) would match against any
(keyboard) key-press event, regardless of which key was pressed.
