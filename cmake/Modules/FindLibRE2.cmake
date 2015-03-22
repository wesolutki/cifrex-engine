set(re2_DEFINITIONS ${PC_LIBXML_CFLAGS_OTHER})

find_path(re2_INCLUDE_DIR re2/re2.h
          HINTS ${PC_re2_INCLUDEDIR} ${PC_re2_INCLUDE_DIRS}
          PATH_SUFFIXES re2)

find_library(re2_LIBRARY NAMES re2 libre2
             HINTS ${PC_re2_LIBDIR} ${PC_re2_LIBRARY_DIRS} )

set(re2_LIBRARIES ${re2_LIBRARY} )
set(re2_INCLUDE_DIRS ${re2_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set re2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(re2 DEFAULT_MSG
                                  re2_LIBRARY re2_INCLUDE_DIR)

mark_as_advanced(re2_INCLUDE_DIR re2_LIBRARY )
