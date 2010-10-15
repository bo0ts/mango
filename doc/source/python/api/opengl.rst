OpenGL
======

The OpenGL module provides a subset of the OpenGL API. All of these functions
are imported into the global namespace, so for instance one can invoke
OpenGL.glVertex by calling it directly: 'glVertex', without prefixing it with
OpenGL. Consult the OpenGL documentation for more information about these
methods (http://www.opengl.org/sdk/docs/man/), or read a tutorial.

.. module:: OpenGL
   :synopsis: provided OpenGL methods


.. function:: glBegin(mode)

   Initiate a rendering sequence. mode should be one of:

     * GL_POINTS 
     * GL_LINES 
     * GL_LINE_LOOP
     * GL_LINE_STRIP
     * GL_TRIANGLES
     * GL_TRIANGLE_STRIP
     * GL_TRIANGLE_FAN
     * GL_QUADS
     * GL_QUAD_STRIP
     * GL_POLYGON          

   Every call to glVertex should take place between a call to glBegin and
   glEnd. Consult the OpenGL documentation for more information.


.. function:: glEnd()

   Terminate a rendering sequence. See glBegin().


.. function:: glVertex(v)

   Render a vertex at point v. Every call to glVertex should take place 
   between a call to glBegin and glEnd.


.. function:: glNormal(v)

   Set the normal for all future vertices that will be rendered, until
   another call to glNormal. This is relevant when using a rendering mode 
   that renders surfaces - the normals should be set so as to point in a 
   direction perpendicular to the surface. 


.. function:: glColor(r, g, c)

   Set the color for all future vertices that will be rendered. r, g, and b
   represent the red, green and blue components of the color and should take
   values between 0 and 1. Also affects calls to helper methods in the Draw
   module such as Draw.line. This method also accepts a tuple with three
   values.


.. function:: glTranslate(v)

   Translate the current frame of referencein which things will be rendered.


.. function:: glRotate(alpha, v=(0, 0, 1))

   Rotate the current frame of reference in which things will be rendered by
   the angle alpha around the vector v.

.. function:: glScale(kx, ky, kz)

   Scale the current frame of reference in which things will be rendered.