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
#include "vector.h"
#include "matrix.h"

#ifndef MANGO_FRAME
#define MANGO_FRAME

namespace Mango{
  namespace Core{
    

    /**
     * A frame of reference.
     */
    class Frame{
    public:
      Frame(bool is_global_frame = false);
      ~Frame();

      //// @cond
      virtual const char *objectType() const{
	return "Frame";
      }
      //// @endcond

      void setOrientationAxes(Vector &new_u1, Vector &new_u2, Vector &new_u3);		        
      void setOrientation(GLfloat alpha, GLfloat beta, GLfloat gamma);

      void orientationAxes(Vector &vec_u1, Vector &vec_u2, Vector &vec_u3);
      void orientation(GLfloat &alpha, GLfloat &beta, GLfloat &gamma);

      void rotate(GLfloat dalpha, GLfloat dbeta = 0, GLfloat dgamma = 0);
      void translate(GLfloat dx, GLfloat dy, GLfloat dz = 0);
      void translate(Vector &dpos);

      Matrix rotationFromParent();
      Matrix rotationToParent();

      Vector transformToParent(Vector &w);
      Vector transformToAncestor(Vector &w, Frame *ancestor);
      
      Vector transformFromParent(Vector &w);
      Vector transformFromAncestor(Vector &w, Frame *ancestor);


      void orientationFor(Vector &v, GLfloat &alpha, GLfloat &beta);
      void pointTo(Vector &v);

      Frame *parentFrame();
      bool setParentFrame(Frame *new_parent);
      bool hasFrameAsAncestor(Frame *suspect_parent);

      void transform(bool transform_parent = true);
      void reverseTransform(bool transform_parent = true);

      Vector position;
      GLfloat alpha;
      GLfloat beta;
      GLfloat gamma;

    protected:      
      Vector u1;         // First axis of rotation, defaults to z axis
      Vector u2;         // Second axis of rotation, defaults to x axis
      Vector u3;         // Third axis of rotation, defaults to z axis      

      Frame *parent_frame;
    };
  }
}


#endif // MANGO_FARME
