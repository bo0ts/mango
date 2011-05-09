#include "core/error.h"
#include <string.h>
#include <stdio.h>

namespace Mango{
  namespace Core{				

    /**
     * Create an Error instance with given sourceObject,
     * originatingMethodName and error message. The strings passed in 
     * will be copied to member variables. 
     * 
     * @param sourceObject 
     *   a string representing the object in which
     *   the error originated. Can be NULL.
     *
     * @param originatingMethodName
     *   a string representing the method in which 
     *   the error originated. Can be NULL.
     *
     * @param m
     *   the error message. Can, but probably should not be, NULL.
     */
    Error::Error(const char *sourceObject, const char *originatingMethodName, const char * m){
      int fullLength = 0;
      int tmpLength = 0;
      msg = m;
		
      if (sourceObject != NULL){
	tmpLength = strlen(sourceObject);
	fullLength += tmpLength;
	origObjectType = new char[tmpLength];
	strcpy(origObjectType, sourceObject);
      }
      else{
	origObjectType = NULL;
      }
		
      if (originatingMethodName != NULL){
	tmpLength += strlen(originatingMethodName);
	fullLength += tmpLength;
	methodName = new char[tmpLength];
	strcpy(methodName, originatingMethodName);
      }
		
      fullLength += strlen(msg);
      fullLength += 5;
      fullMsg = new char[fullLength];
      if (sourceObject != NULL && originatingMethodName != NULL){
	sprintf(fullMsg, "%s.%s: %s", sourceObject, originatingMethodName, msg);
      }
      else if (sourceObject != NULL){
	sprintf(fullMsg, "%s: %s", sourceObject, msg);
      }
      else if (originatingMethodName != NULL){
	sprintf(fullMsg, "%s: %s", originatingMethodName, msg);
      }
      else{
	strcpy(fullMsg, msg);
      }
		
    }
	
    const char* Error::what() const throw(){
      return msg;
    }
		
    const char* Error::Message() const throw() {
      return msg;
    }
		
    const char* Error::FullMessage() const throw() {
      return fullMsg;
    }
		
    const char* Error::originatingObjectType() const throw(){
      return origObjectType;
    }
		
    const char* Error::originatingMethodName() const throw() {
      return methodName;
    }
		
    /**
     * Print a trace of the error that occurred. At the moment, this
     * will print one of 
     * "<error-type> in <orig-object>.<orig-method>: <error-msg>"
     * "<error-type> in object <orig-object>: <error-message>"
     * "<error-type> in <orig-method>: <error-message>"
     * "<error-type>: <error-message>"
     * depending on what error information is available.
     * 
     */
    void Error::trace() const throw(){
      std::cout << std::endl << objectType();
      if (origObjectType != NULL && methodName != NULL){
	std::cout << " in " << origObjectType << "." << methodName;
      }
      else if (origObjectType != NULL){
	std::cout << " in object " << origObjectType;
      }
      else if (methodName != NULL){
	std::cout << " in " << methodName;
      }
      std::cout << ":" << std::endl;
      std::cout << msg << std::endl;
    }
  } // Core
} // Mango
