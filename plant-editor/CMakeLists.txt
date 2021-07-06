cmake_minimum_required(VERSION 3.16)
project(PlantEditor LANGUAGES CXX VERSION 0.1)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
    src/main.cpp
    src/Widgets/MainWindow.cpp
    src/Widgets/MainWindow.hpp
    src/Widgets/NodeEditorWidget.cpp
    src/Widgets/NodeEditorWidget.hpp
    src/Controllers/ModelController.cpp
    src/Controllers/ModelController.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX Sources FILES ${SOURCES})
