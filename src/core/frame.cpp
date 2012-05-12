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
#include <mango/core/frame.h>
#include <mango/core/core.h>

namespace Mango{
  namespace Core{

    /**
     * Create a Frame at position (0, 0, 0)  with orientation axes
     * (0, 1, 0), (1, 0, 0) and (0, 1, 0) and rotation angles all
     * 0. The default parent frame is the global GlobalFrame, unless
     * this frame is indicated as being itself a GlobalFrame.     
     */
    Frame::Frame(bool is_global_frame){
      position[0] = 0;
      position[1] = 0;
      position[2] = 0;		
		
      u1[0] = 0;
      u1[1] = 1;
      u1[2] = 0;
		
      u2[0] = 1;
      u2[1] = 0;
      u2[2] = 0;
		
      u3[0] = 0;
      u3[1] = 1;
      u3[2] = 0;
		
      alpha = 0;
      beta = 0;
      gamma = 0;

      parent_frame = (is_global_frame ? NULL : GlobalFrame);
    }

    /**
     * Destroy frame instance
     */
    Frame::~Frame(){
    }

    /**
     * Set the orientation axes of the object. The object's
     * orientation in 3-space is determined by rotating it by its
     * first orientation angle about its first orientation axis, then
     * rotating it by its second orientation angle about its second
     * oreintation axis (relative to the new coordinate system
     * obtained from the first rotation) and finally rotating by its
     * third orientation angle about its third orientation axis (again
     * relative to the new coordinate system).
     */
    void Frame::setOrientationAxes(Vector &new_u1, Vector &new_u2, Vector &new_u3){
      if (new_u1[0] == 0 && new_u1[1] == 0 && new_u1[2] == 0){
	throw ValueError(objectType(), "setOrientationAxes", "orientation axis u1 cannot be the zero vector");
      }
      else if (new_u2[0] == 0 && new_u2[1] == 0 && new_u2[2] == 0){
	throw ValueError(objectType(), "setOrientationAxes", "orientation axis u2 cannot be the zero vector");
      }
      else if (new_u3[0] == 0 && new_u3[1] == 0 && new_u3[2] == 0){
	throw ValueError(objectType(), "setOrientationAxes", "orientation axis u3 cannot be the zero vector");
      }
		
      u1 = new_u1;
      u2 = new_u2;
      u3 = new_u3;
    }
		
    /**     
     * Set all three orientation angles of the object. For an
     * explanation of the role of the orientation angles see
     * Frame::setOrientationAxes.  
     *
     * @see setOrientationAxes 
     * @see orientation
     */
    void Frame::setOrientation(GLfloat angle_alpha, GLfloat angle_beta, GLfloat angle_gamma){
      alpha = angle_alpha;
      beta = angle_beta;
      gamma = angle_gamma;
    }
		

    /**
     * Retrieve the object's orientation axes, by assigning them to
     * three Vector variables passed as arguments by reference.    
     *
     * @see setOrientationAxes
     * @see setOrientation
     * @see orientation
     */
    void Frame::orientationAxes(Vector &vec_u1, Vector &vec_u2, Vector &vec_u3){
      vec_u1 = u1;
      vec_u2 = u2;
      vec_u3 = u3;
    }
		
    /**
     * Retrieve the object's orientation angles, by assigning them to
     * three GLfloat variables passed as arguments by reference.     
     *
     * @see setOrientation
     * @see setOrientationAxes
     * @see orientationAxes
     */
    void Frame::orientation(GLfloat &angle_alpha, GLfloat &angle_beta, GLfloat &angle_gamma){
      angle_alpha = alpha;
      angle_beta = beta;
      angle_gamma = gamma;
    }
		
    /**
     * Translate the position of the frame of reference.     
     *
     * @see rotate
     */
    void Frame::translate(GLfloat dx, GLfloat dy, GLfloat dz){
      position[0] += dx;
      position[1] += dy;
      position[2] += dz;
    }
		
    /**
     * Translate the position of the frame of reference.     
     *
     * @see rotate
     */
    void Frame::translate(Vector &dv){
      position += dv;
    }

    /**
     * Rotate the frame of reference by modifying its orientation
     * angles. The given values will be added to the corresponding
     * orientation angles (e.g. dalpha to alpha, dbeta to beta, dgamma
     * to gamma).
     *
     * @see setOrientation
     */
    void Frame::rotate(GLfloat dalpha, GLfloat dbeta, GLfloat dgamma){
      alpha += dalpha;
      beta += dbeta;
      gamma += dgamma;
    }


    /** 
     * Calculate and return a rotation matrix representing the tranformation
     * from the parent's orientation to this frame's orientation.
     *
     */
    Matrix Frame::rotationFromParent(){
      GLfloat m[17];
      Matrix M;

      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();
      glRotated(alpha, u1[0], u1[1], u1[2]);
      glRotated(beta, u2[0], u2[1], u2[2]);
      glRotated(gamma, u3[0], u3[1], u3[2]);

      glGetFloatv(GL_MODELVIEW_MATRIX, m);

      M[0][0] = m[0];
      M[0][1] = m[1];
      M[0][2] = m[2];

      M[1][0] = m[4];
      M[1][1] = m[5];
      M[1][2] = m[6];

      M[2][0] = m[8];
      M[2][1] = m[9];
      M[2][2] = m[10];

      glPopMatrix();

      return M;
    }

    /** 
     * Calculate and return a rotation matrix representing the tranformation
     * from this frame's orientation to the parent's orientation.
     */
    Matrix Frame::rotationToParent(){
      GLfloat m[17];
      Matrix M;

      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();
      glRotated(-gamma, u3[0], u3[1], u3[2]);
      glRotated(-beta, u2[0], u2[1], u2[2]);      
      glRotated(-alpha, u1[0], u1[1], u1[2]);
      glGetFloatv(GL_MODELVIEW_MATRIX, m);

      M[0][0] = m[0];
      M[0][1] = m[1];
      M[0][2] = m[2];

      M[1][0] = m[4];
      M[1][1] = m[5];
      M[1][2] = m[6];

      M[2][0] = m[8];
      M[2][1] = m[9];
      M[2][2] = m[10];

      glPopMatrix();

      return M;
    }


    /** 
     * Transform and return the given vector to the parent's frame of
     * reference.  If one thinks of the given vector graphically as
     * having its base at the origin of this frame of reference and
     * it's tip at the point it represents relative to this frame of
     * reference, the returned vector would have its tip at the same point
     * in 3-space but its base at the origin of the parent frame.
     *
     * @see transformToAncestor
     * @see transformFromParent
     */
    Vector Frame::transformToParent(Vector &w){
      Matrix Rotation = rotationToParent();
      Vector v = Rotation.transform(w);
      v += position;
      return v;
    }

    /** 
     * Transform and return the given vector to the given ancestor's
     * frame of reference. If the given frame is not actually an
     * ancestor of this frame, a Core::ValueError will be thrown. 
     *
     * @see transformToParent
     * @see transformFromAncestor
     */
    Vector Frame::transformToAncestor(Vector &w, Frame *ancestor){
      Vector v;
      if ((parent_frame == NULL) && (ancestor != this)){
	throw ValueError(objectType(), "transformToAncestor", "called with a frame that is not an ancestor");
      }
      else if (ancestor == this){
	return w;
      }

      v = transformToParent(w);
      return parent_frame->transformToAncestor(v, ancestor);
    }


    /** 
     * Transform and return the given vector from the parent frame of
     * reference to this one.  If one thinks of the given vector
     * graphically as having its base at the origin of the parent
     * frame of reference and it's tip at the point it represents
     * relative to the parent, the returned vector would have its tip
     * at the same point in 3-space but its base at the origin of this
     * frame of reference.
     *
     * @see transformToParent
     * @see transformFromAncestor
     */
    Vector Frame::transformFromParent(Vector &w){
      Matrix Rotation = rotationFromParent();      
      Vector v = w - position;
      v = Rotation.transform(v);
      return v;
    }

    /** 
     * Transform and return the given vector from the given ancestor's
     * frame of reference to this one. If the given frame is not
     * actually an ancestor of this frame, a Core::ValueError will be
     * thrown.
     *
     * @see transformFromParent
     * @see transformToAncestor
     */
    Vector Frame::transformFromAncestor(Vector &w, Frame *ancestor){
      Vector v;
      if ((parent_frame == NULL) && (ancestor != this)){
	throw ValueError(objectType(), "transformFromAncestor", "called with a frame that is not an ancestor");
      }
      else if (ancestor == this){
	return w;
      }

      v = parent_frame->transformFromAncestor(w, ancestor);
      return transformFromParent(v);
    }


    /**
     * Assign the first and second orientation angles to the given
     * variables, with values so that these angles would orient a
     * frame of reference such that its y-axis points in the same
     * direction as the given vector. Note that if v has length 0 the
     * variables alef and bet will not be modified.
     *
     * @param v a 
     *   Vector that will determine the orientation angles
     *
     * @param &alef 
     *   variable that will receive the value of the first
     *   orientation angle
     *
     * @param &bet
     *   variable that will receive the value of the second
     *   orientation angle
     * 
     * @see pointTo
     */
    void Frame::orientationFor(Vector &v, GLfloat &alef, GLfloat &bet){
      GLfloat r;      
      r = v.norm();
      if (r == 0){
	return;
      }

      alef = (180 / 3.14159265358979323846) * atan2(v[0], v[2]);
      bet = 90 - (180 / 3.14159265358979323846) * asin(v[1]/r);
    }

    /**
     * Orient this frame of reference so that its y-axis points in the same
     * direction as v. If v has zero length, no change it effected to the 
     * frame's orientation.
     *
     * @see orientationFor
     */
    void Frame::pointTo(Vector &v){
      orientationFor(v, alpha, beta);
    }

    /**
     * Retrieve a pointer to the parent frame of this
     * frame of reference. A global frame of reference will return NULL.
     * 
     * @see setParentFrame
     */
    Frame *Frame::parentFrame(){
      return parent_frame;
    }

    /**
     * Set the frame's parent frame of reference. Passing NULL will
     * cause the global frame of reference to be used. The function
     * will return true on success and false on failure. Failure can
     * result from passing a pointer to a frame that would cause a
     * circular loop of frames (e.g. passing the frame itself or a
     * frame that has this frame as an ancestor).
     *
     * @return true on success, false on failure
     *
     * @see parentFrame
     */
    bool Frame::setParentFrame(Frame *new_parent_frame){
      if (new_parent_frame == NULL){
	if (this != GlobalFrame){
	  parent_frame = GlobalFrame;
	  return true;
	}
	else{
	  return false;
	}
      }

      if (this == new_parent_frame){
	return false;
      }

      if (new_parent_frame->hasFrameAsAncestor(this)){
	return false;
      }      

      parent_frame = new_parent_frame;
      return true;
    }

    /**
     * Return true if the argument is an ancestor of this frame, false
     * otherwise
     *
     * @see setParentFrame
     * @see parentFrame
     */
    bool Frame::hasFrameAsAncestor(Frame *suspect_parent){
      if (parent_frame == suspect_parent){
	return true;
      }
      if (parent_frame == NULL){
	return false;
      }
      return parent_frame->hasFrameAsAncestor(suspect_parent);
    }


    /**
     * Transform the rendering point to the frame's position and
     * orientation, in preparation for rendering in this frame of
     * reference. If true is passed, this method will first call
     * transform on its parent, causing the final transformation to be
     * relative to the global frame. If false is passed as an
     * argument, the method will not invoke its parent transformation
     * and so the final transformation will be relative to its parent
     * frame. The default value of the argument is true. Note that
     * transformation in used in the context of the OpenGL functions
     * glTranslated and glRotated.
     *
     * @see reverseTransform
     */
    void Frame::transform(bool transform_parent){
      if (transform_parent && parent_frame != NULL){
	parent_frame->transform(true);
      }

      glTranslated(position[0], position[1], position[2]);

      glRotated(alpha, u1[0], u1[1], u1[2]);
      glRotated(beta, u2[0], u2[1], u2[2]);
      glRotated(gamma, u3[0], u3[1], u3[2]);
    }

    /**
     * Transform the rendering point with the inverse transformation
     * to that determined by this frame's position and orientation. If
     * true is passed, this method will call reverseTransform on its
     * parent after performing the inverse transformation on this
     * frame.      
     * 
     * @see transform
     */
    void Frame::reverseTransform(bool transform_parent){
      glRotated(-gamma, u3[0], u3[1], u3[2]);
      glRotated(-beta, u2[0], u2[1], u2[2]);
      glRotated(-alpha, u1[0], u1[1], u1[2]);

      glTranslated(-position[0], -position[1], -position[2]);

      if (transform_parent && parent_frame != NULL){
	parent_frame->reverseTransform(true);
      }
    }
  }
}
