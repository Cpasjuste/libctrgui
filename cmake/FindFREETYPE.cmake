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

set(FREETYPE_PATHS $ENV{FREETYPE} libfreetype ${DEVKITPRO}/portlibs/armv6k)

find_path(FREETYPE_INCLUDE_DIR freetype.h
        PATHS ${FREETYPE_PATHS}
        PATH_SUFFIXES include/freetype2)

find_library(FREETYPE_LIBRARY NAMES freetype libfreetype.a
        PATHS ${FREETYPE_PATHS}
        PATH_SUFFIXES lib)

set(FREETYPE_LIBRARIES ${FREETYPE_LIBRARY} )
set(FREETYPE_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBSF2D_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(FREETYPE  DEFAULT_MSG FREETYPE_LIBRARY FREETYPE_INCLUDE_DIR)

mark_as_advanced(FREETYPE_INCLUDE_DIR FREETYPE_LIBRARY )
if(FREETYPE_FOUND)
    set(FREETYPE ${FREETYPE_INCLUDE_DIR}/..)
    message(STATUS "setting FREETYPE to ${FREETYPE}")

    add_library(3ds::freetype STATIC IMPORTED GLOBAL)
    set_target_properties(3ds::freetype PROPERTIES
        IMPORTED_LOCATION "${FREETYPE_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${FREETYPE_INCLUDE_DIR}"
    )
endif()
