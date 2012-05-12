cmake_minimum_required(VERSION 2.8)
project(Mango_geometry)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/../mango/include")

add_library(Mango_geometry "${PROJECT_SOURCE_DIR}/src/geometry.cpp")