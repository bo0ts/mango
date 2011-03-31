#include <iostream>
#include <exception>

#ifndef MANGO_ERROR
#define MANGO_ERROR 1

namespace Mango{
  namespace Core{
				
    class Error : public std::exception{
    public:
      Error(const char *origObjectType, const char *originatingMethodName, const char *m="");
      //~Error() throw();
		
      virtual const char *objectType() const{
	return "Error";
      }
		
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
				
		
    class ValueError : public Error{
    public:
    ValueError(const char *origObjectType, const char *originatingMethodName, const char *m=""): Error(origObjectType, originatingMethodName, m){
      }
		
      virtual const char *objectType() const{
	return "ValueError";
      }
    };
		
    class IndexError : public Error{
    public:
    IndexError(const char *origObjectType, const char *originatingMethodName, const char *m=""): Error(origObjectType, originatingMethodName, m){
      }
		
      virtual const char *objectType() const{
	return "IndexError";
      }
    };
	  
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
