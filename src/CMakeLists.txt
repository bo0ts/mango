cmake_minimum_required(VERSION 2.8)
project(Mango_libs)

include_directories("${PROJECT_SOURCE_DIR}/../include")

file(GLOB Mango_core_src "${PROJECT_SOURCE_DIR}/core/*.cpp")
set(Mango_core_src "${PROJECT_SOURCE_DIR}/mango.cpp" ${Mango_core_src})
file(GLOB Mango_draw_src "${PROJECT_SOURCE_DIR}/draw/*.cpp")
file(GLOB Mango_geometry_src "${PROJECT_SOURCE_DIR}/geometry/*.cpp")
file(GLOB Mango_glut_src "${PROJECT_SOURCE_DIR}/geometry/*.cpp")

add_library(Mango ${Mango_core_src})
add_library(Mango_geometry ${Mango_geometry_src})
add_library(Mango_draw ${Mango_draw_src})
add_library(Mango_glut ${Mango_glut_src})
