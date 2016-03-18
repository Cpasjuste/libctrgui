# - Try to find sf2d
# Once done this will define
#  LIBSF2D_FOUND - System has sf2d
#  LIBSF2D_INCLUDE_DIRS - The sf2d include directories
#  LIBSF2D_LIBRARIES - The libraries needed to use sf2d
#
# It also adds an imported target named `3ds::sf2d`.
# Linking it is the same as target_link_libraries(target ${LIBSF2D_LIBRARIES}) and target_include_directories(target ${LIBSF2D_INCLUDE_DIRS})

# DevkitPro paths are broken on windows, so we have to fix those
macro(msys_to_cmake_path MsysPath ResultingPath)
    string(REGEX REPLACE "^/([a-zA-Z])/" "\\1:/" ${ResultingPath} "${MsysPath}")
endmacro()

if(NOT DEVKITPRO)
    msys_to_cmake_path("$ENV{DEVKITPRO}" DEVKITPRO)
endif()

set(ZLIB_PATHS $ENV{ZLIB} libz ${DEVKITPRO}/portlibs/armv6k)

find_path(ZLIB_INCLUDE_DIR zlib.h
        PATHS ${ZLIB_PATHS}
        PATH_SUFFIXES include)

find_library(ZLIB_LIBRARY NAMES z libz.a
        PATHS ${ZLIB_PATHS}
        PATH_SUFFIXES lib)

set(ZLIB_LIBRARIES ${ZLIB_LIBRARY} )
set(ZLIB_INCLUDE_DIRS ${ZLIB_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBSF2D_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(ZLIB  DEFAULT_MSG ZLIB_LIBRARY ZLIB_INCLUDE_DIR)

mark_as_advanced(ZLIB_INCLUDE_DIR ZLIB_LIBRARY )
if(ZLIB_FOUND)
    set(ZLIB ${ZLIB_INCLUDE_DIR}/..)
    message(STATUS "setting ZLIB to ${ZLIB}")

    add_library(3ds::libz STATIC IMPORTED GLOBAL)
    set_target_properties(3ds::libz PROPERTIES
        IMPORTED_LOCATION "${ZLIB_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${ZLIB_INCLUDE_DIR}"
    )
endif()
