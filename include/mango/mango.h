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


#ifndef MANGO
#define MANGO 

#include <mango/core/core.h>
#include <mango/core/triangle.h>
#include <mango/draw/draw.h>
#include <stdio.h>

namespace Mango{  
  const char *full_version_string();
	
  namespace Core{
  }

  /**
   * Initialize the Mango environment. This should be called at the
   * beginning of every Mango simulation. Normally it populates the globals
   * GlobalFrame, Engine, Keyboard, Mouse, Camera and View, as well as
   * setting their properties. If setup_default_environment is false
   * these globals will not be instantiated, and it is the developer's
   * responsibility to do so.
   */
  void initialize(bool setup_default_environment = true);

  /**
   * Tears down the Mango environment. Normally, it destroys the
   * globals GlobalFrame, Engine, Keyboard, Mouse, Camera and View. If
   * teardown_default_environment is false these globals will not be
   * destroyed, and it is the developer's responsibility to make sure
   * no memory is leaked as a result.
   */
  void finalize(bool teardown_default_environment = true);
}

#endif // MANGO

