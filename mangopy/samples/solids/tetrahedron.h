#include "mango.h"

#ifndef MANGO_SOLIDS_TETRAHEDRON
#define MANGO_SOLIDS_TETRAHEDRON

namespace Mango{
  namespace Solids{
    class Tetrahedron: public Core::Object{
      float h;
    
    public:
      Tetrahedron():Core::Object(){
        h = 1.4142;
      }
    
      virtual void render(){
        transform();
        glBegin(GL_TRIANGLES);
    
        glNormal3f(0.0, -1.0, 0.0);    
        glColor3f(1.0, 0.0, 0.0); glVertex3f(1.0, 0.0, 0.0);
        glColor3f(0.0, 1.0, 0.0); glVertex3f(-0.5, 0.0, 0.866);
        glColor3f(0.0, 0.0, 1.0); glVertex3f(-0.5, 0.0, -0.866);
    
        glNormal3f(0.166, 0.333, 0.288);
        glColor3f(1.0, 1.0, 0.0); glVertex3f(0.0, h, 0.0);
        glColor3f(0.0, 1.0, 0.0); glVertex3f(-0.5, 0.0, 0.866);
        glColor3f(1.0, 0.0, 0.0);  glVertex3f(1.0, 0.0, 0.0);
    
        glNormal3f(0.166, 0.333, -0.288);
        glColor3f(1.0, 0.0, 0.0); glVertex3f(1.0, 0.0, 0.0);    
        glColor3f(0.0, 0.0, 1.0); glVertex3f(-0.5, 0.0, -0.866);
        glColor3f(1.0, 1.0, 0.0); glVertex3f(0.0, h, 0.0);
    
        glNormal3f(-0.333, 0.333, 0.0);
        glColor3f(1.0, 1.0, 0.0); glVertex3f(0.0, h, 0.0);        
        glColor3f(0.0, 0.0, 1.0);  glVertex3f(-0.5, 0.0, -0.866);
        glColor3f(0.0, 1.0, 0.0); glVertex3f(-0.5, 0.0, 0.866);
    
        glEnd();
      }
    
      void setHeight(float new_height){
        if (new_height <= 0){
          throw Mango::Core::ValueError(objectType(), "setHeight", "height must be positive");
        }
        h = new_height;
      }
      
      float height(){
        return h;
      }
    };
    }
};

#endif // MANGO_SOLIDS_TETRAHEDRON
