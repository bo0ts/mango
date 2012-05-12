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

#include <mango/core/mango_opengl.h>

#ifndef MANGO_RAW_CHARACTER_DATA
#define MANGO_RAW_CHARACTER_DATA

namespace Mango{
  namespace Draw{
    extern GLfloat raw_vertices[];
    extern int ord_map[][3];

    extern GLfloat row_min_height;
    extern GLfloat row_max_height;
// define RAW_VERTICES_SIZE 33760

  } // Draw
} // Mango

#endif // MANGO_RAW_CHARACTER_DATA
