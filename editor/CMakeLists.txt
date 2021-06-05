cmake_minimum_required(VERSION 3.16)
project(editor LANGUAGES CXX)

# set location of module finding scrips
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(SRC_FILES
  src/main.cpp
)

set(HEADER_FILES
  src/Tree.hpp
  src/TreeEditWindow.hpp
  src/Trees.hpp
)

source_group(Sources FILES ${SRC_FILES} ${HEADER_FILES})

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_link_libraries(${PROJECT_NAME} PRIVATE lsystem)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE resources)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_INCLUDE_DIR})
