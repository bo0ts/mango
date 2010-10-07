#include "geometry.h"

namespace Mango{
  namespace Geometry{
		
    /*
      ColorfulObject
    */
						
    /* Constructors, Destructors */									
		
    /**
     * Create a ColorfulObject of given dimensions.
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
     * Set the color.
     * Sets the color of the ColorfulObject in RGBA format. Each component is a GLfloat between 0 and 1.
     * @param GLfloat r        - the red component
     * @param GLfloat g        - the green component
     * @param GLfloat b        - the green component
     * @see getColor
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
     * Set the red component.
     * Sets the red component of the ColorfulObject's color, as a GLfloat between 0 and 1.
     * @param GLfloat r        - the new red component
     * @see getColor			
     * @see setColor
     * @see setGreenComponent
     * @see setBlueComponent
     * @see setAlphaComponent	
     */
    void ColorfulObject::setRedComponent(GLfloat c_r){
      color_r = c_r;
    }				
		
    /**
     * Set the green component.
     * Sets the green component of the ColorfulObject's color, as a GLfloat between 0 and 1.
     * @param GLfloat g        - the new green component
     * @see getColor		
     * @see setColor
     * @see setRedComponent		
     * @see setBlueComponent
     * @see setAlphaComponent
     */
    void ColorfulObject::setGreenComponent(GLfloat c_g){
      color_g = c_g;
    }		
		
    /**
     * Set the blue component.
     * Sets the blue component of the ColorfulObject's color, as a GLfloat between 0 and 1.
     * @param GLfloat b        - the new blue component
     * @see getColor
     * @see setColor
     * @see setRedComponent
     * @see setGreenComponent		
     * @see setAlphaComponent
     */
    void ColorfulObject::setBlueComponent(GLfloat c_b){
      color_b = c_b;
    }									
		
    /*
     * Retrieve the object's color.
     * Retrieve the object's color by assigning the color components to three variables passed by reference.
     * Each component is a float between 0 and 1.
     * @param &r     - the variable to which the red component will be assigned.
     * @param &g     - the variable to which the green component will be assigned.
     * @param &b     - the variable to which the blue component will be assigned.
     * @param &alpha - the variable to which the alpha component will be assigned.
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
     * Get the red component.
     * Returns the red component of the ColorfulObject's color, as a GLfloat between 0 and 1.
     * @return GLfloat r        - the red component
     * @see getColor			
     * @see setColor		
     * @see greenComponent
     * @see blueComponent		
     */
    GLfloat ColorfulObject::redComponent(){
      return color_r;
    }
		
    /**
     * Get the green component.
     * Returns the green component of the ColorfulObject's color, as a GLfloat between 0 and 1.
     * @return GLfloat g        - the green component
     * @see getColor			
     * @see setColor		
     * @see redComponent
     * @see blueComponent			
     */
    GLfloat ColorfulObject::greenComponent(){
      return color_g;
    }	
		
    /**
     * Get the blue component.
     * Returns the blue component of the ColorfulObject's color, as a GLfloat between 0 and 1.
     * @return GLfloat b        - the blue component
     * @see getColor			
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
     * Create a Box of given dimensions.
     * Creates a Box with a given height, width and length.
     * @param float height       - the height of the box, defaults to 1.0.
     * @param float width        - the width of the box, defaults to 1.0.
     * @param float length       - the length of the box, defaults to 1.0.
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
     * Set the dimensions.
     * Sets the dimensions of the Box.
     * @param float h        - the height of the box.
     * @param float w        - the width of the box.
     * @param float l        - the length of the box.
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
     * @param &h     - the variable to which the height will be assigned.
     * @param &w     - the variable to which the width will be assigned.
     * @param &l     - the variable to which the length will be assigned.
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
     * Create a Sphere of a given radius and number of sides.
     * Creates a red Sphere with a given radius and number of sides
     * @param float radius       - the radius of the sphere.
     * @param int sides         - the number of sides to use when rendering the sphere (affects the smoothness of the sphere).
     */
    Sphere::Sphere(GLfloat radius, int num_sides):ColorfulObject(){
      if (radius <= 0){
	throw Core::ValueError(objectType(), "Sphere", "radius must be positive");
      }
      if (num_sides <= 0){
	throw Core::ValueError(objectType(), "Sphere", "number of slices must be positive");
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
     * Set the radius.
     * Sets the radius of the Sphere.
     * @param float radius       - the new radius
     * @see radius
     */
    void Sphere::setRadius(GLfloat radius){
      if (radius <= 0){
	throw Core::ValueError(objectType(), "setRadius", "radius must be positive");
      }
      r = radius;
    }
		
    /**
     * Set the number of sides.
     * Sets the number of sides used when rendering the sphere (affects its smoothness).
     * @param int sides     - the number of sides to use.
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
     * Get the radius.
     * Returns the radius of the sphere.
     * @see setRadius
     */
    GLfloat Sphere::radius(){
      return r;
    }
		
    /**
     * Get the number of sides.
     * Returns the number of sides used when rendering the sphere.
     * @see setNumberOfSides
     */
    int Sphere::numberOfSides(){
      return sides;
    }
		
    /* Dynamic Functions */
				
    void Sphere::render(){			
      transform();				    
		
      glBegin(GL_QUADS);
      glColor3f(color_r, color_g, color_b);		    	
		
		
      Core::Vector last_points[sides + 1];
      GLfloat x1, x2, y1, y2, z1, z2, R;
      for (int i = 0; i < sides + 1; i += 1){
	last_points[i][0] = 0;
	last_points[i][1] = r;
	last_points[i][2] = 0;
      }
		
      for (int i = 1; i <= sides; i += 1){
	for (int j = 0; j < sides; j += 1){
	  R = r*sin(i*dphi);
		
	  x1 = R*cos(j*dtheta);
	  y1 = r*cos(i*dphi);
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
		
				
		
		
	  last_points[j][0] = x1;
	  last_points[j][1] = y1;
	  last_points[j][2] = z1;
	}
	last_points[sides][0] = last_points[0][0];
	last_points[sides][1] = last_points[0][1];
	last_points[sides][2] = last_points[0][2];
      }
      glEnd();
    }						
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
    /*
      Cylinder
    */
		
		
		
    /* Construcors, Destructors */
		
    /**
     * Create a cylinder of given dimensions.
     * Creates a red cylinder with a given radius, height and number of sides
     * @param GLfloat radius       - the radius of the cylinder.
     * @param GLfloat height		  - the height of the cylinder.
     * @param int sides         - the number of sides to use when rendering the Cylinder (affects the smoothness of the Cylinder).
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
     * Set the radius.
     * Sets the radius of the cylinder.
     * @param GLfloat radius       - the new radius
     * @see radius
     */
    void Cylinder::setRadius(GLfloat radius){
      if (radius <= 0){
	throw Core::ValueError(objectType(), "setRadius", "radius must be positive");
      }
      r = radius;
    }
		
		
    /**
     * Set the height.
     * Sets the height of the cylinder.
     * @param GLfloat height       - the new height
     * @see height
     */
    void Cylinder::setHeight(GLfloat height){
      if (height <= 0){
	throw Core::ValueError(objectType(), "setHeight", "height must be positive");
      }
      h_over_2 = height / 2.0;
    }
		
    /**
     * Set the number of sides.
     * Sets the number of sides used when rendering the cylinder (affects its smoothness).
     * @param int sides     - the number of sides to use.
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
     * Get the radius.
     * Returns the radius of the cylinder.
     * @see setRadius
     */
    GLfloat Cylinder::radius(){
      return r;
    }
		
    /**
     * Get the height.
     * Returns the height of the cylinder.
     * @see setHeight
     */
    GLfloat Cylinder::height(){
      return 2*h_over_2;
    }
		
    /**
     * Get the number of sides.
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
     * Create a shell of a given radius and number of sides.
     * Creates a cyan shell with a given radius and number of sides
     * @param float radius       - the radius of the shell.
     * @param int sides         - the number of sides to use when rendering the shell (affects the smoothness of the shell).
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
     * Set the radius.
     * Sets the radius of the shell.
     * @param float radius       - the new radius
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
     * Set the thickness.
     * Sets the thickness of the shell.
     * @param float thcknss       - the new thickness
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
     * Set the fraction to draw.
     * Sets the fraction of the shell that is rendered. 0 means just the north pole, 0.5 is the top hemisphere, and 1.0 is the whole sphere.
     * @param float frctn       - the new fraction
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
     * Set the number of sides.
     * Sets the number of sides used when rendering the shell (affects its smoothness).
     * @param int sides     - the number of sides to use.
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
     * Get the radius.
     * Returns the radius of the shell.
     * @see setRadius
     */
    GLfloat Shell::radius(){
      return r;
    }
		
    /**
     * Get the thickness.
     * Returns the thickness of the shell.
     * @see setThickness
     */
    GLfloat Shell::thickness(){
      return t;
    }
		
    /**
     * Get the fraction.
     * Returns the fraction of the shell that is rendered.
     * @see setFraction
     */
    GLfloat Shell::fraction(){
      return f;
    }
		
    /**
     * Get the number of sides.
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
     * Create an arrow of a given length and thickness.
     * Creates a yellow Arrow with a given length and thickness.
     * @param float length       - the length of the vector.
     * @param float thickness    - the thickness of the vector
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
     * Sets the length of the arrow.
     * Sets the length of the arrow (including the head).
     * @param GLfloat length    the new length of the arrow
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
     * Sets the thickness of the arrow.
     * Sets the thickness of the arrow (width of each side).
     * @param GLfloat thickness    the new thickness of the arrow
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

    void Arrow::setTipPosition(Vector &v){
      pointTo(v);
      setLength(v.norm());
    }

		
    /**
     * Returns the length of the arrow.
     * Returns the length of the arrow.
     * @return GLfloat length    the length of the arrow
     * @see setLength
     * @see thickness
     */
    GLfloat Arrow::length(){
      return l;
    }
		
    /**
     * Returns the thickness of the arrow.
     * Returns the thickness of the arrow.
     * @return GLfloat thickness    the thickness of the arrow
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
     * Create a coordinate system.
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
     * Set the axis length.
     * Sets the length of axes in the coordinate system.
     * @param float axis_length       - the new axis length
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
     * Set the axis thickness.
     * Sets the thickness of axes in the coordinate system.
     * @param float axis_thickness       - the new axis thickness
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
     * Set the orientation of the coordiante system.
     * Sets the orientation of the coordinate system. The coordiante system will render as a right 
     * handed coordinate system if right_handed is true, and as a left handed coordinate system otherwise.
     * @param bool right_handed       - whether to render the coordinate system right handed
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
     * Returns the axis length.
     * Returns the length of the coordinate system's axes.
     * @return GLfloat length    the length of the axes
     * @see setAxisLength
     * @see axisThickness
     */
    GLfloat CoordinateSystem::axisLength(){
      return axes[0]->length();
    }
		
    /**
     * Returns the axis thickness.
     * Returns the thickness of the coordinate system's axes.
     * @return GLfloat thickness    the thickness of the axes
     * @see setAxisThickness
     * @see axisLength
     */
    GLfloat CoordinateSystem::axisThickness(){
      return axes[0]->thickness();
    }
		
    /**
     * Returns true if the coordiante system is right handed.
     * Returns true if the coordiante system is right handed, false if it is left handed.
     * @return bool is_right_handed    true if the coordinate system is right handed, false otherwise
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
     * Create a vertex array.
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
     * Add a vertex.
     * Adds the point represented by the Vector v to the array, as the last vertex in the array. 
     * @param Vector v       - a vector representing a vertex to append to the array		
     * @see insertAt
     * @see vertexAt
     * @see removeAt
     * @see size
     */
    void VertexArray::add(Core::Vector &v){
      vertices.push_back(v);	
    }
		
    /**
     * Add a vertex.
     * Adds the point represented by the tuple (x, y, z) to the array, as the last vertex in the array. 
     * @param GLfloat x       - the x coordinate of the new vertex
     * @param GLfloat y       - the y coordinate of the new vertex
     * @param GLfloat z       - the z coordinate of the new vertex
     * @see insertAt
     * @see vertexAt
     * @see removeAt
     * @see size
     */
    void VertexArray::add(GLfloat x, GLfloat y, GLfloat z){
      vertices.push_back(Core::Vector(x, y, z));	
    }
		
    /**
     * Insert a vertex.
     * Inserts the point represented by the vector v into the array, in front of the vertex at the given index. An exception of
     * type Core::IndexError is raised of index is invalid. 
     * @param int index       - the index at which to insert the vertex
     * @param Vector v        - a vector representing the vertex to insert		
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
     * Insert a vertex.
     * Inserts the point represented by the tuple (x, y, z) into the array, in front of the vertex at the given index. An exception of
     * type Core::IndexError is raised of index is invalid.
     * @param int index       - the index at which to insert the vertex
     * @param GLfloat x       - the x coordinate of the vertex to insert		
     * @param GLfloat y       - the y coordinate of the vertex to insert		
     * @param GLfloat z       - the z coordinate of the vertex to insert		
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
     * Remove a vertex.
     * Removes the vertex at the given index. An exception of type Core::IndexError is raised of index is invalid. 
     * @param int index       - the index of the vertex to be removed
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
     * Get a vertex.
     * Returns the vertex at the given index. An exception of type Core::IndexError is raised if index is invalid.
     * @param int index       - index of the vertex to return
     * @return Vector& v		 - the vector at the given index
     * @see size
     */
    Core::Vector& VertexArray::vertexAt(int index){
      if ((index < 0) || (index >= vertices.size())){
	throw Core::IndexError(objectType(), "vertexAt", "invalid index");
      }
				
      return vertices[index];
    }
		
    /**
     * Set the rendering style.
     * Sets the style used to render the vertices in the array. See VertexArray::VertexArray() for a list of supported rendering styles.
     * @param int style    the style used to render the vertices in the array
     * @see style
     * @see VertexArray
     */
    void VertexArray::setStyle(int new_style){
      render_style = new_style;
    }
		
    /**
     * Set whether or not to render the reverse orientation.
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
     * Returns the rendering style.
     * Returns the style used to render the vertices in the array. See VertexArray::VertexArray() for a list of supported rendering styles.
     * @return int style    the style used to render the vertices in the array
     * @see setStyle
     * @see VertexArray
     */
    int VertexArray::style(){
      return render_style;
    }
		
    /**
     * Returns true if the object also renders its vertices in reverse.
     * Returns the value of the flag that determines if the object also renders its vertices in reverse order. See 
     * VertexArray::setRenderReverseOrientation() for a more detailed explanation.
     * @return bool also_renders_in_reverse    true if the object also renders its vertices in reverse, false otherwise
     * @see setRenderReverseOrientation
     * @see setStyle
     * @see style
     */
    bool VertexArray::renderReverseOrientation(){
      return also_render_opposite_orientation;
    }
		
		
    /**
     * Returns the size of the array.
     * Returns the size of the array, that is the number of vertices in the array.
     * @return int size    the number of vertices in the array
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
     * Create a Circle of a given radius and number of sides.
     * Creates a red Circle with a given radius and number of sides
     * @param float radius       - the radius of the circle.
     * @param int sides         - the number of sides to use when rendering the circle (affects the smoothness of the circle).
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
    }
		
    Circle::~Circle(){
      // pass
    }
		
		
		
    /* Set, Get functions */
		
    /**
     * Set the radius.
     * Sets the radius of the circle.
     * @param float radius       - the new radius
     * @see radius
     */
    void Circle::setRadius(GLfloat radius){
      if (radius <= 0){
	throw Core::ValueError(objectType(), "setRadius", "radius must be positive");
      }
      r = radius;
    }
		
    /**
     * Set the number of sides.
     * Sets the number of sides used when rendering the circle (affects its smoothness).
     * @param int sides     - the number of sides to use.
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
     * Set the rendering style.
     * Sets the style used to render the circles. Possible values are:
     - WIRE
     - FILL
     * (these are aliases for GL_LINE_LOOP and GL_POLYGON, respectively. Technically any of the styles availabe for VertexArray 
     * are acceptable, but in practice these two are the most appropriate. Try experimenting with the other style constants 
     * for funky results). 
     * @param int style    the style used to render the circle
     * @see style		
     */
    void Circle::setStyle(int new_style){
      render_style = new_style;
    }
		
    /**
     * Set whether or not to render the reverse orientation.
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
     * Get the radius.
     * Returns the radius of the circle.
     * @see setRadius
     */
    GLfloat Circle::radius(){
      return r;
    }
		
    /**
     * Get the number of sides.
     * Returns the number of sides used when rendering the circle.
     * @see setNumberOfSides
     */
    int Circle::numberOfSides(){
      return number_of_sides;
    }
		
    /**
     * Returns the rendering style.
     * Returns the style used to render the circle. See Circle::setStyle() for a list of supported rendering styles.
     * @return int style    the style used to render the circle
     * @see setStyle		
     */
    int Circle::style(){
      return render_style;
    }
		
    /**
     * Returns true if the circle also renders its vertices in reverse.
     * Returns the value of the flag that determines if the circle also renders in reverse orientation. See 
     * Circle::setRenderReverseOrientation() for a more detailed explanation.
     * @return bool also_renders_in_reverse    true if the circle also renders its vertices in reverse, false otherwise
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
     * Create an n-gon of a given radius and number of sides.
     * Creates a symmetric n-gon with a given radius and number of sides
     * @param float radius       - the radius of the n-gon, the distance from its center to any of its vertices.
     * @param int sides         - the number of sides to use when rendering the n-gon.
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
     * Create a rectangle of a given width and length.
     * Creates a rectangle with a given width and length
     * @param GLfloat width       - the width of the rectangle
     * @param GLfloat length		 - the length of the rectangle		
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
     * Set the width.
     * Sets the width of the rectangle.
     * @param GLfloat width       - the new width
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
     * Set the length.
     * Sets the length of the rectangle.
     * @param GLfloat length       - the new length
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
     * Set the dimensions.
     * Sets the width and length of the rectangle.
     * @param GLfloat width       - the new width
     * @param GLfloat length       - the new length
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
     * Set the rendering style.
     * Sets the style used to render the circles. Possible values are:
     - WIRE
     - FILL
     * (these are aliases for GL_LINE_LOOP and GL_POLYGON, respectively. Technically any of the styles availabe for VertexArray 
     * are acceptable, but in practice these two are the most appropriate. Try experimenting with the other style constants 
     * for funky results). 
     * @param int style    the style used to render the circle
     * @see style		
     */
    void Rectangle::setStyle(int new_style){
      render_style = new_style;
    }
		
    /**
     * Set whether or not to render the reverse orientation.
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
     * Get the width.
     * Returns the width of the rectangle.
     * @see setWidth
     */
    GLfloat Rectangle::width(){
      return w;
    }
		
    /**
     * Get the length.
     * Returns the length of the rectangle.
     * @see setLength
     */
    GLfloat Rectangle::length(){
      return l;
    }
		
    /**
     * Returns the rendering style.
     * Returns the style used to render the circle. See Rectangle::setStyle() for a list of supported rendering styles.
     * @return int style    the style used to render the circle
     * @see setStyle		
     */
    int Rectangle::style(){
      return render_style;
    }
		
    /**
     * Returns true if the circle also renders its vertices in reverse.
     * Returns the value of the flag that determines if the circle also renders in reverse orientation. See 
     * Rectangle::setRenderReverseOrientation() for a more detailed explanation.
     * @return bool also_renders_in_reverse    true if the circle also renders its vertices in reverse, false otherwise
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
		
		
  } // Geometry
} // Mango