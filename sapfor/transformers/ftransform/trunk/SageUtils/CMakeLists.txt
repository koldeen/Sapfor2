cmake_minimum_required(VERSION 3.1)

set(project SageUtils)
if(TARGET ${project})
    return()
endif()
project(${project})
message("processing ${project}")

set(project SageUtils)
set(CMAKE_CXX_STANDARD 11)

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
        ./src/SageUtils.cpp
        ./src/SageTransformUtils.cpp
        ./src/decodeStmtVariant.cpp
        ./src/LineReorderRecord.cpp
        ./src/LineReorderer.cpp
        )
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

include_directories(./include)
include_directories(${fdvm_include} ${sage_include_1} ${sage_include_2})
add_library(SageUtils STATIC ${SOURCE_LIB})


add_subdirectory(../libSage ${CMAKE_CURRENT_BINARY_DIR}/libSage)
add_subdirectory(../libSage++ ${CMAKE_CURRENT_BINARY_DIR}/libSage++)
target_link_libraries(SageUtils libSage libSage++)
