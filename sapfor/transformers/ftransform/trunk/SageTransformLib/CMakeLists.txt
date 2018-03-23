cmake_minimum_required(VERSION 2.8)

set(project SageTransformLib)
if(TARGET ${project})
    return()
endif()
project(${project})
message("processing ${project}")

# Read pathes to external sapfor directories
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../paths.txt")
    message("Found paths.txt, using custom paths.")
    FILE(STRINGS ../paths.txt SAPFOR_PATHS)
else ()
    message("Not found paths.txt, using default paths.")
    FILE(STRINGS ../paths.default.txt SAPFOR_PATHS)
endif ()
foreach (NameAndValue ${SAPFOR_PATHS})
    # Strip leading spaces
    string(REGEX REPLACE "^[ ]+" "" NameAndValue ${NameAndValue})
    # Find variable name
    string(REGEX MATCH "^[^=]+" Name ${NameAndValue})
    # Find the value
    string(REPLACE "${Name}=" "" Value ${NameAndValue})
    # Set the variable, note the ../ because we are deeper than the file
    set(${Name} "../${Value}")
endforeach ()

set(SOURCE_LIB
        ./src/dependency/Dependency.cpp
        ./src/dependency/DependencyInfo.cpp
        ./src/dependency/DependencyInfoGetter.cpp
        ./src/dependency/DependencyUtils.cpp
        src/LoopWrapTransform.cpp
        ./src/LoopTransformBreak.cpp
        ./src/LoopTransformMerge.cpp
        ./src/LoopTransformSplit.cpp
        ./src/LoopTransformTighten.cpp
        ./src/StatementOrderTransform.cpp
        ./src/StatementReorderer.cpp
        ./src/StatementReshuffler.cpp
        ./src/StatementsSplitter.cpp
        ./src/TempArrayTransform.cpp
        ./src/WriteDearray.cpp
        ./src/LoopCombine.cpp
        ./src/BaseTransform.cpp)

include_directories(./include)
include_directories(../CommonLib/include)
include_directories(../SageUtils/include)
include_directories(${fdvm_include} ${sage_include_1} ${sage_include_2})
include_directories(${sapfor2017_include})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
add_library(SageTransformLib STATIC ${SOURCE_LIB})

add_subdirectory(../libSage ${CMAKE_CURRENT_BINARY_DIR}/libSage)
add_subdirectory(../libSage++ ${CMAKE_CURRENT_BINARY_DIR}/libSage++)
add_subdirectory(../CommonLib ${CMAKE_CURRENT_BINARY_DIR}/CommonLib)
add_subdirectory(../SageUtils ${CMAKE_CURRENT_BINARY_DIR}/SageUtils)
target_link_libraries(SageTransformLib SageUtils CommonLib libSage libSage++)