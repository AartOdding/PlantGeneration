cmake_minimum_required(VERSION 3.16)
project(4mbjam LANGUAGES CXX)

# set location of module finding scrips
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_PREFIX_PATH})
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(FetchContent)
include("${CMAKE_SOURCE_DIR}/cmake/CMakeRC.cmake")

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
  GIT_REPOSITORY https://github.com/AartOdding/raylib.git
  GIT_TAG        4mbjam
)
FetchContent_MakeAvailable(raylib)

# include imgui after raylib! 
include("${CMAKE_SOURCE_DIR}/cmake/imgui.cmake")

find_package(Glm REQUIRED)

add_subdirectory(editor)
add_subdirectory(game)
add_subdirectory(lsystem)
add_subdirectory(resources)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT game)
set_target_properties(glfw PROPERTIES FOLDER dependencies)
set_target_properties(glfw_objlib PROPERTIES FOLDER dependencies)
set_target_properties(raylib PROPERTIES FOLDER dependencies)
set_target_properties(imgui PROPERTIES FOLDER dependencies)
