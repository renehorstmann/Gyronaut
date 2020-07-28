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
find_library(SDL2_IMAGE_LIB SDL2_image)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(gyronaut m ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIB})

# Desktop or Mobile? -> GL or GLES?
find_library(GL_LIB GL)
find_library(GLES_LIB GLESv3)
if (GL_LIB)
    message("GL found: Desktop mode")
    target_link_libraries(gyronaut ${GL_LIB})
elseif (GLES_LIB)
    message("GLES found: Mobile mode")
    add_compile_definitions(G_GLES)
    target_link_libraries(gyronaut ${GLES_LIB})
else()
    message( FATAL_ERROR "Neither GL nor GLESv3 found, exiting CMake")
endif ()

# res
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})