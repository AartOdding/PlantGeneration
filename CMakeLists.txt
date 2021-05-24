cmake_minimum_required(VERSION 3.16)
project(4mbjam LANGUAGES CXX)

include(FetchContent)

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

add_executable(4mbjam src/main.cpp)
target_link_libraries(4mbjam raylib)