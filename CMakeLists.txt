cmake_minimum_required(VERSION 3.16)
project(4mbjam LANGUAGES CXX)

include(FetchContent)
include("${CMAKE_SOURCE_DIR}/cmake/CMakeRC.cmake")

set(SHADER_FILES
  resources/shaders/test.frag
)

cmrc_add_resource_library(static-resources
  NAMESPACE resources
  WHENCE resources
  ${SHADER_FILES}
)

source_group(Shaders FILES resources/shaders/test.frag)

# provide default build type release
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# prefer new opengl libraries
set(OpenGL_GL_PREFERENCE GLVND)

# get raylib 
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        3.7.0
)
FetchContent_MakeAvailable(raylib)

add_executable(4mbjam src/main.cpp ${SHADER_FILES})
target_link_libraries(4mbjam PRIVATE raylib)
target_link_libraries(4mbjam PRIVATE static-resources)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT 4mbjam)
