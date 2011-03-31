#include "core/error.h"
#include <string.h>
#include <stdio.h>

namespace Mango{
	namespace Core{				
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
		
		/*
		Error::~Error() throw (){
		    if (origObjectType != NULL){
		        delete origObjectType;
		    }
		    if (methodName != NULL){
		        delete methodName;
		    }
		    if (fullMsg != NULL){
		        delete fullMsg;
		    }
		}*/
		
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
