#include "core/core.h"
#include <vector>
#include "mango.h"

#ifndef MANGO_GEOMETRY
#define MANGO_GEOMETRY

namespace Mango{
  namespace Geometry{
    
    
    /**
     * An object with color properties.
     * An object with red, green, blue and alpha color values with matching set and get functions. This object
     * is the base class for all objects that have a color.
     */
    class ColorfulObject : public Core::Object{
    public:		    	
      ColorfulObject();
      ~ColorfulObject();
      
      virtual const char *objectType() const{
	return "ColorfulObject";
      }
      
      void setColor(GLfloat c_r, GLfloat c_g, GLfloat c_b);
      void setRedComponent(GLfloat c_r);
      void setGreenComponent(GLfloat c_g);
      void setBlueComponent(GLfloat c_b);				
      
      void color(GLfloat &c_r, GLfloat &c_g, GLfloat &c_b);	
      GLfloat redComponent();
      GLfloat greenComponent();
      GLfloat blueComponent();		        
      
    protected:
      GLfloat color_r, color_g, color_b;
      //GLfloat color_alpha;
    };
    
    
    /**
     * A "box".
     * A "box" of particular dimensions, color with outward-pointing normals.
     */
    class Box : public ColorfulObject{
    public:		    	
      Box(GLfloat h=1.0, GLfloat w=1.0, GLfloat l=1.0);
      ~Box();
      
      virtual const char *objectType() const{
	return "Box";
      }
      
      void setDimensions(GLfloat h, GLfloat w, GLfloat l);		        		
      void dimensions(GLfloat &h, GLfloat &w, GLfloat &l);	
      
      virtual void render();
      
    protected:
      GLfloat height, width, length;
    };
    
    
    
    
    /**
     * A sphere.
     * A sphere of arbitrary radius, color and smoothness with outward pointing normals.
     */
    class Sphere : public ColorfulObject{
    public:
      Sphere(GLfloat radius = 1.0, int sides = 24);
      ~Sphere();
      
      virtual const char *objectType() const{
	return "Sphere";
      }
      
      void setRadius(GLfloat radius);
      void setNumberOfSides(int sides);		        
      
      GLfloat radius();
      int numberOfSides();		        
      
      virtual void render();
      
    protected:
      int sides;
      GLfloat r, dtheta, dphi;
      
    };
    
    
    
    
    
    
    
    
    /**
     * A cylinder.
     * A cylinder of arbitrary radius, height, color and smoothness with outward pointing normals.
     */
    class Cylinder : public ColorfulObject{
    public:
      Cylinder(GLfloat radius = 1.0, GLfloat height = 2.0, int num_sides = 24);
      ~Cylinder();
      
      virtual const char *objectType() const{
	return "Cylinder";
      }
      
      void setRadius(GLfloat radius);
      void setHeight(GLfloat height);
      void setNumberOfSides(int sides);		        
      
      GLfloat radius();
      GLfloat height();
      int numberOfSides();		        
      
      virtual void render();
      
    protected:
      int sides;
      GLfloat r, dtheta, h_over_2;		
    };
    
    
    
    
    
    /**
     * A shell.
     * A shell of arbitrary radius, color and smoothness with outward pointing normals.
     */
    class Shell : public ColorfulObject{
    public:
      Shell(GLfloat radius = 1.0,  GLfloat thickness=0.1, GLfloat fraction=0.3, int sides = 24);
      ~Shell();
      
      virtual const char *objectType() const{
	return "Shell";
      }
      
      void setRadius(GLfloat radius);
      void setThickness(GLfloat thickness);
      void setFraction(GLfloat fraction);
      void setNumberOfSides(int sides);		        
      
      GLfloat radius();
      GLfloat thickness();
      GLfloat fraction();
      int numberOfSides();		        
      
      virtual void render();
      
    protected:
      GLfloat r, t, f, dtheta, dphi;
      GLfloat irr; // ratio of inner radius to (inner radius + thickness)
      int num_sides;
      
    };
    
    
    
    
    
    
    
    /**
     * An arrow.
     * An arrow of arbitrary length, thickness and color, with outward normals.
     */
    class Arrow : public ColorfulObject{
    public:
      Arrow(GLfloat length = 1, GLfloat thickness = 0.1);
      ~Arrow();
      
      virtual const char *objectType() const{
	return "Arrow";
      }
      
      void setLength(GLfloat length);
      void setThickness(GLfloat thickness);        
      void setTipPosition(Vector &v);

      GLfloat length();
      GLfloat thickness();        
      
      
      
      virtual void render();
      
    protected:
      GLfloat l, w_x, w_y;        
      GLfloat pyramid_base_ratio, pyramid_height_fraction;
    };
    
    
    
    
    
    
    
		
    
    
    
    
    
    
    /**
     * A coordinate system.
     * A set of orthogonal axes that form a three dimensional coordinate system of given orientation, axis length and axis thickness.
     */
    class CoordinateSystem : public Core::Object{
    public:
      CoordinateSystem();
      ~CoordinateSystem();
      
      virtual const char *objectType() const{
	return "CoordinateSystem";
      }
      
      void setAxisLength(GLfloat length);
      void setAxisThickness(GLfloat thickness);        
      void setRightHanded(bool is_r_handed);				
      
      GLfloat axisLength();
      GLfloat axisThickness();        
      bool rightHanded();		

      virtual void render();
      
    protected:
      Arrow* axes[3];		        
    };
    
    
    
		
		
		
		
		
    /**
     * A collection of vertices.
     * A collection of vertices that are rendered with a given style. This object provides an interface that allows defining 
     * sophisticated two and three dimensional shapes without overriding an Object's render event. The object will render the 
     * vertices in order, with one of the following styles:
     * 	GL_POINTS                 - render the vertices as individual points
     * 	GL_LINES              	  - render a lines between each consecutive, non-overlapping pair of vertices
     * 	GL_LINE_LOOP          	  - render a line between each consecutive, overlapping pair of vertices, including the last and first
     * 	GL_LINE_STRIP             - render a line between each consecutive, overlapping pair of vertices, not including the last and first
     * 	GL_TRIANGLES              - render a triangle between each consecutive, non-overlapping triplet of vertices
     * 	GL_TRIANGLE_STRIP         - ?
     * 	GL_TRIANGLE_FAN           - ?
     * 	GL_QUADS                  - render a quad between each consecutive, non-overlapping quadruplet of vertices
     * 	GL_QUAD_STRIP             - ?
     * 	GL_POLYGON 				  - ?
     */
    class VertexArray : public ColorfulObject {
    public:
      VertexArray();
      ~VertexArray();
      
      virtual const char *objectType() const{
	return "VertexArray";
      }
      
      void add(Core::Vector &v);
      void add(GLfloat x, GLfloat y, GLfloat z);
      void insertAt(int index, Core::Vector &v);
      void insertAt(int index, GLfloat x, GLfloat y, GLfloat z);
      Core::Vector& vertexAt(int index);
      void removeAt(int index);
				
      inline Core::Vector& operator[](int index){
	if ((index < 0) || (index >= vertices.size())){
	  throw Core::IndexError(objectType(), "[]", "invalid index");
	}
	
	return vertices[index];
      }        
      
      void setRenderReverseOrientation(bool render_in_reverse);
      void setStyle(int new_style);     
      
      int style();
      bool renderReverseOrientation();
      int size();
      
      virtual void render();	        
      
    protected:
      std::vector<Core::Vector> vertices;
      int render_style;
      bool also_render_opposite_orientation;
    };
    
    
		
		
		
		
    
		
		
		
		
		
    
    /**
     * A circle.
     * A circle with a given radius and smoothness.
     */
    class Circle : public ColorfulObject {
    public:
      Circle(GLfloat radius = 1.0, int num_sides=24);
      ~Circle();
      
      virtual const char *objectType() const{
	return "Circle";
      }
      
      void setRadius(GLfloat radius);
      void setNumberOfSides(int sides);
      void setStyle(int new_style);     
      void setRenderReverseOrientation(bool render_in_reverse);
      
      GLfloat radius();
      int numberOfSides();
      int style();	
      bool renderReverseOrientation();	        
						
      virtual void render();
      virtual void draw();
      
    protected:
      GLfloat r, dtheta;
      int number_of_sides, render_style;
      bool also_render_opposite_orientation;
    };
    
    
    /**
     * A symmetric n-gon.
     * A symmetric n-gon with n sides, with a given radius.
     */
    class NGon : public Circle {
    public:
      NGon(GLfloat radius = 1.0, int num_sides=5);
      ~NGon();
      
      virtual const char *objectType() const{
	return "NGon";
      }			        		        			                										        	    
    };
    
    
    
		
		
		
		
		
    
    /**
     * A rectangle.
     * A rectangle with given width and length.
     */
    class Rectangle : public ColorfulObject {
    public:
      Rectangle(GLfloat width = 1.0, GLfloat height = 1.618);
      ~Rectangle();
      
      virtual const char *objectType() const{
	return "Rectangle";
      }
      
      void setWidth(GLfloat width);
      void setLength(GLfloat length);
      void setDimensions(GLfloat width, GLfloat length);
      void setStyle(int new_style);     
      void setRenderReverseOrientation(bool render_in_reverse);
      
      GLfloat width();
      GLfloat length();		        		        
      int style();	
      bool renderReverseOrientation();	        
      
      virtual void render();
      virtual void draw();
      
    protected:
      GLfloat w, l;
      int render_style;
      bool also_render_opposite_orientation;
    };
    
    
    
  } // Geometry	
} // Mango

#endif // MANGO_GEOMETRY

