
#-------------------------------------------------------------------------------------------------------------------
# Setup unit testing
#-------------------------------------------------------------------------------------------------------------------

#------------------------------------
# download doctests
#-----------------------------------
ExternalProject_Add(
    external_doctest
    PREFIX ${CMAKE_BINARY_DIR}/external_projects/doctest
    GIT_REPOSITORY https://github.com/onqtam/doctest.git
    TIMEOUT 10
    GIT_TAG ef9da5263ac0092ce5662ab6c94b0eaf47a6ce03
    #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

# Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(external_doctest source_dir)
set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE INTERNAL "Path to include folder for doctest")
MESSAGE(STATUS DOCTEST_INCLUDE_DIR ${DOCTEST_INCLUDE_DIR})
include_directories(${DOCTEST_INCLUDE_DIR})


# meta target for all to handle dependencies
add_custom_target(externl_headers_test)
add_dependencies(externl_headers_test
    externl_headers 
    external_doctest
)

#-------------------------------------------------------------------------------------------------------------------
# Add Unit Tests
#-------------------------------------------------------------------------------------------------------------------
file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM files "test_infusion_infusion")

# test executable
add_executable(test_nifty_infusion test_nifty_infusion.cpp ${files})

target_link_libraries(test_nifty_infusion   ${NIFTY_INFUSION_EXTERNALS_LIBRARIES})

# declare the executable as test
add_test(NAME test_nifty_infusion COMMAND test_nifty_infusion)

# add dependencies 
add_dependencies(test_nifty_infusion externl_headers_test)