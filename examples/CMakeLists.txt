cmake_minimum_required(VERSION 2.8)
project(CtrGui)
enable_language(ASM)

set(NETLOAD_IP "192.168.1.14")

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(APP_ICON ../res/icon.png)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DKA_SUGGESTED_C_FLAGS}") # Use the devkitArm suggested flags. This is not mandatory.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

# Note that you must copy the cmake folder and the DevkitArm3DS.cmake file in this directory
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake) # Add the cmake folder to the modules paths, so that we can use the tools and find_package for ctrulib
include(Tools3DS) # Include all the macros and tools needed for 3ds development.

# ELF
add_executable(Example main.cpp)
# LIBS
target_link_libraries(Example 3ds::libpng 3ds::libz 3ds::freetype 3ds::ctrulib ctrgui)
# 3DSX
add_3dsx_target(Example)
# 3DSLINK
add_netload_target(Example_3dslink Example)
# CIA
add_cia_target(Example res/app.rsf res/banner.png res/audio.wav)
# CITRA
add_citra_target(Example_Citra Example)
set_target_properties(Example_Citra PROPERTIES COMPILE_FLAGS "-DCITRA")


