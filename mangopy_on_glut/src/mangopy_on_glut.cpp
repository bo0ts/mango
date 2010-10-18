#include "mangopy_python.h"
#include "mango_on_glut.h"
#include "mangopy.h"

#include <iostream>

int main(int argc, char *argv[]){
  int return_val;

  MangoPy::initialize(argc, argv);
  Mango::OnGlut::initialize(argc, argv);
  
  return_val = 0;
  try{
    if (argc == 1){
      MangoPy::runScript("main.py", true);
    }
    else{
      MangoPy::runScript(argv[1], false);	
    }
    Mango::OnGlut::startWithoutCatchingErrors();
  }
  catch(Mango::Core::Error &e){
    e.trace();
    MangoPy::printPythonScriptStderr();
    std::cerr << std::endl << std::endl;
    return_val = 1;
  }
  catch(std::exception &e){
    e.what();
    return_val = 2;
  }
  
  MangoPy::finalize();  

  return return_val;
}
