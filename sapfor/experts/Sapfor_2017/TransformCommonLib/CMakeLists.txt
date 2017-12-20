cmake_minimum_required(VERSION 2.8)

set(project TransformCommonLib)
if (TARGET ${project})
    return()
endif ()
project(${project})
message("processing ${project}")
#include(CTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions("-D SYS5")
add_definitions("-D YYDEBUG")

#set(CMAKE_CXX_STANDARD 11)

set(PATH_TO_REPO_ROOT ../../../..)
set(FDVM_INCLUDES ${PATH_TO_REPO_ROOT}/dvm/fdvm/trunk/include)
set(FDVM_SAGE_LIB_INCLUDES ${PATH_TO_REPO_ROOT}/dvm/fdvm/trunk/Sage/lib/include)
set(FDVM_SAGE_H_INCLUDES ${PATH_TO_REPO_ROOT}/dvm/fdvm/trunk/Sage/h/)
set(FTRANSFORM_BASE ${PATH_TO_REPO_ROOT}/sapfor/transformers/ftransform/trunk/)
set(libdb_sources ${PATH_TO_REPO_ROOT}/dvm/fdvm/trunk/Sage/lib/oldsrc)
set(sage_sources ${PATH_TO_REPO_ROOT}/dvm/fdvm/trunk/Sage/lib/newsrc)
set(sagepp_sources ${PATH_TO_REPO_ROOT}/dvm/fdvm/trunk/Sage/Sage++)
set(parser_sources ${PATH_TO_REPO_ROOT}/dvm/fdvm/trunk/parser)

include_directories(_src)
#Sage lib includes
include_directories(${FDVM_INCLUDES})
include_directories(${FDVM_SAGE_LIB_INCLUDES})
include_directories(${FDVM_SAGE_H_INCLUDES})
#Ftransform includes
include_directories(${FTRANSFORM_BASE}/CommonLib/include)
include_directories(${FTRANSFORM_BASE}/SageTransformLib/include)
include_directories(${FTRANSFORM_BASE}/SageUtils/include)

set(SOURCE_EXE
        ${FTRANSFORM_BASE}/CommonLib/src/Log.cpp
        ${FTRANSFORM_BASE}/CommonLib/src/SageTransformException.cpp
        ${FTRANSFORM_BASE}/CommonLib/src/SignalHandling.cpp
        ${FTRANSFORM_BASE}/CommonLib/src/Stacktrace.cpp
        ${FTRANSFORM_BASE}/CommonLib/src/StringUtils.cpp)


add_definitions("-D __SPF")
add_library(${project} STATIC ${SOURCE_EXE})