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

set(PNG_PATHS $ENV{PNG} libpng ${DEVKITPRO}/portlibs/armv6k)

find_path(PNG_INCLUDE_DIR png.h
        PATHS ${PNG_PATHS}
        PATH_SUFFIXES include)

find_library(PNG_LIBRARY NAMES png libpng.a
        PATHS ${PNG_PATHS}
        PATH_SUFFIXES lib)

set(PNG_LIBRARIES ${PNG_LIBRARY} )
set(PNG_INCLUDE_DIRS ${PNG_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBSF2D_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(PNG  DEFAULT_MSG PNG_LIBRARY PNG_INCLUDE_DIR)

mark_as_advanced(PNG_INCLUDE_DIR PNG_LIBRARY )
if(PNG_FOUND)
    set(PNG ${PNG_INCLUDE_DIR}/..)
    message(STATUS "setting PNG to ${PNG}")

    add_library(3ds::libpng STATIC IMPORTED GLOBAL)
    set_target_properties(3ds::libpng PROPERTIES
        IMPORTED_LOCATION "${PNG_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${PNG_INCLUDE_DIR}"
    )
endif()
