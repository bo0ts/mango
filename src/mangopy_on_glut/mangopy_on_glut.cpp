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
#include <mango/mangopy/mangopy_python.h>
#include <mango/glut/mango_on_glut.h>
#include <mango/mangopy/mangopy.h>

#include <iostream>

void print_usage();
void print_help();
void print_version();

int main(int argc, char *argv[]){
  int return_val;
 
  // Py_SetPath(L"/usr/lib/python3.2");
  // Py_SetPythonHome(L"/usr/");
  // Py_SetProgramName(L"/usr/bin/python3.2");

  std::wcout << Py_GetPath() << std::endl;
  std::wcout << Py_GetPrefix() << std::endl;
  std::wcout << Py_GetExecPrefix() << std::endl;

  MangoPy::initialize(argc, argv);
  Mango::OnGlut::initialize(argc, argv);
 
  return_val = 0;
  try{
    if (argc == 1){
      print_usage();
      return_val = 3;
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
