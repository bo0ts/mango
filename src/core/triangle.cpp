/*
 Copyright (c) 2011 Amos Joshua
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/
#include <mango/core/triangle.h>

namespace Mango{
  namespace Core{
    

    
    
    /**
     * Create a Triangle object with default size of 0.3. 
     */
    Triangle::Triangle():Object(){
      tsize = 0.3;
    }
    
    Triangle::~Triangle(){
      //skip
    }    
    
    /**
     * Set the size of the Triangle, the distance from its center to
     * any of its vertices.
     *
     * @param size 
     *   the new size, a ValueError will be raised if it is not positive.
     *
     * @see size
     */
    void Triangle::setSize(GLfloat new_size){
      if (new_size <= 0){
	throw ValueError(objectType(), "setSize", "size must be positive");
      }
      
      tsize = new_size;
    }		
    
    /**
     * Return the size of the Triangle, the distance from its center
     * to any of its vertices.
     *
     * @see setSize
     */
    GLfloat Triangle::size(){
      return tsize;
    }						
    
    /* Dynamic Functions */
    
    void Triangle::render(){
      double rx, ry;
      
      transform();
      
      ry = tsize/2;
      rx = 0.866025*tsize;
      glBegin(GL_TRIANGLES);
            
      glNormal3f(0.0, 1.0, 0.0);
      glColor3f(1.0, 0.0, 0.0);
      glVertex3f(0, 0, tsize);
      
      glColor3f(0.0, 1.0, 0.0);
      glVertex3f(rx, 0, -ry);
      
      glColor3f(0.0, 0.0, 1.0);
      glVertex3f(-rx, 0, -ry);
      
      glNormal3f(0.0, -1.0, 0.0);
      glColor3f(0.0, 0.0, 1.0);
      glVertex3f(-rx, 0, -ry);
      
      glColor3f(0.0, 1.0, 0.0);
      glVertex3f(rx, 0, -ry);
      
      glColor3f(1.0, 0.0, 0.0);
      glVertex3f(0, 0, tsize);
      
      glEnd();
    }
    
  } // Core
} // Mango
