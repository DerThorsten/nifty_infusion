cmake_minimum_required(VERSION 3.1)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)


project(NIFTY_INFUSION)
set(${PROJECT_NAME}_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

#-------------------------------------------------------------------------------------------------------------------
# Version
#-------------------------------------------------------------------------------------------------------------------
# as seen in the github.com/QuantStack/xtensor
file(STRINGS "${${PROJECT_NAME}_INCLUDE_DIR}/nifty/infusion/infusion_config.hpp" ${PROJECT_NAME}_version_defines
     REGEX "#define ${PROJECT_NAME}_VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${${PROJECT_NAME}_version_defines})
    if(ver MATCHES "#define ${PROJECT_NAME}_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(${PROJECT_NAME}_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(${PROJECT_NAME}_VERSION 
    ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH})
message(STATUS "${PROJECT_NAME} v${${PROJECT_NAME}_VERSION}")


SET(BUILD_TESTS    ON CACHE BOOL "Build the test suite ?"   FORCE)
SET(BUILD_DOCS     ON CACHE BOOL "Build the documentation?" FORCE)
SET(BUILD_EXAMPLES ON CACHE BOOL "Build the examples?"      FORCE)








#-------------------------------------------------------------------------------------------------------------------
# cmake packages
#-------------------------------------------------------------------------------------------------------------------
include(ExternalProject)

#-------------------------------------------------------------------------------------------------------------------
# check for c++ 14 support
#-------------------------------------------------------------------------------------------------------------------
include(CheckCXXCompilerFlag)
# FIXME c++14 checks are broken???
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    CHECK_CXX_COMPILER_FLAG("-std=c++14" HAS_CPP14_FLAG)
    #CHECK_CXX_COMPILER_FLAG("-std=c++11" HAS_CPP11_FLAG)
    if (HAS_CPP14_FLAG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    else()
        message(FATAL_ERROR "Unsupported compiler -- multi-array  requires C++14 support!")
    endif()
endif()


if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

#-------------------------------------------------------------------------------------------------------------------
# threading package
#-------------------------------------------------------------------------------------------------------------------
find_package(Threads REQUIRED)

#-------------------------------------------------------------------------------------------------------------------
# include include files
#-------------------------------------------------------------------------------------------------------------------
file(GLOB_RECURSE headers include/*.hxx)
include_directories(include)


#---------------------------------------------------
# NIFTY_META
#---------------------------------------------------
find_package(NIFTY_META REQUIRED)
include_directories(${NIFTY_META_INCLUDE_DIRS})


#---------------------------------------------------
# NIFTY_TOOLS
#---------------------------------------------------
find_package(NIFTY_TOOLS REQUIRED)
include_directories(${NIFTY_TOOLS_INCLUDE_DIRS})


#---------------------------------------------------
# QPBO
#---------------------------------------------------
find_package(QPBO REQUIRED)
include_directories(${QPBO_INCLUDE_DIRS})

#---------------------------------------------------
# AD3
#---------------------------------------------------
find_package(AD3 REQUIRED)
include_directories(${AD3_INCLUDE_DIRS})




if(FALSE)

    #---------------------------------------------------
    # ad3 
    #---------------------------------------------------
    ExternalProject_Add(
        external_ad3
        PREFIX ${CMAKE_BINARY_DIR}/external_projects/ad3
        GIT_REPOSITORY https://github.com/andre-martins/AD3
        GIT_TAG 2.1
        TIMEOUT 5
        #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
    )
    # Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
    ExternalProject_Get_Property(external_ad3 source_dir)
    set(AD3_INCLUDE_DIR ${source_dir}/include/ CACHE INTERNAL "Path to include folder for ad3")
    include_directories(${AD3_INCLUDE_DIR})


    #---------------------------------------------------
    # maxflow 
    #---------------------------------------------------
    ExternalProject_Add(
        external_maxflow
        PREFIX ${CMAKE_BINARY_DIR}/external_projects/maxflow
        GIT_REPOSITORY https://github.com/DerThorsten/maxflow
        GIT_TAG 0.1.0
        TIMEOUT 5
        #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
    )
    # Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
    ExternalProject_Get_Property(external_maxflow source_dir)
    set(MAXFLOW_INCLUDE_DIR ${source_dir}/include/ CACHE INTERNAL "Path to include folder for maxflow")
    include_directories(${MAXFLOW_INCLUDE_DIR})




    #---------------------------------------------------
    # ibfs 
    #---------------------------------------------------
    ExternalProject_Add(
        external_ibfs
        PREFIX ${CMAKE_BINARY_DIR}/external_projects/ibfs
        GIT_REPOSITORY https://github.com/DerThorsten/graphCutMex_IBFS
        GIT_TAG 0.1.0
        TIMEOUT 5
        #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
    )
    # Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
    ExternalProject_Get_Property(external_ibfs source_dir)
    set(IBFS_INCLUDE_DIR ${source_dir}/include/ CACHE INTERNAL "Path to include folder for ibfs")
    include_directories(${IBFS_INCLUDE_DIR})


    #---------------------------------------------------
    # libdai 
    #---------------------------------------------------
    ExternalProject_Add(
        external_libdai
        PREFIX ${CMAKE_BINARY_DIR}/external_projects/libdai
        GIT_REPOSITORY https://github.com/DerThorsten/libDAI-1
        GIT_TAG 0.1.0
        TIMEOUT 5
        #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
    )
    # Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
    ExternalProject_Get_Property(external_libdai source_dir)
    set(LIBDAI_INCLUDE_DIR ${source_dir}/include/ CACHE INTERNAL "Path to include folder for xtensor")
    include_directories(${LIBDAI_INCLUDE_DIR})

endif()



# meta target for all to handle dependencies
add_custom_target(externl_headers)
# add_dependencies(externl_headers
#     #external_boost_header_only
#     #external_gsl 
#     #external_xtensor
#     #external_nifty_tools
#     #external_nifty_meta

# )







#-------------------------------------------------------------------------------------------------------------------
# enable `make test` in root dir
#-------------------------------------------------------------------------------------------------------------------
if(BUILD_TESTS)
    enable_testing()
endif()

#------------------------------------------------------------------------------------------------------------------
# src folder
#-------------------------------------------------------------------------------------------------------------------
add_subdirectory(src)





#------------------------------------------------------------------------------------------------------------------
# install
#-------------------------------------------------------------------------------------------------------------------
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)


install(DIRECTORY  ${${PROJECT_NAME}_INCLUDE_DIR}/nifty/infusion
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nifty)


set(${PROJECT_NAME}_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE
    STRING "install path for ${PROJECT_NAME}Config.cmake")

configure_package_config_file(${PROJECT_NAME}Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${${PROJECT_NAME}_CMAKECONFIG_INSTALL_DIR})


write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${${PROJECT_NAME}_VERSION}
                                 COMPATIBILITY AnyNewerVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${${PROJECT_NAME}_CMAKECONFIG_INSTALL_DIR})
