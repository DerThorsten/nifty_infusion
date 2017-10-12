# Try to find the Google AD3 library and headers.
#  AD3_FOUND        - system has qpbo lib
#  AD3_INCLUDE_DIRS - the qpbo include directory
#  AD3_LIBRARIES    - libraries needed to use qpbo

find_path(AD3_INCLUDE_DIR
	ad3/GenericFactor.h

    PATHS  ENV C_INCLUDE_PATH
           ENV C_PLUS_INCLUDE_PATH
           ENV INCLUDE_PATH

    HINTS ENV C_INCLUDE_PATH
          ENV C_PLUS_INCLUDE_PATH
          ENV INCLUDE_PATH
)

find_library(AD3_LIBRARY
	NAMES ad3
	DOC "The qpbo library"
    PATHS ENV LIBRARY_PATH
          ENV LD_LIBRARY_PATH
)

set(AD3_INCLUDE_DIRS ${AD3_INCLUDE_DIR})
set(AD3_LIBRARIES    ${AD3_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(AD3
	FOUND_VAR AD3_FOUND
	REQUIRED_VARS AD3_INCLUDE_DIR AD3_LIBRARY AD3_LIBRARIES
)

mark_as_advanced(AD3_FOUND)
