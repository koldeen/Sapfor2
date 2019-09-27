cmake_minimum_required(VERSION 2.8)

set(project Inliner)
#also named as libSage++
if (TARGET ${project})
    return()
endif ()
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

# if not default ${sagepp_sources} must be set in ../paths.txt
set(SOURCE_EXE
        ${inline_expansion_sources}/hlp.cpp
        ${inline_expansion_sources}/inliner.cpp
        ${inline_expansion_sources}/inl_exp.cpp
        )

# if not default ${fdvm_include}, ${sage_include_1}, ${sage_include_2} must be set in ../paths.txt
include_directories(${fdvm_include} ${sage_include_1} ${sage_include_2})
add_executable(Inliner ${SOURCE_EXE})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
add_definitions("-D __SPF")
add_definitions("-D _CRT_SECURE_NO_WARNINGS")
add_definitions("-D SYS5")
add_definitions("-D YYDEBUG")

add_subdirectory(../SageOldSrc ${CMAKE_CURRENT_BINARY_DIR}/SageOldSrc)
add_subdirectory(../SageNewSrc ${CMAKE_CURRENT_BINARY_DIR}/SageNewSrc)
add_subdirectory(../SageLib ${CMAKE_CURRENT_BINARY_DIR}/SageLib)
target_link_libraries(Inliner SageOldSrc SageNewSrc SageLib)
