cmake_minimum_required(VERSION 2.8)

set(project ftransform)
if (TARGET ${project})
    return()
endif ()
project(${project})
message("processing ${project}")
include(CTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions("-D SYS5")
add_definitions("-D YYDEBUG")

# Read pathes to external sapfor directories
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/paths.txt")
    message("Found paths.txt, using custom paths.")
    FILE(STRINGS ./paths.txt SAPFOR_PATHS)
else ()
    message("Not found paths.txt, using default paths.")
    FILE(STRINGS ./paths.default.txt SAPFOR_PATHS)
endif ()
foreach (NameAndValue ${SAPFOR_PATHS})
    # Strip leading spaces
    string(REGEX REPLACE "^[ ]+" "" NameAndValue ${NameAndValue})
    # Find variable name
    string(REGEX MATCH "^[^=]+" Name ${NameAndValue})
    # Find the value
    string(REPLACE "${Name}=" "" Value ${NameAndValue})
    # Set the variable, note the ../ because we are deeper than the file
    set(${Name} "${Value}")
    message("Using ${Name} ${${Name}}")
endforeach ()

#set(SOURCE_EXE
#        ./SageTransformApp/src/main.cpp
#        ./SageTransformApp/src/LaunchOptions.cpp)

include_directories(./CommonLib/include)
include_directories(./SageUtils/include)
#include_directories(./SageTransformLib/include)
#include_directories(./SageTransformApp/include)
include_directories(${fdvm_include} ${sage_include_1} ${sage_include_2})
#include_directories(${sapfor2017_include})
#add_executable(ftransform ${SOURCE_EXE})

add_subdirectory(CommonLib)
add_subdirectory(SageUtils)
#add_subdirectory(SageTransformLib)
add_subdirectory(test)
#target_link_libraries(ftransform SageTransformLib SageUtils CommonLib)