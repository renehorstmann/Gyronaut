cmake_minimum_required(VERSION 3.0)
project(Gyronaut C)

set(CMAKE_C_STANDARD 11)

#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -march=native)  # march=native for best performance
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic -Wno-unused-function -Wno-missing-braces")

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)
file(GLOB SRCS
        "${PROJECT_SOURCE_DIR}/include/*"
        "${PROJECT_SOURCE_DIR}/src/*"
        )

add_executable(gyronaut ${SRCS})

# SDL
find_package(SDL2 REQUIRED)
target_link_libraries(gyronaut ${SDL2_LIBRARIES} m)

# Desktop or Mobile? -> GL or GLES?
find_library(GL_LIB GL)
if (GL_LIB)
    message("GL found: Desktop mode")
    target_link_libraries(gyronaut ${GL_LIB})
    add_compile_definitions(GYRONAUT_OPENGL_MAJOR_VERSION=3)
    add_compile_definitions(GYRONAUT_OPENGL_MINOR_VERSION=0)
else ()
    message("GL not found: Mobile mode")
    add_compile_definitions(GYRONAUT_GLES)
    add_compile_definitions(GYRONAUT_OPENGL_MAJOR_VERSION=3)
    add_compile_definitions(GYRONAUT_OPENGL_MINOR_VERSION=0)
endif ()
