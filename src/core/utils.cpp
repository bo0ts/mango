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
#include <mango/core/utils.h>

namespace Mango{
  namespace Core{
    int elapsed_time_in_milliseconds(){
#ifdef WINDOWS
#error elapsed_time_in_milliseconds not implemented
#else
      struct timeval current_time;
      gettimeofday(&current_time, NULL);
      return  ((current_time.tv_sec) * 1000 + current_time.tv_usec/1000.0) + 0.5;
#endif
    }

    void seconds_sleep(float seconds){
#ifdef WINDOWS
      Sleep(seconds);
#error millisecond_sleep implementation needs to be verified
#else
      usleep((int)(seconds * 1000000.0));
#endif
    }
  }
}
