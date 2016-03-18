cmake_minimum_required(VERSION 2.8)
project(CtrGui)
enable_language(ASM)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DKA_SUGGESTED_C_FLAGS} -Wno-deprecated-declarations") # Use the devkitArm suggested flags. This is not mandatory.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -Wno-deprecated-declarations")

# Note that you must copy the cmake folder and the DevkitArm3DS.cmake file in this directory
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake) # Add the cmake folder to the modules paths, so that we can use the tools and find_package for ctrulib
include(Tools3DS) # Include all the macros and tools needed for 3ds development.

find_package(CTRULIB REQUIRED)
find_package(FREETYPE REQUIRED)
find_package(PNG REQUIRED)
find_package(ZLIB REQUIRED)

file(GLOB_RECURSE SOURCE_FILES
    external/sf2dlib/libsf2d/source/*
    external/sftdlib/libsftd/source/*
    external/sfillib/libsfil/source/*
    source/*
)

add_library(ctrgui ${SOURCE_FILES})
set_target_properties(ctrgui PROPERTIES COMPILE_FLAGS "-DCITRA")

target_include_directories(ctrgui PUBLIC
        external/sf2dlib/libsf2d/include
        external/sftdlib/libsftd/include
        external/sfillib/libsfil/include
)
target_embed_shader(ctrgui data/shader_vsh.vsh)
target_link_libraries(ctrgui 3ds::libpng 3ds::libz 3ds::freetype 3ds::ctrulib)

add_subdirectory (examples)
