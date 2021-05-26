# Locate Glm library (https://github.com/g-truc/glm)
# Glm is header-only.
#
# Defines
# GLM_FOUND - If Glm was found
# GLM_INCLUDE_DIR - Glm include dir
#
# First looks in standard installation locations.
# Then looks in the submodule location.
# GLM_INCLUDE_DIR set to provide manual location.

find_path(GLM_INCLUDE_DIR
  NAMES
    glm
  PATHS
    "${GLM_INCLUDE_DIR}"
    /usr/include
    dependencies/glm
)

# Handle error message if package not found and set GLM_FOUND
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Glm DEFAULT_MSG GLM_INCLUDE_DIR)