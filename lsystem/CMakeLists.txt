cmake_minimum_required(VERSION 3.16)
project(lsystem LANGUAGES CXX VERSION 0.1)

# Public interface of the library, should only be hpp files in include folder.
set(PUBLIC_FILES
    include/LSystem/Instruction.hpp
    include/LSystem/LSystem.hpp
    include/LSystem/Rule.hpp
    include/LSystem/VertexBuffer.hpp
)

# Private files, can be cpp or hpp, should be in src folder
set(PRIVATE_FILES
    src/Instruction.cpp
    src/LSystem.cpp
)

source_group(Interface FILES ${PUBLIC_FILES})
source_group(Sources FILES ${PRIVATE_FILES})

add_library(${PROJECT_NAME} STATIC ${PUBLIC_FILES} ${PRIVATE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_INCLUDE_DIR})

target_compile_definitions(${PROJECT_NAME} PUBLIC GLM_ENABLE_EXPERIMENTAL)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
