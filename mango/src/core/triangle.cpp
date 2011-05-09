#include "core/triangle.h"

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
