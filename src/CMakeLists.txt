cmake_minimum_required(VERSION 2.8)
project(Mango_libs)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})

include_directories("${PROJECT_SOURCE_DIR}/../include")

file(GLOB Mango_core_src "${PROJECT_SOURCE_DIR}/core/*.cpp")
set(Mango_core_src "${PROJECT_SOURCE_DIR}/mango.cpp" ${Mango_core_src})
file(GLOB Mango_draw_src "${PROJECT_SOURCE_DIR}/draw/*.cpp")
file(GLOB Mango_geometry_src "${PROJECT_SOURCE_DIR}/geometry/*.cpp")
file(GLOB Mango_glut_src "${PROJECT_SOURCE_DIR}/glut/*.cpp")

add_library(Mango_core ${Mango_core_src})
target_link_libraries(Mango_core ${OPENGL_LIBRARIES})

add_library(Mango_geometry ${Mango_geometry_src})
target_link_libraries(Mango_geometry ${OPENGL_LIBRARIES})

add_library(Mango_draw ${Mango_draw_src})
target_link_libraries(Mango_draw ${OPENGL_LIBRARIES})

## Mango_on_GLUT is optional

find_package(GLUT)
if(${GLUT_FOUND})
  include_directories(${GLUT_INCLUDE_DIR})
  add_library(Mango_glut ${Mango_glut_src})
  target_link_libraries(Mango_glut ${GLUT_LIBRARIES})
else()
  message("GLUT not found, not building Mango_glut")
endif()



## Build the Python Bindings
find_package(PythonLibs 3.2)

if(${PYTHONLIBS_FOUND})
  include_directories(${PYTHON_INCLUDE_PATH})

  file(GLOB Mango_py_src "${PROJECT_SOURCE_DIR}/mangopy/*.cpp")
  add_library(Mango_py ${Mango_py_src})
  target_link_libraries(Mango_py ${PYTHON_LIBRARIES} Mango_core Mango_draw)

  file(GLOB Mango_pygeometry_src "${PROJECT_SOURCE_DIR}/pygeometry/*.cpp")
  add_library(Mango_pygeometry ${Mango_pygeometry_src})
  target_link_libraries(Mango_pygeometry ${PYTHON_LIBRARIES} Mango_core Mango_geometry)

if(${GLUT_FOUND})
  include_directories(${GLUT_INCLUDE_DIR})
  add_executable(mango "${PROJECT_SOURCE_DIR}/mangopy_on_glut/mangopy_on_glut.cpp")
  target_link_libraries(mango ${GLUT_LIBRARIES} Mango_core Mango_draw Mango_glut Mango_py)
else()
  message("GLUT not found, not building the mango executable")
endif()

else()
  message("Not building the Python Bindings. No Python installation has been found.")
endif()