/*
 Copyright (c) 2011, 2012 Amos Joshua
 
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
#include <mango/geometry/geometry.h>
#include <cstdlib>

namespace Mango{
  namespace Geometry{

    static void fghCircleTable(double **sint,double **cost,const int n);

    /*
      ColorfulObject
    */
						
    /* Constructors, Destructors */									
		
    /**
     * Creates a ColorfulObject with a given height, width and length.						
     */
    ColorfulObject::ColorfulObject():Object(){	
      color_r = 0.0f;
      color_g = 0.0f;
      color_b = 1.0f;		    	    		    
    }
		
    ColorfulObject::~ColorfulObject(){
      //skip
    }
								
		
    /**
     * Sets the color of the ColorfulObject in RGB format. Each component is a GLfloat between 0 and 1.
     * @see color
     * @see setRedComponent
     * @see setGreenComponent
     * @see setBlueComponent		
     */
    void ColorfulObject::setColor(GLfloat c_r, GLfloat c_g, GLfloat c_b){		
      color_r = c_r;
      color_g = c_g;
      color_b = c_b;		    
    }		
		
    /**
     * Sets the red component of the ColorfulObject's color, as a GLfloat between 0 and 1.
     * @see color			
     * @see setColor
     * @see setGreenComponent
     * @see setBlueComponent
     */
    void ColorfulObject::setRedComponent(GLfloat c_r){
      color_r = c_r;
    }				
		
    /**
     * Sets the green component of the ColorfulObject's color, as a GLfloat between 0 and 1.
     * @see color		
     * @see setColor
     * @see setRedComponent		
     * @see setBlueComponent
     */
    void ColorfulObject::setGreenComponent(GLfloat c_g){
      color_g = c_g;
    }		
		
    /**
     * Sets the blue component of the ColorfulObject's color, as a GLfloat between 0 and 1.
     * @see color
     * @see setColor
     * @see setRedComponent
     * @see setGreenComponent		
     */
    void ColorfulObject::setBlueComponent(GLfloat c_b){
      color_b = c_b;
    }									
		
    /*
     * Retrieve the object's color by assigning the color components to three variables passed by reference.
     * Each component is a float between 0 and 1.
     * @see setColor
     * @see redComponent
     * @see greenComponent
     * @see blueComponent		
     */
    void ColorfulObject::color(GLfloat &c_r, GLfloat &c_g, GLfloat &c_b){
      c_r = color_r;
      c_g = color_g;
      c_b = color_b;
    }
		
    /**
     * Returns the red component of the ColorfulObject's color, as a GLfloat between 0 and 1.
     * @see color			
     * @see setColor		
     * @see greenComponent
     * @see blueComponent		
     */
    GLfloat ColorfulObject::redComponent(){
      return color_r;
    }
		
    /**
     * Returns the green component of the ColorfulObject's color, as a GLfloat between 0 and 1.
     * @see color			
     * @see setColor		
     * @see redComponent
     * @see blueComponent			
     */
    GLfloat ColorfulObject::greenComponent(){
      return color_g;
    }	
		
    /**
     * Returns the blue component of the ColorfulObject's color, as a GLfloat between 0 and 1.
     * @see color			
     * @see setColor		
     * @see redComponent
     * @see greenComponent					
     */
    GLfloat ColorfulObject::blueComponent(){
      return color_b;
    }			
		
    /* Dynamic Functions */					



		
		
    /*
      Box
    */
						
    /* Constructors, Destructors */									
		
    /**
     * Creates a Box with a given height, width and length.
     */
    Box::Box(GLfloat h, GLfloat w, GLfloat l):ColorfulObject(){
      if (h <= 0){
	throw Core::ValueError(objectType(), "Box", "height must be positive");
      }
      if (w <= 0){
	throw Core::ValueError(objectType(), "Box", "width must be positive");
      }
      if (l <= 0){
	throw Core::ValueError(objectType(), "Box", "length must be positive");
      }
		
      height = h;
      width = w;
      length = l;
    }
		
    Box::~Box(){
      //skip
    }
		
		
		
    /* Set, Get functions */
		
    /**
     * Sets the dimensions of the Box.
     * @see getDimensions
     */
    void Box::setDimensions(GLfloat h, GLfloat w, GLfloat l){
      if (h <= 0){
	throw Core::ValueError(objectType(), "setDimensions", "height must be positive");
      }
      if (w <= 0){
	throw Core::ValueError(objectType(), "setDimensions", "width must be positive");
      }
      if (l <= 0){
	throw Core::ValueError(objectType(), "setDimensions", "length must be positive");
      }
      height = h;
      width = w;
      length = l;
    }		
		
    /*
     * Retrieve the box's dimensions.
     * Retrieve the dimensions of the box by assigning them to three variables passed by reference.
     * Each component is a float between 0 and 1.
     * @see setDimensions
     */
    void Box::dimensions(GLfloat &h, GLfloat &w, GLfloat &l){
      h = height;
      w = width;
      l = length;
    }		
		
    /* Dynamic Functions */					
		
    void Box::render(){
      GLfloat h, w, l;
      h = height/2.0;
      w = width/2.0;
      l = length/2.0;			
		    
      transform();		
      
		
      glBegin(GL_QUADS);	            
      glColor3f(color_r, color_g, color_b);		    	
	
      glNormal3f(0, 1, 0);
      glVertex3f( h, w, -l);	// Top Right Of The Quad (Top)
      glVertex3f(-h, w, -l);	// Top Left Of The Quad (Top)
      glVertex3f(-h, w, l);	// Bottom Left Of The Quad (Top)
      glVertex3f( h, w, l);	// Bottom Right Of The Quad (Top)
	
      glNormal3f(0, -1, 0);
      glVertex3f( h, -w, l);	// Top Right Of The Quad (Bottom)
      glVertex3f(-h, -w, l);	// Top Left Of The Quad (Bottom)
      glVertex3f(-h, -w, -l);	// Bottom Left Of The Quad (Bottom)
      glVertex3f( h, -w, -l);	// Bottom Right Of The Quad (Bottom)
	
      glNormal3f(0, 0, 1);
      glVertex3f( h, w, l);	// Top Right Of The Quad (Front)
      glVertex3f(-h, w, l);	// Top Left Of The Quad (Front)
      glVertex3f(-h, -w, l);	// Bottom Left Of The Quad (Front)
      glVertex3f( h, -w, l);	// Bottom Right Of The Quad (Front)
	
      glNormal3f(0, 0, -1);
      glVertex3f( h, -w, -l);	// Top Right Of The Quad (Back)
      glVertex3f(-h, -w, -l);	// Top Left Of The Quad (Back)
      glVertex3f(-h, w, -l);	// Bottom Left Of The Quad (Back)
      glVertex3f( h, w, -l);	// Bottom Right Of The Quad (Back)
	
      glNormal3f(-1, 0, 0);
      glVertex3f(-h, w, l);	// Top Right Of The Quad (Left)
      glVertex3f(-h, w, -l);	// Top Left Of The Quad (Left)
      glVertex3f(-h, -w, -l);	// Bottom Left Of The Quad (Left)
      glVertex3f(-h, -w, l);	// Bottom Right Of The Quad (Left)
	
      glNormal3f(1, 0, 0);
      glVertex3f( h, w, -l);	// Top Right Of The Quad (Right)
      glVertex3f( h, w, l);	// Top Left Of The Quad (Right)
      glVertex3f( h, -w, l);	// Bottom Left Of The Quad (Right)
      glVertex3f( h, -w, -l);	// Bottom Right Of The Quad (Right)		
      glEnd();
    }
		
		
		
		
		
				
				
    /*
      Sphere
    */
		
		
		
    /* Construcors, Destructors */
		
    /**
     * Creates a red Sphere with a given radius and number of sides
     */
    Sphere::Sphere(GLfloat radius, int num_sides):ColorfulObject(){
      if (radius <= 0){
	throw Core::ValueError(objectType(), "Sphere", "radius must be positive");
      }
      if (num_sides <= 0){
	throw Core::ValueError(objectType(), "Sphere", "number of sides must be positive");
      }
		
      r = radius;
      setNumberOfSides(num_sides);		    
      setColor(0.0, 1.0, 0.0);
    }
		
    Sphere::~Sphere(){
      // pass
    }
		
		
		
    /* Set, Get functions */
		
    /**
     * Sets the radius of the Sphere.
     * @see radius
     */
    void Sphere::setRadius(GLfloat radius){
      if (radius <= 0){
	throw Core::ValueError(objectType(), "setRadius", "radius must be positive");
      }
      r = radius;
    }
		
    /**
     * Sets the number of sides used when rendering the sphere (affects its smoothness).
     * @see numberOfSides
     */
    void Sphere::setNumberOfSides(int num_sides){
      if (num_sides <= 0){
	throw Core::ValueError(objectType(), "setNumberOfSides", "number of sides must be positive");
      }
      sides = num_sides;
      dtheta = 2*3.1415926535897932384626433832795/sides;
      dphi = 3.1415926535897932384626433832795/sides;
    }
		
    /**
     * Returns the radius of the sphere.
     * @see setRadius
     */
    GLfloat Sphere::radius(){
      return r;
    }
		
    /**
     * Returns the number of sides used when rendering the sphere.
     * @see setNumberOfSides
     */
    int Sphere::numberOfSides(){
      return sides;
    }
		
    /* Dynamic Functions */
				
    void Sphere::render(){			
      transform();
      
      glColor3f(color_r, color_g, color_b);
      
      /*
	NOTE: This implementation is copied from the freeGLUT project v2.6.0,
            specifically from the function glutSolidSphere present in  
	    freeglut_geometry.c. In that project's source the original author 
	    of the function is credited as Andreas Umbach, later updated by 
	    Nigel Stewart.	    
     */
    
      int i,j;
      int slices, stacks;
      slices = sides;
      stacks = sides;

      /* Adjust z and radius as stacks are drawn. */

      double z0,z1;
      double r0,r1;

      /* Pre-computed circle */

      double *sint1,*cost1;
      double *sint2,*cost2;

      fghCircleTable(&sint1,&cost1,-slices);
      fghCircleTable(&sint2,&cost2,stacks*2);

      /* The top stack is covered with a triangle fan */

      z0 = 1.0;
      z1 = cost2[(stacks>0)?1:0];
      r0 = 0.0;
      r1 = sint2[(stacks>0)?1:0];

      glBegin(GL_TRIANGLE_FAN);

      glNormal3d(0,0,1);
      glVertex3d(0,0, r);

      for (j=slices; j>=0; j--)
        {
	  glNormal3d(cost1[j]*r1,        sint1[j]*r1,        z1       );
	  glVertex3d(cost1[j]*r1*r, sint1[j]*r1*r, z1*r);
        }

      glEnd();

      /* Cover each stack with a quad strip, except the top and bottom stacks */

      for( i=1; i<stacks-1; i++ )
	{
	  z0 = z1; z1 = cost2[i+1];
	  r0 = r1; r1 = sint2[i+1];

	  glBegin(GL_QUAD_STRIP);

	  for(j=0; j<=slices; j++)
            {
	      glNormal3d(cost1[j]*r1,        sint1[j]*r1,        z1       );
	      glVertex3d(cost1[j]*r1*r, sint1[j]*r1*r, z1*r);
	      glNormal3d(cost1[j]*r0,        sint1[j]*r0,        z0       );
	      glVertex3d(cost1[j]*r0*r, sint1[j]*r0*r, z0*r);
            }

	  glEnd();
	}

      /* The bottom stack is covered with a triangle fan */

      z0 = z1;
      r0 = r1;

      glBegin(GL_TRIANGLE_FAN);

      glNormal3d(0,0,-1);
      glVertex3d(0,0,-r);

      for (j=0; j<=slices; j++)
        {
	  glNormal3d(cost1[j]*r0,        sint1[j]*r0,        z0       );
	  glVertex3d(cost1[j]*r0*r, sint1[j]*r0*r, z0*r);
        }

      glEnd();

      /* Release sin and cos tables */

      free(sint1);
      free(cost1);
      free(sint2);
      free(cost2);   
    }						
		
		
		
		
		
		
		
       
		
		
		
		
		
    /*
      Cylinder
    */
		
		
		
    /* Construcors, Destructors */
		
    /**
     * Creates a red cylinder with a given radius, height and number of sides
     */
    Cylinder::Cylinder(GLfloat radius, GLfloat height, int num_sides):ColorfulObject(){
      if (radius <= 0){
	throw Core::ValueError(objectType(), "Cylinder", "radius must be positive");
      }
      if (height <= 0){
	throw Core::ValueError(objectType(), "Cylinder", "height must be positive");	
      }
      if (num_sides <= 0){
	throw Core::ValueError(objectType(), "Cylinder", "number of slices must be positive");
      }
		
      r = radius;
      setHeight(height);
      setNumberOfSides(num_sides);		    		    
      setColor(1.0, 0.0, 0.0);
    }
		
    Cylinder::~Cylinder(){
      // pass
    }
		
		
		
    /* Set, Get functions */
		
    /**
     * Sets the radius of the cylinder.
     * @see radius
     */
    void Cylinder::setRadius(GLfloat radius){
      if (radius <= 0){
	throw Core::ValueError(objectType(), "setRadius", "radius must be positive");
      }
      r = radius;
    }
		
		
    /**
     * Sets the height of the cylinder.
     * @see height
     */
    void Cylinder::setHeight(GLfloat height){
      if (height <= 0){
	throw Core::ValueError(objectType(), "setHeight", "height must be positive");
      }
      h_over_2 = height / 2.0;
    }
		
    /**
     * Sets the number of sides used when rendering the cylinder (affects its smoothness).
     * @see numberOfSides
     */
    void Cylinder::setNumberOfSides(int num_sides){
      if (num_sides <= 0){
	throw Core::ValueError(objectType(), "setNumberOfSides", "number of sides must be positive");
      }
      sides = num_sides;
      dtheta = 2*3.1415926535897932384626433832795/sides;    		
    }
		
    /**
     * Returns the radius of the cylinder.
     * @see setRadius
     */
    GLfloat Cylinder::radius(){
      return r;
    }
		
    /**
     * Returns the height of the cylinder.
     * @see setHeight
     */
    GLfloat Cylinder::height(){
      return 2*h_over_2;
    }
		
    /**
     * Returns the number of sides used when rendering the Cylinder.
     * @see setNumberOfSides
     */
    int Cylinder::numberOfSides(){
      return sides;
    }
		
    /* Dynamic Functions */		
    void Cylinder::render(){
      GLfloat x1, z1, x2, z2;
      int i;
			
      transform();
				    		    
		    
      // Draw the upper cap
      glBegin(GL_TRIANGLE_FAN);
      glColor3f(color_r, color_g, color_b);
      glNormal3f(0, 1, 0);
		
      for (i = sides-1; i >= 0; i -= 1){
	x1 = r*cos(i*dtheta);
	z1 = r*sin(i*dtheta);
	glVertex3f(x1, h_over_2, z1);
      }
      glEnd();
		
      // Draw the lower cap
      glBegin(GL_TRIANGLE_FAN);
      glNormal3f(0, -1, 0);
		
      for (i = 0; i < sides; i += 1){
	x1 = r*cos(i*dtheta);
	z1 = r*sin(i*dtheta);
	glVertex3f(x1, -h_over_2, z1);
      }
      glEnd();
		
		
      // Draw the tube
      glBegin(GL_QUADS);
      for (i = 0; i < sides; i += 1){
	x1 = r*cos(i*dtheta);
	z1 = r*sin(i*dtheta);
	x2 = r*cos((i+1)*dtheta);
	z2 = r*sin((i+1)*dtheta);
		
		
	glNormal3f(x1, 0, z1);
	glVertex3f(x1, -h_over_2, z1);
	glVertex3f(x1, h_over_2, z1);
		
	glNormal3f(x2, 0, z2);
	glVertex3f(x2, h_over_2, z2);
	glVertex3f(x2, -h_over_2, z2);
      }
      glEnd();
    }				
		
		
		
		
		
		
		
		
		
		
		
		

    /*
      Shell
    */
		
		
		
    /* Construcors, Destructors */
		
    /**
     * Creates a cyan shell with a given radius and number of sides
     */
    Shell::Shell(GLfloat radius, GLfloat thcknss, GLfloat frctn, int sides):ColorfulObject(){
      if (radius <= 0){
	throw Core::ValueError(objectType(), "Shell", "radius must be positive");
      }
      if (thcknss <= 0){
	throw Core::ValueError(objectType(), "Shell", "thickness must be positive");
      }
      if (frctn <= 0){
	throw Core::ValueError(objectType(), "Shell", "fraction must be positive");
      }
      if (sides <= 0){
	throw Core::ValueError(objectType(), "Shell", "number of sides must be positive");
      }
		
      r = radius;		   
      t = thcknss; 
      f = frctn;		    
      irr = r / (r + t);
      num_sides = sides;    		
      dtheta = 2*3.1415926535897932384626433832795/num_sides;
      dphi = f*3.1415926535897932384626433832795/num_sides;		    		    		    
      setColor(0.0, 1.0, 1.0);
    }
		
    Shell::~Shell(){
      // pass
    }
		
		
		
    /* Set, Get functions */
		
    /**
     * Sets the radius of the shell.
     * @see radius
     */
    void Shell::setRadius(GLfloat radius){
      if (radius <= 0){
	throw Core::ValueError(objectType(), "setRadius", "radius must be positive");
      }
      r = radius;
      irr = r / (r + t);
    }
		
    /**
     * Sets the thickness of the shell.
     * @see thickness
     */
    void Shell::setThickness(GLfloat thcknss){
      if (thcknss <= 0){
	throw Core::ValueError(objectType(), "setThickness", "thickness must be positive");
      }
      t = thcknss;
      irr = r / (r + t);
    }
		
    /**
     * Sets the fraction of the shell that is rendered. 0 means just the north pole, 0.5 is the top hemisphere, and 1.0 is the whole sphere.
     * @see fraction
     */
    void Shell::setFraction(GLfloat frctn){
      if (frctn <= 0){
	throw Core::ValueError(objectType(), "setFraction", "fraction must be positive");
      }
      f = frctn;
      dphi = f*3.1415926535897932384626433832795/num_sides;
    }
		
		
    /**
     * Sets the number of sides used when rendering the shell (affects its smoothness).
     * @see numberOfSides
     */
    void Shell::setNumberOfSides(int sides){
      if (num_sides <= 0){
	throw Core::ValueError(objectType(), "setNumberOfSides", "number of sides must be positive");
      }
      num_sides = sides;
      dtheta = 2*3.1415926535897932384626433832795/num_sides;
      dphi = f*3.1415926535897932384626433832795/num_sides;
    }
		
    /**
     * Returns the radius of the shell.
     * @see setRadius
     */
    GLfloat Shell::radius(){
      return r;
    }
		
    /**
     * Returns the thickness of the shell.
     * @see setThickness
     */
    GLfloat Shell::thickness(){
      return t;
    }
		
    /**
     * Returns the fraction of the shell that is rendered.
     * @see setFraction
     */
    GLfloat Shell::fraction(){
      return f;
    }
		
    /**
     * Returns the number of sides used when rendering the shell.
     * @see setNumberOfSides
     */
    int Shell::numberOfSides(){
      return num_sides;
    }
		
    /* Dynamic Functions */
		
		
    void Shell::render(){			
      transform();				    		
		    		   
      glScaled(r + t, r + t, r + t);
      glBegin(GL_QUADS);
      glColor3f(color_r, color_g, color_b);
				
      Core::Vector last_points[num_sides + 1];
      GLfloat x1, x2, y1, y2, z1, z2, R;
      for (int i = 0; i < num_sides + 1; i += 1){
	last_points[i][0] = 0;
	last_points[i][1] = 1;
	last_points[i][2] = 0;
      }
		
      for (int i = 1; i <= num_sides; i += 1){
	for (int j = 0; j < num_sides; j += 1){
	  R = sin(i*dphi);
		
	  x1 = R*cos(j*dtheta);
	  y1 = cos(i*dphi);
	  z1 = R*sin(j*dtheta);
		
	  x2 = R*cos((j+1)*dtheta);
	  y2 = y1;
	  z2 = R*sin((j+1)*dtheta);
		
	  // Draw the outer surface
		
	  glNormal3f(last_points[j][0], last_points[j][1], last_points[j][2]);
	  glVertex3f(last_points[j][0], last_points[j][1], last_points[j][2]);
		
	  glNormal3f(last_points[j+1][0], last_points[j+1][1], last_points[j+1][2]);
	  glVertex3f(last_points[j+1][0], last_points[j+1][1], last_points[j+1][2]);
		
	  glNormal3f(x2, y2, z2);
	  glVertex3f(x2, y2, z2);
		
	  glNormal3f(x1, y1, z1);
	  glVertex3f(x1, y1, z1);
		
		
		
		
	  // Draw the inner surface
		
	  glNormal3f(-x1, -y1, -z1);
	  glVertex3f(irr * x1, irr * y1, irr * z1);
		
	  glNormal3f(-x2, -y2, -z2);
	  glVertex3f(irr * x2, irr * y2, irr * z2);
		
	  glNormal3f(-last_points[j+1][0], -last_points[j+1][1], -last_points[j+1][2]);
	  glVertex3f(irr * last_points[j+1][0], irr * last_points[j+1][1], irr * last_points[j+1][2]);
		
	  glNormal3f(-last_points[j][0], -last_points[j][1], -last_points[j][2]);
	  glVertex3f(irr * last_points[j][0], irr * last_points[j][1], irr * last_points[j][2]);
		
		
		
	  // Draw the edge, if fraction < 1
	  if (f < 1 && i == num_sides){
	    glNormal3f(0, -1, 0);
		
	    glVertex3f(irr * x2, irr * y2, irr * z2);
		
	    glVertex3f(irr * x1, irr * y1, irr * z1);
		
	    glVertex3f(x1, y1, z1);
		
	    glVertex3f(x2, y2, z2);
		
		
		
		
		
		
	  }
		
		
	  last_points[j][0] = x1;
	  last_points[j][1] = y1;
	  last_points[j][2] = z1;
	}
	last_points[num_sides][0] = last_points[0][0];
	last_points[num_sides][1] = last_points[0][1];
	last_points[num_sides][2] = last_points[0][2];
      }
      glEnd();
    }						
		
		
		
		
		
		
		
		



		
    /*
      Arrow
    */				
		
    /* Construcors, Destructors */
    /**
     * Creates a yellow Arrow with a given length and thickness.
     */
    Arrow::Arrow(GLfloat length, GLfloat thickness):ColorfulObject(){
      if (length <= 0){
	throw Core::ValueError(objectType(), "Arrow", "length must be positive");
      }
      if (thickness <= 0){
	throw Core::ValueError(objectType(), "Arrow", "thickness must be positive");
      }
		
      l = length;
      w_x = thickness;
      w_y = thickness;			
      pyramid_base_ratio = 1.7;
      pyramid_height_fraction = 0.1;
      setColor(1.0, 1.0, 0);
    }
		
    Arrow::~Arrow(){
      // pass
    }
		
		
		
    /* Set, Get functions */
		
    /**
     * Sets the length of the arrow (including the head).
     * @see length
     * @see setThickness
     */
    void Arrow::setLength(GLfloat length){
      if (length <= 0){
	throw Core::ValueError(objectType(), "setLength", "length must be positive");
      }
      l = length;
    }
		
    /**
     * Sets the thickness of the arrow (width of each side).
     * @see thickness
     * @see setLength
     */
    void Arrow::setThickness(GLfloat thickness){
      if (thickness <= 0){
	throw Core::ValueError(objectType(), "setThickness", "thickness must be positive");
      }
      w_x = thickness;
      w_y = thickness;
    }

    /**
     * Sets the length and orientation of the arrow so that its tip is
     * located at the given position
     */
    void Arrow::setTipPosition(Vector &v){
      pointTo(v);
      setLength(v.norm());
    }

		
    /**
     * Returns the length of the arrow.
     * @see setLength
     * @see thickness
     */
    GLfloat Arrow::length(){
      return l;
    }
		
    /**
     * Returns the thickness of the arrow.
     * @see setThickness
     * @see length
     */
    GLfloat Arrow::thickness(){
      return w_x;
    }			      

		
    /* Dynamic Functions */
		
    void Arrow::render(){			
      GLfloat hh, hw, hl, bh, bw, bl;
      hh = w_x/2;
      hw = (1-(w_x/l))*l;
      hl = w_y/2;
		
      bh = pyramid_base_ratio*hh;
      bw = pyramid_height_fraction * hl;
      bl = pyramid_base_ratio*hl;		    		    
		    		
      transform();
		
      glBegin(GL_QUADS);
      glColor3f(color_r, color_g, color_b);
		
		
      glNormal3f(0, 1, 1);
      glVertex3f(-bh, hw, bl);
      glVertex3f(bh, hw, bl);
      glVertex3f(0, l, 0);
      glVertex3f(0, l, 0);
		
      glNormal3f(1, 1, 0);
      glVertex3f(bh, hw, bl);
      glVertex3f(bh, hw, -bl);
      glVertex3f(0, l, 0);
      glVertex3f(0, l, 0);
		
      glNormal3f(0, 1, -1);
      glVertex3f(bh, hw, -bl);
      glVertex3f(-bh, hw, -bl);
      glVertex3f(0, l, 0);
      glVertex3f(0, l, 0);
		
      glNormal3f(-1, 1, 0);
      glVertex3f(-bh, hw, -bl);
      glVertex3f(-bh, hw, bl);
      glVertex3f(0, l, 0);
      glVertex3f(0, l, 0);
		
      glNormal3f(0, -1, 0);
      glVertex3f( bh, hw, bl);	// Bottom Right Of The Quad (Bottom of Pyarmid)
      glVertex3f(-bh, hw, bl);	// Bottom Left Of The Quad (Bottom of Pyarmid)
      glVertex3f(-bh, hw, -bl);	// Top Left Of The Quad (Bottom of Pyarmid)
      glVertex3f( bh, hw, -bl);	// Top Right Of The Quad (Bottom of Pyarmid)
		
      glNormal3f(0, -1, 0);
      glVertex3f( hh, 0, hl);	// Top Right Of The Quad (Bottom)
      glVertex3f(-hh, 0, hl);	// Top Left Of The Quad (Bottom)
      glVertex3f(-hh, 0, -hl);	// Bottom Left Of The Quad (Bottom)
      glVertex3f( hh, 0, -hl);	// Bottom Right Of The Quad (Bottom)
		
      glNormal3f(0, 0, 1);
      glVertex3f( hh, hw, hl);	// Top Right Of The Quad (Front)
      glVertex3f(-hh, hw, hl);	// Top Left Of The Quad (Front)
      glVertex3f(-hh, 0, hl);	// Bottom Left Of The Quad (Front)
      glVertex3f( hh, 0, hl);	// Bottom Right Of The Quad (Front)
		
      glNormal3f(0, 0, -1);
      glVertex3f( hh, 0, -hl);	// Top Right Of The Quad (Back)
      glVertex3f(-hh, 0, -hl);	// Top Left Of The Quad (Back)
      glVertex3f(-hh, hw, -hl);	// Bottom Left Of The Quad (Back)
      glVertex3f( hh, hw, -hl);	// Bottom Right Of The Quad (Back)
		
      glNormal3f(-1, 0, 0);
      glVertex3f(-hh, hw, hl);	// Top Right Of The Quad (Left)
      glVertex3f(-hh, hw, -hl);	// Top Left Of The Quad (Left)
      glVertex3f(-hh, 0, -hl);	// Bottom Left Of The Quad (Left)
      glVertex3f(-hh, 0, hl);	// Bottom Right Of The Quad (Left)
		
      glNormal3f(1, 0, 0);
      glVertex3f( hh, hw, -hl);	// Top Right Of The Quad (Right)
      glVertex3f( hh, hw, hl);	// Top Left Of The Quad (Right)
      glVertex3f( hh, 0, hl);	// Bottom Left Of The Quad (Right)
      glVertex3f( hh, 0, -hl);	// Bottom Right Of The Quad (Right)
      glEnd();
    }				
		
		
		
		
		
		
		
		
		
		
		
		
		
    /*
      CoordinateSystem
    */		
		
    /* Construcors, Destructors */
    /**
     * Creates a 3D coordinate system with given orientation, axis length and thickness.				
     */
    CoordinateSystem::CoordinateSystem():Core::Object(){
      axes[0] = new Arrow();
      axes[1] = new Arrow();
      axes[2] = new Arrow();
			
      axes[0]->setColor(0.0, 1.0, 0.0);
      axes[1]->setColor(0.0, 0.0, 1.0);
      axes[2]->setColor(1.0, 1.0, 0.0);
	
      axes[1]->setOrientation(0, 90, 0);
      axes[2]->setOrientation(90, 90, 0);			
    }
		
    CoordinateSystem::~CoordinateSystem(){
      // pass
    }
		
		
    /* Set, Get functions */
		
    /**
     * Sets the length of axes in the coordinate system.
     * @see axisLength
     */
    void CoordinateSystem::setAxisLength(GLfloat axis_l){
      if (axis_l <= 0){
	throw Core::ValueError(objectType(), "setAxisLength", "axis length must be positive");
      }
		    
      axes[0]->setLength(axis_l);
      axes[1]->setLength(axis_l);
      axes[2]->setLength(axis_l);
    }
		
		
    /**
     * Sets the thickness of axes in the coordinate system.
     * @see axisThickness
     */
    void CoordinateSystem::setAxisThickness(GLfloat axis_t){
      if (axis_t <= 0){
	throw Core::ValueError(objectType(), "setAxisThickness", "axis thickness must be positive");
      }
		    
      axes[0]->setThickness(axis_t);
      axes[1]->setThickness(axis_t);
      axes[2]->setThickness(axis_t);
    }
		
		
    /**
     * Sets the orientation of the coordinate system. The coordiante system will render as a right 
     * handed coordinate system if right_handed is true, and as a left handed coordinate system otherwise.
     * @see isRightHanded
     */
    void CoordinateSystem::setRightHanded(bool right_handed){
      if (right_handed){
	axes[1]->setOrientation(0, 90, 0);
      }
      else{
	axes[1]->setOrientation(0, -90, 0);
      }
    }
		
		
    /**
     * Returns the length of the coordinate system's axes.
     * @see setAxisLength
     * @see axisThickness
     */
    GLfloat CoordinateSystem::axisLength(){
      return axes[0]->length();
    }
		
    /**
     * Returns the thickness of the coordinate system's axes.
     * @see setAxisThickness
     * @see axisLength
     */
    GLfloat CoordinateSystem::axisThickness(){
      return axes[0]->thickness();
    }
		
    /**
     * Returns true if the coordiante system is right handed, false if it is left handed.
     * @see shouldBeRightHanded		
     */
    bool CoordinateSystem::rightHanded(){
      return (axes[1]->beta == 90);
    }				
		
    void CoordinateSystem::render(){
      transform();
      axes[0]->render();
      axes[1]->render();
      axes[2]->render();
    }
		
		
		
		
		
		
		
		
		
		
		
		
    /*
      VertexArray
    */		
		
    /* Construcors, Destructors */
		    
    /**
     * Creates an empty vertex array with the default style GL_LINES.				
     */
    VertexArray::VertexArray():ColorfulObject(){
      render_style = GL_LINE_STRIP;
      also_render_opposite_orientation = false;
      setColor(1.0, 0.0, 1.0);
    }
		
    VertexArray::~VertexArray(){
      // pass
    }
		
		
    /**
     * Adds the point represented by the Vector v to the array, as the last vertex in the array. 
     * @see insertAt
     * @see vertexAt
     * @see removeAt
     * @see size
     */
    void VertexArray::add(Core::Vector &v){
      vertices.push_back(v);	
    }
		
    /**
     * Adds the point represented by the tuple (x, y, z) to the array, as the last vertex in the array. 
     * @see insertAt
     * @see vertexAt
     * @see removeAt
     * @see size
     */
    void VertexArray::add(GLfloat x, GLfloat y, GLfloat z){
      vertices.push_back(Core::Vector(x, y, z));	
    }
		
    /**
     * Inserts the point represented by the vector v into the array, in front of the vertex at the given index. An exception of
     * type Core::IndexError is raised of index is invalid. 
     * @see add
     * @see vertexAt
     * @see removeAt
     * @see size		
     */
    void VertexArray::insertAt(int index, Core::Vector &v){
      int size = vertices.size();
      if ((index < 0) || (index > size)){
	throw Core::IndexError(objectType(), "vertexAt", "invalid index");
      }
      else if (index == size){
	vertices.push_back(v);
	return;
      }
      vertices.insert(vertices.begin() + index, v);
    }
		
		
    /**
     * Inserts the point represented by the tuple (x, y, z) into the array, in front of the vertex at the given index. An exception of
     * type Core::IndexError is raised of index is invalid.
     * @see add
     * @see vertexAt
     * @see removeAt
     * @see size						
     */
    void VertexArray::insertAt(int index, GLfloat x, GLfloat y, GLfloat z){
      int size = vertices.size();
      if ((index < 0) || (index > size)){
	throw Core::IndexError(objectType(), "vertexAt", "invalid index");
      }
      else if (index == size){
	vertices.push_back(Core::Vector(x, y, z));
	return;
      }
      vertices.insert(vertices.begin() + index, Core::Vector(x, y, z));
    }

    /**
     * Removes the vertex at the given index. An exception of type Core::IndexError is raised of index is invalid. 
     * @see add
     * @see vertexAt
     * @see insertAt
     * @see size						
     */
    void VertexArray::removeAt(int index){
      if ((index < 0) || (index >= vertices.size())){
	throw Core::IndexError(objectType(), "vertexAt", "invalid index");
      }
      vertices.erase(vertices.begin() + index);
    }  
		
    /**
     * Returns the vertex at the given index. An exception of type Core::IndexError is raised if index is invalid.
     * @see size
     */
    Core::Vector& VertexArray::vertexAt(int index){
      if ((index < 0) || (index >= vertices.size())){
	throw Core::IndexError(objectType(), "vertexAt", "invalid index");
      }
				
      return vertices[index];
    }
		
    /**
     * Sets the style used to render the vertices in the array. See VertexArray::VertexArray() for a list of supported rendering styles.
     * @see style
     * @see VertexArray
     */
    void VertexArray::setStyle(int new_style){
      render_style = new_style;
    }
		
    /**
     * Sets a flag that, when true, causes the object to render its vertices in reverse order in addition to the normal order. Normally 
     * (when this flag is off) each vertex is rendered once in order of their position in the array. Some rendering styles, such as 
     * GL_TRIANGLES or GL_QUADS will render a two dimensional shape that is only visible from one side - which side depends on the
     * orientation as determined by the order of the vertices. In such cases, rendering the vertices in reverse order will make the 
     * shape visible from both sides.
     * @see alsoRendersReverseOrientation
     * @see setStyle
     * @see style
     */
    void VertexArray::setRenderReverseOrientation(bool render_in_reverse){
      also_render_opposite_orientation = render_in_reverse;
    }
		
    /**
     * Returns the style used to render the vertices in the array. See VertexArray::VertexArray() for a list of supported rendering styles.
     * @see setStyle
     * @see VertexArray
     */
    int VertexArray::style(){
      return render_style;
    }
		
    /**
     * Returns the value of the flag that determines if the object also renders its vertices in reverse order. See 
     * VertexArray::setRenderReverseOrientation() for a more detailed explanation.
     * @see setRenderReverseOrientation
     * @see setStyle
     * @see style
     */
    bool VertexArray::renderReverseOrientation(){
      return also_render_opposite_orientation;
    }
		
		
    /**
     * Returns the size of the array, that is the number of vertices in the array.
     * @see add
     * @see style
     */
    int VertexArray::size(){
      return vertices.size();
    }
		
    void VertexArray::render(){			
      transform();
		    
      std::vector<Core::Vector>::iterator current_vertex;
      std::vector<Core::Vector>::reverse_iterator rvertex;
		    
      glBegin(render_style);
      glColor3f(color_r, color_g, color_b);
		    	
      for (current_vertex = vertices.begin(); current_vertex != vertices.end(); current_vertex++){
	glVertex3f((*current_vertex)[0], (*current_vertex)[1], (*current_vertex)[2]);	
      }		    		    		
      if (also_render_opposite_orientation){		    			    	
	for (rvertex = vertices.rbegin(); rvertex != vertices.rend(); rvertex++){
	  glVertex3f((*rvertex)[0], (*rvertex)[1], (*rvertex)[2]);	
	}		    				    			    		
      }    		    		
      glEnd();		    		    
    }		
		
		
		
		
		
		
		
		
		
		
		
    /*
      Circle
    */
						
    /* Construcors, Destructors */
		
    /**
     * Creates a red Circle with a given radius and number of sides
     */
    Circle::Circle(GLfloat radius, int num_sides):ColorfulObject(){
      if (radius <= 0){
	throw Core::ValueError(objectType(), "Circle", "radius must be positive");
      }
      if (num_sides <= 0){
	throw Core::ValueError(objectType(), "Circle", "number of slices must be positive");
      }
		
      r = radius;
      render_style = WIRE_LOOP;
      setNumberOfSides(num_sides);		    
      setColor(1.0, 0.5, 0.0);
      setRenderReverseOrientation(true);
    }
		
    Circle::~Circle(){
      // pass
    }
		
		
		
    /* Set, Get functions */
		
    /**
     * Sets the radius of the circle.
     * @see radius
     */
    void Circle::setRadius(GLfloat radius){
      if (radius <= 0){
	throw Core::ValueError(objectType(), "setRadius", "radius must be positive");
      }
      r = radius;
    }
		
    /**
     * Sets the number of sides used when rendering the circle (affects its smoothness).
     * @see numberOfSides
     */
    void Circle::setNumberOfSides(int sides){
      if (sides <= 0){
	throw Core::ValueError(objectType(), "setNumberOfSides", "number of sides must be positive");
      }
      number_of_sides = sides;
      dtheta = 2*3.1415926535897932384626433832795/number_of_sides;    		
    }
		
    /**
     * Sets the style used to render the circles. Possible values are:
     - WIRE
     - FILL
     * (these are aliases for GL_LINE_LOOP and GL_POLYGON, respectively. Technically any of the styles availabe for VertexArray 
     * are acceptable, but in practice these two are the most appropriate. Try experimenting with the other style constants 
     * for funky results). 
     * @see style		
     */
    void Circle::setStyle(int new_style){
      render_style = new_style;
    }
		
    /**
     * Sets a flag that, when true, causes the circle to render in reverse orientation. Normally 
     * (when this flag is off) the circle is rendered in only one of its orientations. This is irrelevant for the WIRE rendering style,
     * however the FILL rendering style will render a circle that is only visible from one side. In such cases, setting this flag to true
     * will cause the circle to be rendered in both orientation, making it visible from both sides.		
     * @see alsoRendersReverseOrientation
     * @see setStyle
     * @see style
     */
    void Circle::setRenderReverseOrientation(bool render_in_reverse){
      also_render_opposite_orientation = render_in_reverse;
    }
		
    /**
     * Returns the radius of the circle.
     * @see setRadius
     */
    GLfloat Circle::radius(){
      return r;
    }
		
    /**
     * Returns the number of sides used when rendering the circle.
     * @see setNumberOfSides
     */
    int Circle::numberOfSides(){
      return number_of_sides;
    }
		
    /**
     * Returns the style used to render the circle. See Circle::setStyle() for a list of supported rendering styles.
     * @see setStyle		
     */
    int Circle::style(){
      return render_style;
    }
		
    /**
     * Returns the value of the flag that determines if the circle also renders in reverse orientation. See 
     * Circle::setRenderReverseOrientation() for a more detailed explanation.
     * @see setRenderReverseOrientation
     * @see setStyle
     * @see style
     */
    bool Circle::renderReverseOrientation(){
      return also_render_opposite_orientation;
    }
		
    /* Dynamic Functions */				
		
    void Circle::render(){			
      transform();
		
      glColor3f(color_r, color_g, color_b);
		
      glBegin(render_style);
      GLfloat theta = 0;
      for (int i = 0; i < number_of_sides; i += 1){
	glVertex3f(r*cos(theta), r*sin(theta), 0);	
	theta += dtheta;
      }
      glEnd();
		    
      if (also_render_opposite_orientation){
	glBegin(render_style);
	GLfloat theta = 2*3.1415926535897932384626433832795;
	for (int i = 0; i < number_of_sides; i += 1){
	  glVertex3f(r*cos(theta), r*sin(theta), 0);	
	  theta -= dtheta;
	}
	glEnd();
      }
    }
		
		
    void Circle::draw(){
      render();
    }
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
    /*
      NGon
    */
						
    /* Construcors, Destructors */
		
    /**
     * Creates a symmetric n-gon with a given radius and number of sides
     */
    NGon::NGon(GLfloat radius, int num_sides):Circle(radius, num_sides){		     
      setColor(0.5, 1.0, 0.0);
    }
		
    NGon::~NGon(){
      // pass	
    }
		
		
		
		
		
		
		
		
		
		
		
		
		
		
    /*
      Rectangle
    */
						
    /* Construcors, Destructors */
		
    /**
     * Creates a rectangle with a given width and length
     */
    Rectangle::Rectangle(GLfloat width, GLfloat length):ColorfulObject(){
      if (width <= 0){
	throw Core::ValueError(objectType(), "Rectangle", "width must be positive");
      }
      if (length <= 0){
	throw Core::ValueError(objectType(), "Rectangle", "length must be positive");
      }
		
      w = width;
      l = length;
      render_style = WIRE_LOOP;		    
      setColor(1.0, 1.0, 1.0);
    }
		
    Rectangle::~Rectangle(){
      // pass
    }
		
		
		
    /* Set, Get functions */
		
    /**
     * Sets the width of the rectangle.
     * @see width
     * @see setLength
     * @see setDimensions
     */
    void Rectangle::setWidth(GLfloat width){
      if (width <= 0){
	throw Core::ValueError(objectType(), "setWidth", "width must be positive");
      }
      w = width;
    }
		
		
    /**
     * Sets the length of the rectangle.
     * @see length
     * @see setWidth
     * @see setDimensions
     */
    void Rectangle::setLength(GLfloat length){
      if (length <= 0){
	throw Core::ValueError(objectType(), "setLength", "length must be positive");
      }
      l = length;
    }
		
    /**
     * Sets the width and length of the rectangle.
     * @see width
     * @see length
     * @see setWidth
     * @see setLength		
     */
    void Rectangle::setDimensions(GLfloat width, GLfloat length){
      setWidth(width);
      setLength(length);
    }
		
    /**
     * Sets the style used to render the circles. Possible values are:
     - WIRE
     - FILL
     * (these are aliases for GL_LINE_LOOP and GL_POLYGON, respectively. Technically any of the styles availabe for VertexArray 
     * are acceptable, but in practice these two are the most appropriate. Try experimenting with the other style constants 
     * for funky results). 
     * @see style		
     */
    void Rectangle::setStyle(int new_style){
      render_style = new_style;
    }
		
    /**
     * Sets a flag that, when true, causes the circle to render in reverse orientation. Normally 
     * (when this flag is off) the circle is rendered in only one of its orientations. This is irrelevant for the WIRE rendering style,
     * however the FILL rendering style will render a circle that is only visible from one side. In such cases, setting this flag to true
     * will cause the circle to be rendered in both orientation, making it visible from both sides.		
     * @see alsoRendersReverseOrientation
     * @see setStyle
     * @see style
     */
    void Rectangle::setRenderReverseOrientation(bool render_in_reverse){
      also_render_opposite_orientation = render_in_reverse;
    }
		
    /**
     * Returns the width of the rectangle.
     * @see setWidth
     */
    GLfloat Rectangle::width(){
      return w;
    }
		
    /**
     * Returns the length of the rectangle.
     * @see setLength
     */
    GLfloat Rectangle::length(){
      return l;
    }
		
    /**
     * Returns the style used to render the circle. See Rectangle::setStyle() for a list of supported rendering styles.
     * @see setStyle		
     */
    int Rectangle::style(){
      return render_style;
    }
		
    /**
     * Returns the value of the flag that determines if the circle also renders in reverse orientation. See 
     * Rectangle::setRenderReverseOrientation() for a more detailed explanation.
     * @see setRenderReverseOrientation
     * @see setStyle
     * @see style
     */
    bool Rectangle::renderReverseOrientation(){
      return also_render_opposite_orientation;
    }
		
    /* Dynamic Functions */
		
    void Rectangle::render(){			
      transform();
		
      glColor3f(color_r, color_g, color_b);
		
      GLfloat wo2 = w/2.0;
      GLfloat lo2 = l/2.0;
		    
      glBegin(render_style);
      glVertex3f(wo2, lo2, 0);
      glVertex3f(wo2, -lo2, 0);
      glVertex3f(-wo2, -lo2, 0);
      glVertex3f(-wo2, lo2, 0);		        
      glEnd();

      if (also_render_opposite_orientation){
	glBegin(render_style);
	glVertex3f(-wo2, lo2, 0);		        
	glVertex3f(-wo2, -lo2, 0);
	glVertex3f(wo2, -lo2, 0);			        
	glVertex3f(wo2, lo2, 0);
	glEnd();
      }
    }
		
		
    void Rectangle::draw(){
      render();
    }
		


    //// @cond
    /*
      NOTE: This function is copied from the freeGLUT project v2.6.0,
            specifically from the file freeglut_geometry.c. The original
	    contributor appears to be Nigel Stewart.

      * Compute lookup table of cos and sin values forming a cirle
      *
      * Notes:
      *    It is the responsibility of the caller to free these tables
      *    The size of the table is (n+1) to form a connected loop
      *    The last entry is exactly the same as the first
      *    The sign of n can be flipped to get the reverse loop
      */

    static void fghCircleTable(double **sint,double **cost,const int n)
    {
      int i;

      /* Table size, the sign of n flips the circle direction */

      const int size = abs(n);

      /* Determine the angle between samples */

      const double angle = 2*M_PI/(double)( ( n == 0 ) ? 1 : n );

      /* Allocate memory for n samples, plus duplicate of first entry at the end */

      *sint = (double *) calloc(sizeof(double), size+1);
      *cost = (double *) calloc(sizeof(double), size+1);

      /* Bail out if memory allocation fails, fgError never returns */

      if (!(*sint) || !(*cost))
	{
	  free(*sint);
	  free(*cost);
	  throw Core::Error("Sphere", "render", "failed to allocate memory for sin table");
	}

      /* Compute cos and sin around the circle */

      (*sint)[0] = 0.0;
      (*cost)[0] = 1.0;

      for (i=1; i<size; i++)
	{
	  (*sint)[i] = sin(angle*i);
	  (*cost)[i] = cos(angle*i);
	}

      /* Last sample is duplicate of the first */

      (*sint)[size] = (*sint)[0];
      (*cost)[size] = (*cost)[0];
    }

    //// @endcond

  } // Geometry
} // Mango
