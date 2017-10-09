cmake_minimum_required(VERSION 3.1)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

SET(PROJECT_NAME "nifty_infusion")
project(nifty_infusion)




include(CheckCXXCompilerFlag)


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
# QPBO
#---------------------------------------------------
find_package(QPBO REQUIRED)
include_directories(${QPBO_INCLUDE_DIRS})

#---------------------------------------------------
# Boost
#---------------------------------------------------
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})




#---------------------------------------------------------
# external projects which need to be in the `include tree`
#---------------------------------------------------------



# #---------------------------------------------------
# # GSL: Guideline Support Library  
# #---------------------------------------------------
# ExternalProject_Add(
#     external_gsl
#     PREFIX ${CMAKE_BINARY_DIR}/external_projects/GSL
#     GIT_REPOSITORY https://github.com/Microsoft/GSL
#     GIT_TAG b01450878b39307df9abb702f02ce8c1d6c9ee30
#     TIMEOUT 5
#     #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND ""
#     INSTALL_COMMAND ""
#     LOG_DOWNLOAD ON
# )
# # Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
# ExternalProject_Get_Property(external_gsl source_dir)
# set(GSL_INCLUDE_DIR ${source_dir}/include/ CACHE INTERNAL "Path to include folder for GSL")
# include_directories(${GSL_INCLUDE_DIR})



# #---------------------------------------------------
# # xtensor 
# #---------------------------------------------------
# ExternalProject_Add(
#     external_xtensor
#     PREFIX ${CMAKE_BINARY_DIR}/external_projects/xtensor
#     GIT_REPOSITORY https://github.com/QuantStack/xtensor
#     GIT_TAG 0.10.7
#     TIMEOUT 5
#     #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND ""
#     INSTALL_COMMAND ""
#     LOG_DOWNLOAD ON
# )
# # Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
# ExternalProject_Get_Property(external_xtensor source_dir)
# set(XTENSOR_INCLUDE_DIR ${source_dir}/include/ CACHE INTERNAL "Path to include folder for xtensor")
# include_directories(${XTENSOR_INCLUDE_DIR})



#---------------------------------------------------
# nifty_tools 
#---------------------------------------------------
ExternalProject_Add(
    external_nifty_tools
    PREFIX ${CMAKE_BINARY_DIR}/external_projects/nifty_tools
    GIT_REPOSITORY https://github.com/DerThorsten/nifty_tools
    GIT_TAG "0.2.1"
    TIMEOUT 5
    #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)
# Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(external_nifty_tools source_dir)
set(NIFTY_TOOLS_INCLUDE_DIR ${source_dir}/include/ CACHE INTERNAL "Path to include folder for nifty_tools")
include_directories(${NIFTY_TOOLS_INCLUDE_DIR})



#---------------------------------------------------
# nifty_meta
#---------------------------------------------------
ExternalProject_Add(
    external_nifty_meta
    PREFIX ${CMAKE_BINARY_DIR}/external_projects/nifty_meta
    GIT_REPOSITORY https://github.com/DerThorsten/nifty_meta
    GIT_TAG "0.3.0"
    TIMEOUT 5
    #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)
# Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(external_nifty_meta source_dir)
set(NIFTY_META_INCLUDE_DIR ${source_dir}/include/ CACHE INTERNAL "Path to include folder for nifty_meta")
include_directories(${NIFTY_META_INCLUDE_DIR})


# #---------------------------------------------------
# # qpbo 
# #---------------------------------------------------
# ExternalProject_Add(
#     external_qpbo
#     PREFIX ${CMAKE_BINARY_DIR}/external_projects/qpbo
#     GIT_REPOSITORY https://github.com/DerThorsten/qpbo
#     GIT_TAG "0.2.2"
#     TIMEOUT 5
#     #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND ""
#     INSTALL_COMMAND ""
#     LOG_DOWNLOAD ON
# )
# # Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
# ExternalProject_Get_Property(external_qpbo source_dir)
# set(QPBO_ROOT_DIR ${source_dir}/ CACHE INTERNAL "Path to include folder for qpbo")
# include_directories(${QPBO_ROOT_DIR})

# #---------------------------------------------------
# # trws 
# #---------------------------------------------------
# ExternalProject_Add(
#     external_trws
#     PREFIX ${CMAKE_BINARY_DIR}/external_projects/trws
#     GIT_REPOSITORY https://github.com/DerThorsten/PyTrw
#     GIT_TAG 0.1.0
#     TIMEOUT 5
#     #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND ""
#     INSTALL_COMMAND ""
#     LOG_DOWNLOAD ON
# )
# # Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
# ExternalProject_Get_Property(external_trws source_dir)
# set(TRWS_ROOT_DIR ${source_dir}/trw/src/core CACHE INTERNAL "Path to include folder for trws")
# include_directories(${TRWS_ROOT_DIR})


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
add_dependencies(externl_headers
    #external_boost_header_only
    #external_gsl 
    #external_xtensor
    external_nifty_tools
    external_nifty_meta

)







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

