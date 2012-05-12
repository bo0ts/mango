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
#include "core.h"

#ifndef MANGO_CORE_TRIANGLE
#define MANGO_CORE_TRIANGLE

namespace Mango{
  namespace Core{
		
    /**
     * A colorful, equilateral triangle. This is the only object in
     * the core library that implements a render event, and as such is
     * useful to test Mango independently of other modules like
     * Geometry.
     */
    class Triangle : public Object{
    public:
      Triangle();
      ~Triangle();
		
      virtual const char *objectType() const{
	return "Triangle";
      }
		
      void setSize(GLfloat size);
		
      GLfloat size();
		
      virtual void render();
    protected:
      GLfloat tsize;		
    };
		
  } // Core
} // Mango

#endif // MANGO_CORE_TRIANGLE

