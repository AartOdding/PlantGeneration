cmake_minimum_required(VERSION 3.16)
project(lsystem LANGUAGES CXX VERSION 0.1)

find_package(cereal)

# Public interface of the library, should only be hpp files in include folder.
set(PUBLIC_FILES
    include/LSystem/Connection.hpp
    include/LSystem/Forward.hpp
    include/LSystem/Instruction.hpp
    include/LSystem/InstructionPool.hpp
    include/LSystem/LSystem.hpp
    include/LSystem/Operation.hpp
    include/LSystem/Parameter.hpp
    include/LSystem/Plant.hpp
    include/LSystem/VertexBuffer.hpp

    include/LSystem/Operations/ColoringOperation.hpp
    include/LSystem/Operations/ExtrudeOperation.hpp
    include/LSystem/Operations/FanOperation.hpp
    include/LSystem/Operations/ForkOperation.hpp
    include/LSystem/Operations/LoopOperation.hpp
    include/LSystem/Operations/PhyllotaxisOperation.hpp
    include/LSystem/Operations/RadiusOperation.hpp
    include/LSystem/Operations/RandomColorOperation.hpp
    include/LSystem/Operations/RandomLengthOperation.hpp
    include/LSystem/Operations/Registration.hpp
    include/LSystem/Operations/ScaleOperation.hpp
    include/LSystem/Operations/StartOperation.hpp

    include/LSystem/Parameters/BoolParameter.hpp
    include/LSystem/Parameters/ColorParameter.hpp
    include/LSystem/Parameters/FloatParameter.hpp
    include/LSystem/Parameters/IntParameter.hpp
    include/LSystem/Parameters/Registration.hpp

    include/LSystem/Utils/Hash.hpp
    include/LSystem/Utils/Identifier.hpp
    include/LSystem/Utils/MapRange.hpp
    include/LSystem/Utils/NoCopy.hpp
    include/LSystem/Utils/NoMove.hpp
    include/LSystem/Utils/Serialization.hpp
)

# Private files, can be cpp or hpp, should be in src folder
set(PRIVATE_FILES
    src/LSystem.cpp
    src/Operation.cpp
    src/Parameter.cpp
    src/Plant.cpp

    src/Operations/ColoringOperation.cpp
    src/Operations/ExtrudeOperation.cpp
    src/Operations/FanOperation.cpp
    src/Operations/ForkOperation.cpp
    src/Operations/LoopOperation.cpp
    src/Operations/PhyllotaxisOperation.cpp
    src/Operations/RadiusOperation.cpp
    src/Operations/RandomColorOperation.cpp
    src/Operations/RandomLengthOperation.cpp
    src/Operations/ScaleOperation.cpp
    src/Operations/StartOperation.cpp

    src/Parameters/BoolParameter.cpp
    src/Parameters/ColorParameter.cpp
    src/Parameters/FloatParameter.cpp
    src/Parameters/IntParameter.cpp

    src/Utils/Identifier.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX Interface FILES ${PUBLIC_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX Sources FILES ${PRIVATE_FILES})

add_library(${PROJECT_NAME} STATIC ${PUBLIC_FILES} ${PRIVATE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC cereal)

target_compile_definitions(${PROJECT_NAME} PUBLIC GLM_ENABLE_EXPERIMENTAL)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
