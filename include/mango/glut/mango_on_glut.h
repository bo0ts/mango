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

#ifndef MANGO_ON_GLUT_H
#define MANGO_ON_GLUT_H

#include <mango/mango.h>
#include <mango/glut/mango_glut.h>


namespace Mango{
  namespace OnGlut{
    /**
     * Initialize the MangoOnGlut environment. This creates a window
     * using GLUT and initializes the OpenGL state machine. argc and
     * argv are used to initialize GLUT.
     */
    void initialize(int argc, char* argv[]);

    /**
     * Start the GLUT main loop. Any errors derived from
     * Mango::Core::Error that are raised during the main loop will be
     * caught, printed out and then program execution will terminate.
     */
    void start();

    /**
     * Start the GLUT main loop. No error catching is done.
     */
    void startWithoutCatchingErrors();
  }
}

#endif /* MANGO_ON_GLUT_H */

