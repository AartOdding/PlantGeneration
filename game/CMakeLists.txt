cmake_minimum_required(VERSION 3.16)
project(game LANGUAGES CXX)

set(SRC_FILES
  src/debug.cpp
  src/main.cpp
  src/target.cpp
  src/sphere_world.cpp
  src/player.cpp
)

set(HEADER_FILES
  src/debug.hpp
  src/types.hpp
  src/target.hpp
  src/sphere_world.hpp
  src/player.hpp
)

source_group(Sources FILES ${SRC_FILES} ${HEADER_FILES})

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE resources)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE lsystem)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_INCLUDE_DIR})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(${PROJECT_NAME} PRIVATE MB4_PREPROCESSOR_DEBUG)
endif()
