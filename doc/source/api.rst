Mango API (Python)
===================

:mod:`Core` -- Core Mango objects and methods


:mod:`Draw` -- Drawing methods

.. module:: Draw
   :synopsis: drawing methods


:mod:`OpenGL` -- Provided OpenGL methods

.. module:: OpenGL
   :synopsis: provided OpenGL methods


:mod:`Geometry` -- Geometric Objects

.. module:: Geometry
   :synopsis: geometric objects






.. module:: Core
   :synopsis: core objects and methods


.. class:: Object

   The base class for all event-capable objects. The events supported by
   this class are step, render, draw, input, and they don't do anything. 
   Children should override these methods to give the object behavior.

   .. method:: step

   .. method:: render

   .. method:: draw

   .. method:: input(event)
   


.. class:: CoreEngine
   
   .. method:: windowDimensions
   .. method:: setFPS(desired_fps)