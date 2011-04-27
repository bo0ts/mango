#include "mangopy_python.h"
#include "mango_on_glut.h"
#include "mangopy.h"

#include <iostream>

void print_usage();
void print_help();
void print_version();

int main(int argc, char *argv[]){
  int return_val;

  MangoPy::initialize(argc, argv);
  Mango::OnGlut::initialize(argc, argv);
  
  return_val = 0;
  try{
    if (argc == 1){
      print_usage();
      return_val = 3;
      //MangoPy::runScript("main.py", true);
    }
    else{
      char *show_version = MangoPy::check_cmd_op_presence(argv, argv+argc, "-v");
      char *show_help = MangoPy::check_cmd_op_presence(argv, argv+argc, "-h");
      if (show_version){
	print_version();
	return_val = 3;
      }
      else if (show_help){
	print_help();
	return_val = 3;
      }
      else{
	MangoPy::runScript(argv[argc - 1], false);		
      }
    }

    if (return_val == 0){
      Mango::OnGlut::startWithoutCatchingErrors();
    }
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

void print_usage(){
  std::cout << "Usage:" << std::endl << "  mango [options] path/to/script.py" << std::endl;  
}

void print_version(){
  std::cout << "Mango v" << Mango::full_version_string() << std::endl; 
}

void print_help(){
  print_version();
  print_usage();
  std::cout << std::endl << "Options: " << std::endl;
  std::cout << "  -h\tthis help screen" << std::endl;
  std::cout << "  -v\tprint version" << std::endl;
  std::cout << std::endl;
}
