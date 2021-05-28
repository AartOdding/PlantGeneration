cmake_minimum_required(VERSION 3.16)
project(4mbjam LANGUAGES CXX)

# set location of module finding scrips
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(FetchContent)
include("${CMAKE_SOURCE_DIR}/cmake/CMakeRC.cmake")

set(SRC_FILES
  src/debug.cpp
  src/main.cpp
)

set(HEADER_FILES
  src/debug.hpp
  src/types.hpp
)

set(SHADER_FILES
  resources/shaders/test.frag
)

cmrc_add_resource_library(static-resources
  NAMESPACE resources
  WHENCE resources
  ${SHADER_FILES}
)

source_group(Sources FILES ${SRC_FILES} ${HEADER_FILES})
source_group(Shaders FILES ${SHADER_FILES})

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

add_subdirectory(Editor)
add_subdirectory(LSystem)

add_executable(4mbjam ${SRC_FILES} ${HEADER_FILES} ${SHADER_FILES})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(4mbjam PRIVATE MB4_PREPROCESSOR_DEBUG)
endif()

set_property(TARGET 4mbjam PROPERTY CXX_STANDARD 20)
target_link_libraries(4mbjam PRIVATE raylib)
target_link_libraries(4mbjam PRIVATE static-resources)
target_link_libraries(4mbjam PRIVATE imgui)
target_include_directories(4mbjam PUBLIC ${GLM_INCLUDE_DIR})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT 4mbjam)
