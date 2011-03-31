#include "core/frame.h"
#include "core/core.h"

namespace Mango{
  namespace Core{
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

    Frame::~Frame(){
    }

    /**
     * Set the orientation axes.
     * Sets the orientation axes of the object. The objects orientation in 3-space is determined by rotating
     * it by its first orientation angle about its first orientation axis, then rotating it by its second
     * orientation angle about its second oreintation axis (relative to the new coordinate system obtained
     * from the first rotation) and finally rotating by its third orientation angle about its third orientation
     * axis (again relative to the new coordinate system). The default values are
     *
     * u1 = (0, 1, 0) // the y-axis
     *
     * u2 = (1, 0, 0) // the x-axis
     *
     * u3 = (0, 1, 0) // the y-axis
     *
     * With these values, the oreintation angles of the object are equivalent to its Euler angles.
     * @param Vector u1    the first orientation axis
     * @param Vector u2    the second orientation axis
     * @param Vector u3    the third orientation axis
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
     * Set the orientation angles.
     * Sets all three orientation angles of the object. For an explanation of the role of the orientation angles 
     * see Frame::setOrientationAxes.
     * @param GLfloat alpha    the first orientation angle
     * @param GLfloat beta     the second orientation angle
     * @param GLfloat gamma    the third orientation angle
     * @see setOrientationAxes
     * @see orientation
     */
    void Frame::setOrientation(GLfloat angle_alpha, GLfloat angle_beta, GLfloat angle_gamma){
      alpha = angle_alpha;
      beta = angle_beta;
      gamma = angle_gamma;
    }
		

    /**
     * Retrieve the object's orientation axes.
     * Retrieves the object's orientation axes, by assigning them to three Vector variables passed as arguments by reference.
     * @param Vector &vec_u1      a reference to a Vector variable that will be assigned the value of the first orientation axis
     * @param Vector &vec_u2      a reference to a Vector variable that will be assigned the value of the second orientation axis
     * @param Vector &vec_u3      a reference to a Vector variable that will be assigned the value of the third orientation axis
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
     * Retrieve the object's orientation angles.
     * Retrieves the object's orientation angles, by assigning them to three GLfloat variables passed as arguments by reference.
     * @param GLfloat &alpha      a reference to a GLfloat variable that will be assigned the value of the first orientation angle
     * @param GLfloat &beta      a reference to a GLfloat variable that will be assigned the value of the second orientation angle
     * @param GLfloat &gamma      a reference to a GLfloat variable that will be assigned the value of the third orientation angle
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
     * Translate the position of the object.
     * Translates the position of the object's frame of reference.
     * @param GLfloat dx     the change in the x-component.
     * @param GLfloat dy     the change in the y-component.
     * @param GLfloat dz     the change in the z-component.
     * @see rotate
     */
    void Frame::translate(GLfloat dx, GLfloat dy, GLfloat dz){
      position[0] += dx;
      position[1] += dy;
      position[2] += dz;
    }
		
    /**
     * Translate the frame of reference.
     * Translates the frame of reference.
     * @param GLfloat dpos 	a vector representing the change to effect in the frame's position
     * @see rotate
     */
    void Frame::translate(Vector &dv){
      position += dv;
    }

    /**
     * Rotate the frame of reference.
     * Rotates the frame of reference by modifying its orientation angles.
     * @param GLfloat dalpha -   the change in the first orientation angle
     * @param GLfloat dbeta -    the change in the second orientation angle
     * @param GLfloat dgamma -   the change in the third orientation angle
     */
    void Frame::rotate(GLfloat dalpha, GLfloat dbeta, GLfloat dgamma){
      alpha += dalpha;
      beta += dbeta;
      gamma += dgamma;
    }


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


    Vector Frame::transformToParent(Vector &w){
      Matrix Rotation = rotationToParent();
      Vector v = Rotation.transform(w);
      v += position;
      return v;
    }

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



    Vector Frame::transformFromParent(Vector &w){
      Matrix Rotation = rotationFromParent();      
      Vector v = w - position;
      v = Rotation.transform(v);
      return v;
    }

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






    void Frame::orientationFor(Vector &v, GLfloat &alef, GLfloat &bet){
      GLfloat r;      
      r = v.norm();
      if (r == 0){
	return;
      }

      alef = (180 / 3.14159265358979323846) * atan2(v[0], v[2]);
      bet = 90 - (180 / 3.14159265358979323846) * asin(v[1]/r);
    }

    void Frame::pointTo(Vector &v){
      orientationFor(v, alpha, beta);
    }

    /**
     * Return the frame's parent frame of reference.
     * Returns a poitner to the parent frame of reference of this frame of reference.
     * @return  Frame *parent_frame           pointer to the parent frame of reference
     * @see setParentFrame
     */
    Frame *Frame::parentFrame(){
      return parent_frame;
    }

    /**
     * Set the frame's parent frame of reference.
     * Sets the frame's parent frame of reference. Passing NULL will cause the global frame of reference to be used. The 
     * function will return true on success and false on failure. Failure can result from passing a pointer to a frame 
     * that would cause a circular loop of frames (e.g. passing the frame itself or a frame that has this frame as an 
     * ancestor). 
     * @param  Frame* parent_frame            pointer to a frame that will be the new parent frame of reference.
     * @return bool   success                 true on success, false on failure
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
     * Check if a frame is an ancestor of this frame.
     * Returns true of the argument is an ancestor of this frame, false otherwise
     * @param  Frame *suspect_ancestor         a frame to check ancestry against
     * @return bool   is_ancestor              true if suspect_ancestor is an ancestor of this frame, false otherwise
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
     * Transform to the frame's position and orientation
     * Transforms the rendering point to the frame's position and orientation, in preparation for rendering in this 
     * frame of reference. If true  is passed, this method will first call transform on its parent, causing the final 
     * transformation to be relative to the global frame. If false is passed as an argument, the method will not
     * invoke its parent transformation and so the final transformation will be relative to its parent frame. The
     *  default value of the argument is true.
     * @param bool transform_parent                true to invoke the same method on the parent, false to avoid doing so
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
