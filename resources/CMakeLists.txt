cmake_minimum_required(VERSION 3.16)
project(resources LANGUAGES CXX VERSION 0.1)


set(SHADER_FILES
  shaders/test.frag
)

source_group(Shaders FILES ${SHADER_FILES})


cmrc_add_resource_library(${PROJECT_NAME}
  NAMESPACE ${PROJECT_NAME}
  ${SHADER_FILES}
  Plant1.plant
)

target_sources(${PROJECT_NAME} PUBLIC ${SHADER_FILES})
