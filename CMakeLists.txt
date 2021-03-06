cmake_minimum_required(VERSION 3.0)
project(Gyronaut C)

set(CMAKE_C_STANDARD 11)

#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -march=native)  # march=native for best performance
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wno-long-long -Wno-unused-function -Wno-unused-variable -Wno-missing-braces")

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)
file(GLOB SRCS
        "${PROJECT_SOURCE_DIR}/include/*"
        "${PROJECT_SOURCE_DIR}/src/*"
        "${PROJECT_SOURCE_DIR}/src/e/*"
        "${PROJECT_SOURCE_DIR}/src/r/*"
        "${PROJECT_SOURCE_DIR}/src/u/*"
        "${PROJECT_SOURCE_DIR}/src/p/*"
        )

add_executable(gyronaut ${SRCS})

# Desktop or Mobile? -> GL or GLES?
find_library(GL_LIB GL)
find_library(GLES_LIB GLESv3)
if (GL_LIB)
    message("GL found: Desktop mode")
    target_link_libraries(gyronaut ${GL_LIB})
elseif (GLES_LIB)
    message("GLES found: Mobile mode")
    add_compile_definitions(GLES)
    target_link_libraries(gyronaut ${GLES_LIB})
else ()
    message(FATAL_ERROR "Neither GL nor GLESv3 found, exiting CMake")
endif ()

# SDL
find_package(SDL2 REQUIRED)
if (GL_LIB)
    find_library(SDL2_IMAGE_LIBRARIES SDL2_image)
    find_library(SDL2_TTF_LIBRARIES SDL2_ttf)
else ()
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
endif ()
include_directories(${SDL2_INCLUDE_DIRS})
message("include dir:" ${SDL2_INCLUDE_DIRS})
target_link_libraries(gyronaut m
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        )

# res
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})