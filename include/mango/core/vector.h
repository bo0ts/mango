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
#include <math.h>
#include "mango_opengl.h"

#ifndef MANGO_CORE_VECTOR
#define MANGO_CORE_VECTOR

namespace Mango{
  namespace Core{

    /**
     * Three dimensional vector class. Supports basic vector
     * operations (adding, subtracting, scaling, comparing) as well as
     * several convenience methods such as normalization, dot and
     * cross products with other vectors.
     */
    class Vector {
    public:
			
      // Constructors
      inline Vector(){
	v[0] = 0.0;
	v[1] = 0.0;
	v[2] = 0.0;
      }
		
      inline Vector(GLfloat x, GLfloat y, GLfloat z = 0){
	v[0] = x; 
	v[1] = y; 
	v[2] = z;
      }		 
		
      inline Vector(const Vector &w){       
	v[0]= w.v[0]; 
	v[1]= w.v[1]; 
	v[2]= w.v[2];
      }
		
      inline Vector &operator=(const Vector &w){
	v[0]= w.v[0]; 
	v[1]= w.v[1]; 
	v[2]= w.v[2];
	return *this;
      }
		
      // Access
      inline GLfloat& operator[](int i){
	return v[i];
      }
		
      inline const GLfloat& operator[](int i) const{
	return v[i];
      }
		
      inline operator GLfloat*(){
	return v;
      }
		
      // Comparison
      inline bool operator==(const Vector &w){
	return (v[0]== w.v[0]) && (v[1]== w.v[1]) && (v[2]== w.v[2]);
      }
		
      inline bool operator!=(const Vector &w){
	return (v[0] != w.v[0]) || (v[1] != w.v[1]) || (v[2] != w.v[2]);
      }

      inline bool operator==(const double &d){
	return (d == 0) && (v[0] == 0) && (v[1] == 0) && (v[2] == 0);
      }

      inline bool operator!=(const double &d){		       
	return (d != 0) || (v[0] != 0) || (v[1] != 0) || (v[2] != 0);
      }
		     
      // Norm, cross and dot
      inline double norm() const{
	return sqrt( (double)v[0]*v[0] +
		     (double)v[1]*v[1] +
		     (double)v[2]*v[2] );
      }
		
      inline double normSq() const{
	return (double)v[0]*v[0] + (double)v[1]*v[1] + (double)v[2]*v[2];
      }
		
      inline Vector& normalize(){
	double l = norm();
	if(l != 0.0){
	  l = 1.0/l;
	  v[0] *= l; 
	  v[1] *= l; 
	  v[2] *= l;
	}
	return *this;
      }
		     
      inline double dot(Vector &w){
	return (double)v[0]*w.v[0] + (double)v[1]*w.v[1] + (double)v[2]*w.v[2];
      }
		 	  	 
      inline Vector cross(Vector &w){ 	 	 	 	
	return Vector(v[1]*w[2]-v[2]*w[1], v[2]*w[0]-v[0]*w[2], v[0]*w[1]-v[1]*w[0]);
      }
		
		     
      // Scalar multiplication / division
      inline Vector& operator*=(double k){
	v[0] *= k; 
	v[1] *= k; 
	v[2] *= k;
	return *this;
      }
		
      inline Vector& operator/=(double k){
	k = 1.0/k;
	v[0] *= k;
	v[1] *= k; 
	v[2] *= k;
	return *this;
      }
		
      inline Vector operator-(){
	return Vector(-v[0], -v[1], -v[2]);
      }          
		
      inline Vector operator*(double s) const
	{
	  return Vector(v[0]*s, v[1]*s, v[2]*s);
	}
		
      inline Vector operator/(double k) const
      {
	k = 1.0/k;
	return Vector(v[0]*k, v[1]*k, v[2]*k);
      }
		
      // Vector operations
      inline Vector& operator+=(const Vector& w){
	v[0]+= w.v[0];
	v[1]+= w.v[1];
	v[2]+= w.v[2];
	return *this;
      }
		
      inline Vector& operator-=(const Vector& w){
	v[0]-= w.v[0];
	v[1]-= w.v[1];
	v[2]-= w.v[2];
	return *this;
      }
		
      inline Vector operator+(const Vector& w) const{
	return Vector(v[0]+w.v[0], v[1]+w.v[1], v[2]+w.v[2]);
      }
		
      inline Vector operator-(const Vector& w) const{
	return Vector(v[0]-w.v[0], v[1]-w.v[1], v[2]-w.v[2]);
      }
		
      GLfloat v[3];
    };
  }

  typedef Core::Vector Vector;
}

#endif // MANGO_CORE_VECTOR
