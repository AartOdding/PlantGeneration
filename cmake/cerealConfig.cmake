
if(NOT TARGET cereal)

add_library(cereal INTERFACE)
add_library(cereal::cereal ALIAS cereal)

target_include_directories(cereal INTERFACE
    ${CMAKE_SOURCE_DIR}/dependencies/cereal/include
)

endif()
