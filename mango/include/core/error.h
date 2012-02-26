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
#include <iostream>
#include <exception>

#ifndef MANGO_ERROR
#define MANGO_ERROR 1

namespace Mango{
  namespace Core{

    /**
     * The base class for all Mango errors. All objects should raise errors 
     * derived from this class unless they wish to completely bypass Mango's 
     * error catching mechanisms
    */
    class Error : public std::exception{
    public:
      Error(const char *origObjectType, const char *originatingMethodName, const char *m="");
      //~Error() throw();
		
      virtual const char *objectType() const{
	return "Error";
      }

      virtual void raise();

      const char* what() const throw();
      const char* Message() const throw();
      const char* FullMessage() const throw();
      const char* originatingObjectType() const throw();
      const char* originatingMethodName() const throw();		      
		
      virtual void trace() const throw();
		      
    protected:
      const char *msg;
      char *origObjectType, *methodName, *fullMsg;
    };
				
    /**
     * An error appropriate for situations in which a variable or
     * argument has an invalid value and execution cannot continue.
     */
    class ValueError : public Error{
    public:
    ValueError(const char *origObjectType, const char *originatingMethodName, const char *m=""): Error(origObjectType, originatingMethodName, m){
      }
		
      virtual const char *objectType() const{
	return "ValueError";
      }

      virtual void raise();
    };
		
    /**
     * An error appropriate for situations in which an index variable
     * has an invalid value and execution cannot continue.
     */
    class IndexError : public Error{
    public:
    IndexError(const char *origObjectType, const char *originatingMethodName, const char *m=""): Error(origObjectType, originatingMethodName, m){
      }
		
      virtual const char *objectType() const{
	return "IndexError";
      }
    };
	  
    /**
     * An error appropriate for situations in which a failure occurred
     * while setting up the Mango, or a more general, environment.
     */
    class EnvironmentError : public Error{
    public:
    EnvironmentError(const char *origObjectType, const char *originatingMethodName, const char *m=""): Error(origObjectType, originatingMethodName, m){
      }
		
      virtual const char *objectType() const{
	return "EnvironmentError";
      }
    };
		
  } // Core
} // Mango


#endif // MANGO_ERROR
