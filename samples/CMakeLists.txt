cmake_minimum_required(VERSION 2.8)
project(Mango_samples)

file(GLOB samples *.cpp)

include_directories("${PROJECT_SOURCE_DIR}/../include")

foreach(filepath ${samples})
  get_filename_component(filename ${filepath} NAME)
  get_filename_component(name ${filepath} NAME_WE)
  add_executable(${name} ${filepath})
  target_link_libraries(${name} Mango_glut Mango_geometry Mango_core Mango_draw)
endforeach()

# dummy target to build all samples at once
add_custom_target(Mango_samples)
foreach(filepath ${samples})
  get_filename_component(name ${filepath} NAME_WE)
  add_dependencies(Mango_samples ${name})
endforeach()