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
#include <math.h>
#include "mango_opengl.h"
#include "vector.h"

#ifndef MANGO_CORE_MATRIX
#define MANGO_CORE_MATRIX

namespace Mango{
  namespace Core{

    /**
     * Three dimensional matrix class. Supports basic matrix
     * operations (adding, subtracting, scaling, comparing,
     * transforming other matrices and vectors) as well as several
     * convenience methods such as computation of trace, determinant
     * and inverse.
     */
    class Matrix {
    public:
			
      // Constructors
      inline Matrix(){
	M[0][0] = 1.0;
	M[0][1] = 0.0;
	M[0][2] = 0.0;
		       
	M[1][0] = 0.0;
	M[1][1] = 1.0;
	M[1][2] = 0.0;

	M[2][0] = 0.0;
	M[2][1] = 0.0;
	M[2][2] = 1.0;
      }
		
      inline Matrix(GLfloat m00, GLfloat m01, GLfloat m02, 
		    GLfloat m10, GLfloat m11, GLfloat m12, 
		    GLfloat m20, GLfloat m21, GLfloat m22){
	M[0][0] = m00;
	M[0][1] = m01;
	M[0][2] = m02;
		       
	M[1][0] = m10;
	M[1][1] = m11;
	M[1][2] = m12;

	M[2][0] = m20;
	M[2][1] = m21;
	M[2][2] = m22;
      }		 
		
      inline Matrix(const Matrix &N){       
	M[0][0] = N.M[0][0];
	M[0][1] = N.M[0][1];
	M[0][2] = N.M[0][2];
		       
	M[1][0] = N.M[1][0];
	M[1][1] = N.M[1][1];
	M[1][2] = N.M[1][2];

	M[2][0] = N.M[2][0];
	M[2][1] = N.M[2][1];
	M[2][2] = N.M[2][2];		       
      }
		
      inline Matrix &operator=(const Matrix &N){
	M[0][0] = N.M[0][0];
	M[0][1] = N.M[0][1];
	M[0][2] = N.M[0][2];
		       
	M[1][0] = N.M[1][0];
	M[1][1] = N.M[1][1];
	M[1][2] = N.M[1][2];

	M[2][0] = N.M[2][0];
	M[2][1] = N.M[2][1];
	M[2][2] = N.M[2][2];
	return *this;
      }
		
      // Access
      inline GLfloat* operator[](int i){
	return M[i];
      }
		
      inline const GLfloat* operator[](int i) const{
	return M[i];
      }	       
		
      // Comparison
      inline bool operator==(const Matrix &N){
	return ((M[0][0] == N.M[0][0]) && (M[0][1] == N.M[0][1]) && (M[0][2] == N.M[0][2]) && 
		(M[1][0] == N.M[1][0]) && (M[1][1] == N.M[1][1]) && (M[1][2] == N.M[1][2]) && 
		(M[2][0] == N.M[2][0]) && (M[2][1] == N.M[2][1]) && (M[2][2] == N.M[2][2]));
      }
		
      inline bool operator!=(const Matrix &N){
	return ((M[0][0] != N.M[0][0]) || (M[0][1] != N.M[0][1]) || (M[0][2] != N.M[0][2]) || 
		(M[1][0] != N.M[1][0]) || (M[1][1] != N.M[1][1]) || (M[1][2] != N.M[1][2]) || 
		(M[2][0] != N.M[2][0]) || (M[2][1] != N.M[2][1]) || (M[2][2] != N.M[2][2]));
      }		     		     		     
		     
      // Transformation
      inline Vector transform(Vector w){
	Vector v;
	v[0] = (M[0][0]*w.v[0] + M[0][1]*w.v[1] + M[0][2]*w.v[2]);
	v[1] = (M[1][0]*w.v[0] + M[1][1]*w.v[1] + M[1][2]*w.v[2]);
	v[2] = (M[2][0]*w.v[0] + M[2][1]*w.v[1] + M[2][2]*w.v[2]);
	return v;
      }
		     
      inline Matrix transform(Matrix N){
	Matrix P;
	int i, j;
	for (i = 0; i <= 2; i += 1){
	  for (j = 0; j <= 2; j += 1){
	    P[i][j] = M[i][0]*N.M[0][j] + M[i][1]*N.M[1][j] + M[i][2]*N.M[2][j];
	  }
	}
	return P;
      }

      inline Vector rightTransform(Vector w){
	Vector v;
	v[0] = (M[0][0]*w.v[0] + M[1][0]*w.v[1] + M[2][0]*w.v[2]);
	v[1] = (M[0][1]*w.v[0] + M[1][1]*w.v[1] + M[2][1]*w.v[2]);
	v[2] = (M[0][2]*w.v[0] + M[1][2]*w.v[1] + M[2][2]*w.v[2]);
	return v;
      }

      inline Matrix rightTransform(Matrix N){
	Matrix P;
	int i, j;
	for (i = 0; i <= 2; i += 1){
	  for (j = 0; j <= 2; j += 1){
	    P[i][j] = N.M[i][0]*M[0][j] + N.M[i][1]*M[1][j] + N.M[i][2]*M[2][j];
	  }
	}
	return P;
      }
		     
      // Scalar multiplication / division
      inline Matrix& operator*=(double k){
	M[0][0] *= k;
	M[0][1] *= k;
	M[0][2] *= k;
		       
	M[1][0] *= k;
	M[1][1] *= k;
	M[1][2] *= k;

	M[2][0] *= k;
	M[2][1] *= k;
	M[2][2] *= k;
	return *this;
      }
		
      inline Matrix& operator/=(double k){
	if (k == 0){
	  return *this;
	}

	k = 1.0/k;
	M[0][0] *= k;
	M[0][1] *= k;
	M[0][2] *= k;
		       
	M[1][0] *= k;
	M[1][1] *= k;
	M[1][2] *= k;

	M[2][0] *= k;
	M[2][1] *= k;
	M[2][2] *= k;
	return *this;
      }
		
      inline Matrix operator-(){
	return Matrix(-M[0][0], -M[0][1], -M[0][2],
		      -M[1][0], -M[1][1], -M[1][2],
		      -M[2][0], -M[2][1], -M[2][2]);
      }          
		
      inline Matrix operator*(double k) const
	{
	  return Matrix(k*M[0][0], k*M[0][1], k*M[0][2],
			k*M[1][0], k*M[1][1], k*M[1][2],
			k*M[2][0], k*M[2][1], k*M[2][2]);
	}
		
      inline Matrix operator/(double k) const
      {		       
	k = 1.0/k;
	return Matrix(k*M[0][0], k*M[0][1], k*M[0][2],
		      k*M[1][0], k*M[1][1], k*M[1][2],
		      k*M[2][0], k*M[2][1], k*M[2][2]);
      }
		
      // Invariants
      inline GLfloat tr() const{
	return (M[0][0] + M[1][1] + M[2][2]);
      }

      inline GLfloat det() const{
	return ((M[0][0] * (M[1][1]*M[2][2] - M[1][2]*M[2][1])) - \
		(M[1][1] * (M[1][0]*M[2][2] - M[1][2]*M[2][0])) + \
		(M[2][2] * (M[1][0]*M[2][1] - M[1][1]*M[2][0])));
      }
		     

      // Matrix Algebra
      inline Matrix& operator+=(const Matrix& N){
	M[0][0] += N.M[0][0];
	M[0][1] += N.M[0][1];
	M[0][2] += N.M[0][2];

	M[1][0] += N.M[1][0];
	M[1][1] += N.M[1][1];
	M[1][2] += N.M[1][2];

	M[2][0] += N.M[2][0];
	M[2][1] += N.M[2][1];
	M[2][2] += N.M[2][2];
	return *this;
      }
		
      inline Matrix& operator-=(const Matrix& N){
	M[0][0] -= N.M[0][0];
	M[0][1] -= N.M[0][1];
	M[0][2] -= N.M[0][2];

	M[1][0] -= N.M[1][0];
	M[1][1] -= N.M[1][1];
	M[1][2] -= N.M[1][2];

	M[2][0] -= N.M[2][0];
	M[2][1] -= N.M[2][1];
	M[2][2] -= N.M[2][2];
	return *this;
      }
		
      inline Matrix operator+(const Matrix& N) const{
	return Matrix(M[0][0] + N.M[0][0], M[0][1] + N.M[0][1], M[0][2] + N.M[0][2], 
		      M[1][0] + N.M[1][0], M[1][1] + N.M[1][1], M[1][2] + N.M[1][2], 
		      M[2][0] + N.M[2][0], M[2][1] + N.M[2][1], M[2][2] + N.M[2][2]);
      }
		
      inline Matrix operator-(const Matrix& N) const{
	return Matrix(M[0][0] - N.M[0][0], M[0][1] - N.M[0][1], M[0][2] - N.M[0][2], 
		      M[1][0] - N.M[1][0], M[1][1] - N.M[1][1], M[1][2] - N.M[1][2], 
		      M[2][0] - N.M[2][0], M[2][1] - N.M[2][1], M[2][2] - N.M[2][2]);
      }
		
      inline Matrix transpose() const{
	return Matrix(M[0][0], M[1][0], M[2][0], 
		      M[0][1], M[1][1], M[2][1], 
		      M[0][2], M[1][2], M[2][2]);
      }

      inline Matrix inverse() const{
	return *this;
      }

      GLfloat M[3][3];
    };
  }
}

#endif // MANGO_CORE_MATRIX
