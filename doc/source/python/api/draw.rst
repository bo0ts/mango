Draw
====

The Draw module provides helper drawing methods. Methods that accept 
arguments representing points expect vectors or tuples. 

.. module:: Draw
   :synopsis: drawing methods (remember: tuples instead of vectors)

.. function:: line(v1, v2)

   Draw a line extending from the point v1 to the v2


.. function:: rectangle(v1, v2, filled=False)

   Draw a rectangle with corners at points v1, v2.


.. function:: circle(v, r, filled=False, sides=48)

   Draw a circle of radius r at point v. 
   

.. function:: text(v, str, scale=1.0, character_spacing=0.1)

   Draw the string str ad point v. Only a printable subset of the ASCII 
   character set is available.


.. function:: textDimensions(str, scale=1.0, character_spacing=0.1)

   Returns a tuple (width, min_height, max_height) representing the 
   dimensions of the text str. If str is drawn using Draw.text with the same
   parameters, it will extend width units to the right, at most min_height
   units down and at most max_height units up.
