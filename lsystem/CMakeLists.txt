cmake_minimum_required(VERSION 3.16)
project(lsystem LANGUAGES CXX VERSION 0.1)

# Public interface of the library, should only be hpp files in include folder.
set(PUBLIC_FILES
    include/LSystem/Instruction.hpp
    include/LSystem/LSystem.hpp
    include/LSystem/Operation.hpp
    include/LSystem/OperationOwner.hpp
    include/LSystem/Parameter.hpp
    include/LSystem/ParameterOwner.hpp
    include/LSystem/VertexBuffer.hpp
    include/LSystem/Operations/ColoringOperation.hpp
    include/LSystem/Operations/ExtrudeOperation.hpp
    include/LSystem/Operations/FanOperation.hpp
    include/LSystem/Operations/ForkOperation.hpp
    include/LSystem/Operations/PhyllotaxisOperation.hpp
    include/LSystem/Parameters/ColorParameter.hpp
    include/LSystem/Parameters/FloatParameter.hpp
    include/LSystem/Parameters/IntParameter.hpp
)

# Private files, can be cpp or hpp, should be in src folder
set(PRIVATE_FILES
    src/LSystem.cpp
    src/Operation.cpp
    src/OperationOwner.cpp
    src/Parameter.cpp
    src/ParameterOwner.cpp
    src/Operations/ColoringOperation.cpp
    src/Operations/ExtrudeOperation.cpp
    src/Operations/FanOperation.cpp
    src/Operations/ForkOperation.cpp
    src/Operations/PhyllotaxisOperation.cpp
    src/Parameters/ColorParameter.cpp
    src/Parameters/FloatParameter.cpp
    src/Parameters/IntParameter.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX Interface FILES ${PUBLIC_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX Sources FILES ${PRIVATE_FILES})

add_library(${PROJECT_NAME} STATIC ${PUBLIC_FILES} ${PRIVATE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_INCLUDE_DIR})

target_compile_definitions(${PROJECT_NAME} PUBLIC GLM_ENABLE_EXPERIMENTAL)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
