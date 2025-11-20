cmake_minimum_required(VERSION 3.5)

project(GLEngine)

set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE GLEngineSources CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(GLEngine
  "${GLEngineSources}"
)

find_package(glfw3 3.4 REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(GLEngine PRIVATE
  glfw
  GLEW::GLEW
)

target_compile_features(GLEngine PRIVATE
  cxx_std_17
)