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

#ifndef MANGO_GEOMETRY
#define MANGO_GEOMETRY

#include <mango/mango.h>
#include <mango/core/core.h>
#include <vector>

namespace Mango{
  namespace Geometry{
    
    
    /**
     * An object with red, green, and blue color components with
     * matching set and get functions. This object is the base class
     * for all other objects in this module.
     */
    class ColorfulObject : public Core::Object{
    public:		    	
      ColorfulObject();
      ~ColorfulObject();
      
      //// @cond
      virtual const char *objectType() const{
	return "ColorfulObject";
      }
      //// @endcond
      
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
    };
    
    
    /**
     * A "box" of given dimensions and color, with outward-pointing normals.
     */
    class Box : public ColorfulObject{
    public:		    	
      Box(GLfloat h=1.0, GLfloat w=1.0, GLfloat l=1.0);
      ~Box();
      
      //// @cond
      virtual const char *objectType() const{
	return "Box";
      }
      //// @endcond
      
      void setDimensions(GLfloat h, GLfloat w, GLfloat l);		        		
      void dimensions(GLfloat &h, GLfloat &w, GLfloat &l);	
      
      //// @cond
      virtual void render();
      //// @endcond
      
    protected:
      GLfloat height, width, length;
    };
    
    
    
    
    /**
     * A sphere of arbitrary radius, color and smoothness with outward
     * pointing normals.
     */
    class Sphere : public ColorfulObject{
    public:
      Sphere(GLfloat radius = 1.0, int sides = 24);
      ~Sphere();
      
      //// @cond
      virtual const char *objectType() const{
	return "Sphere";
      }
      //// @endcond
      
      void setRadius(GLfloat radius);
      void setNumberOfSides(int sides);		        
      
      GLfloat radius();
      int numberOfSides();		        
      
      //// @cond
      virtual void render();
      //// @endcond
      
    protected:
      int sides;
      GLfloat r, dtheta, dphi;
      
    };
    
    
    
    
    
    
    
    
    /**
     * A cylinder of arbitrary radius, height, color and smoothness
     * with outward pointing normals.
     */
    class Cylinder : public ColorfulObject{
    public:
      Cylinder(GLfloat radius = 1.0, GLfloat height = 2.0, int num_sides = 24);
      ~Cylinder();
      
      //// @cond
      virtual const char *objectType() const{
	return "Cylinder";
      }
      //// @endcond
      
      void setRadius(GLfloat radius);
      void setHeight(GLfloat height);
      void setNumberOfSides(int sides);		        
      
      GLfloat radius();
      GLfloat height();
      int numberOfSides();		        
      
      //// @cond
      virtual void render();
      //// @endcond
      
    protected:
      int sides;
      GLfloat r, dtheta, h_over_2;		
    };
    
    
    
    
    
    /**
     * A spherical shell of arbitrary radius, color and smoothness
     * with outward and inward pointing normals.
     */
    class Shell : public ColorfulObject{
    public:
      Shell(GLfloat radius = 1.0,  GLfloat thickness=0.1, GLfloat fraction=0.3, int sides = 24);
      ~Shell();
      
      //// @cond
      virtual const char *objectType() const{
	return "Shell";
      }
      //// @endcond
      
      void setRadius(GLfloat radius);
      void setThickness(GLfloat thickness);
      void setFraction(GLfloat fraction);
      void setNumberOfSides(int sides);		        
      
      GLfloat radius();
      GLfloat thickness();
      GLfloat fraction();
      int numberOfSides();		        
      
      //// @cond
      virtual void render();
      //// @endcond
      
    protected:
      GLfloat r, t, f, dtheta, dphi;
      GLfloat irr; // ratio of inner radius to (inner radius + thickness)
      int num_sides;
      
    };
    
    
    
    
    
    
    
    /**
     * An arrow of arbitrary length, thickness and color.
     */
    class Arrow : public ColorfulObject{
    public:
      Arrow(GLfloat length = 1, GLfloat thickness = 0.1);
      ~Arrow();
      
      //// @cond
      virtual const char *objectType() const{
	return "Arrow";
      }
      //// @endcond
      
      void setLength(GLfloat length);
      void setThickness(GLfloat thickness);        
      void setTipPosition(Vector &v);

      GLfloat length();
      GLfloat thickness();        
      
      
      
      //// @cond
      virtual void render();
      //// @endcond
      
    protected:
      GLfloat l, w_x, w_y;        
      GLfloat pyramid_base_ratio, pyramid_height_fraction;
    };
    
    
    
    
    
    
    
		
    
    
    
    
    
    
    /**
     * A set of orthogonal axes that form a three dimensional
     * coordinate system of given orientation, axis length and axis
     * thickness.
     */
    class CoordinateSystem : public Core::Object{
    public:
      CoordinateSystem();
      ~CoordinateSystem();
      
      //// @cond
      virtual const char *objectType() const{
	return "CoordinateSystem";
      }
      //// @endcond
      
      void setAxisLength(GLfloat length);
      void setAxisThickness(GLfloat thickness);        
      void setRightHanded(bool is_r_handed);				
      
      GLfloat axisLength();
      GLfloat axisThickness();        
      bool rightHanded();		

      //// @cond
      virtual void render();
      //// @endcond
      
    protected:
      Arrow* axes[3];		        
    };
    
    
    
		
		
		
		
		
    /**
     * A collection of vertices that are rendered with a given
     * style. This object provides an interface that allows defining
     * sophisticated two and three dimensional shapes without
     * overriding an Object's render event. The object will render the
     * vertices in order, with one of the following styles:
     \verbatim embed:rst
 * GL_POINTS: 
     render the vertices as individual points
      
 * GL_LINES: 
     render a lines between each consecutive, 
     non-overlapping pair of vertices

 * GL_LINE_LOOP: 
     render a line between each consecutive, 
     overlapping pair of vertices, including the last and first
	  
 * GL_LINE_STRIP: 
     render a line between each consecutive, overlapping 
     pair of vertices, not including the last and first

 * GL_TRIANGLES: 
     render a triangle between each consecutive, non-overlapping 
     triplet of vertices

 * GL_TRIANGLE_STRIP: 
     render a sequence of triangles formed so: the first three
     vertices determine a triangle, and every additional vertex
     (in order) determines an additional triangle with the
     two vertices preceding it. 

 * GL_TRIANGLE_FAN: 
     render a sequence of triangles formed so: the first three 
     vertices determine a triangle, and every additional vertex
     (in order) determines an additional triangle with the 
     very first vertex and the one preceding it. 

 * GL_QUADS: 
     render a quad between each consecutive, non-overlapping 
     quadruplet of vertices

 * GL_QUAD_STRIP: 
     render a sequence of quads, formed so: the first four
     vertices determine a quad, and every additional pair of
     vertices determines a quad with the pair preceding it.

 * GL_POLYGON: 
     render a simple, convex polygon

     \endverbatim
     */
    class VertexArray : public ColorfulObject {
    public:
      VertexArray();
      ~VertexArray();
      
      //// @cond
      virtual const char *objectType() const{
	return "VertexArray";
      }
      //// @endcond
      
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
      
      //// @cond
      virtual void render();	        
      //// @endcond
      
    protected:
      std::vector<Core::Vector> vertices;
      int render_style;
      bool also_render_opposite_orientation;
    };
    
    
		
		
		
		
    
		
		
		
		
		
    
    /**
     * A circle with a given radius and smoothness.
     */
    class Circle : public ColorfulObject {
    public:
      Circle(GLfloat radius = 1.0, int num_sides=24);
      ~Circle();
      
      //// @cond
      virtual const char *objectType() const{
	return "Circle";
      }
      //// @endcond
      
      void setRadius(GLfloat radius);
      void setNumberOfSides(int sides);
      void setStyle(int new_style);     
      void setRenderReverseOrientation(bool render_in_reverse);
      
      GLfloat radius();
      int numberOfSides();
      int style();	
      bool renderReverseOrientation();	        
	
      //// @cond
      virtual void render();
      virtual void draw();
      //// @endcond
      
    protected:
      GLfloat r, dtheta;
      int number_of_sides, render_style;
      bool also_render_opposite_orientation;
    };
    
    
    /**
     * A symmetric n-gon with n sides, with a given "radius".
     */
    class NGon : public Circle {
    public:
      NGon(GLfloat radius = 1.0, int num_sides=5);
      ~NGon();
      
      //// @cond
      virtual const char *objectType() const{
	return "NGon";
      }
      //// @endcond
    };
    
    
    
		
		
		
		
		
    
    /**
     * A rectangle with given width and length.
     */
    class Rectangle : public ColorfulObject {
    public:
      Rectangle(GLfloat width = 1.0, GLfloat height = 1.618);
      ~Rectangle();
      
      //// @cond
      virtual const char *objectType() const{
	return "Rectangle";
      }
      //// @endcond
      
      void setWidth(GLfloat width);
      void setLength(GLfloat length);
      void setDimensions(GLfloat width, GLfloat length);
      void setStyle(int new_style);     
      void setRenderReverseOrientation(bool render_in_reverse);
      
      GLfloat width();
      GLfloat length();		        		        
      int style();	
      bool renderReverseOrientation();	        
      
      //// @cond
      virtual void render();
      virtual void draw();
      //// @endcond
      
    protected:
      GLfloat w, l;
      int render_style;
      bool also_render_opposite_orientation;
    };
    
    
    
  } // Geometry	
} // Mango

#endif // MANGO_GEOMETRY

