# Try to find the Google QPBO library and headers.
#  QPBO_FOUND        - system has qpbo lib
#  QPBO_INCLUDE_DIRS - the qpbo include directory
#  QPBO_LIBRARIES    - libraries needed to use qpbo

find_path(QPBO_INCLUDE_DIR
	qpbo/QPBO.h

    PATHS  ENV C_INCLUDE_PATH
           ENV C_PLUS_INCLUDE_PATH
           ENV INCLUDE_PATH

    HINTS ENV C_INCLUDE_PATH
          ENV C_PLUS_INCLUDE_PATH
          ENV INCLUDE_PATH
)

find_library(QPBO_LIBRARY
	NAMES qpbo
	DOC "The qpbo library"
    PATHS ENV LIBRARY_PATH
          ENV LD_LIBRARY_PATH
)

set(QPBO_INCLUDE_DIRS ${QPBO_INCLUDE_DIR})
set(QPBO_LIBRARIES    ${QPBO_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QPBO
	FOUND_VAR QPBO_FOUND
	REQUIRED_VARS QPBO_INCLUDE_DIR QPBO_LIBRARY QPBO_LIBRARIES
)

mark_as_advanced(QPBO_FOUND)
