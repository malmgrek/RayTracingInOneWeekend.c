# ------------------------------
# CMake Build Configuration
#
# See README.md for instructions
# ------------------------------

cmake_minimum_required ( VERSION 3.1.0 )

project ( RTWeekendC
  VERSION 3.1.0
  LANGUAGES C
)

# Source
set ( SOURCE_CODE
  src/camera.c
  src/color.h
  src/color.c
  src/ray.h
  src/ray.c
  src/scatter.h
  src/scatter.c
  src/scene.h
  src/scene.c
  src/utils.h
  src/utils.c
  src/vec3.h
  src/main.c
)

# Executables
add_executable(inOneWeekendC ${SOURCE_CODE})

# Link libraries
target_link_libraries(inOneWeekendC m)

include_directories(src)
