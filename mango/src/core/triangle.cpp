#include "core/triangle.h"

namespace Mango{
  namespace Core{
    /*
      Triangle
    */
    
    /* Construcors, Destructors */
    
    
    /**
     * Default constructor.
     * The default constructor, creates a Triangle object with default radius of 0.3 and green color.
     */
    Triangle::Triangle():Object(){
      tsize = 0.3;
    }
    
    Triangle::~Triangle(){
      //skip
    }
    
    
    
    /* Set, Get functions */
    
    /**
     * Set the size.
     * Sets the size of the Triangle, the distance from its center to any of its vertices.
     * @param float size       - the new size
     * @see getSize
     */
    void Triangle::setSize(GLfloat new_size){
      if (new_size <= 0){
	throw ValueError(objectType(), "setSize", "size must be positive");
      }
      
      tsize = new_size;
    }		
    
    /**
     * Get the size.
     * Returns the size of the Triangle, the distance from its center to any of its vertices.
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
