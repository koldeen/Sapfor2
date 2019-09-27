cmake_minimum_required(VERSION 2.8)

set(project Parser)
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
        ${parser_sources}/cftn.c
        ${parser_sources}/errors.c
        ${parser_sources}/gram1.tab.c
        ${parser_sources}/hash.c
        ${parser_sources}/init.c
        ${parser_sources}/lexfdvm.c
        ${parser_sources}/lists.c
        ${parser_sources}/low_hpf.c
        ${parser_sources}/misc.c
        ${parser_sources}/stat.c
        ${parser_sources}/sym.c
        ${parser_sources}/types.c
        ${parser_sources}/unparse_hpf.c
        )

# if not default ${fdvm_include}, ${sage_include_1}, ${sage_include_2} must be set in ../paths.txt
include_directories(${fdvm_include} ${sage_include_1} ${sage_include_2})
add_executable(Parser ${SOURCE_EXE})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
add_definitions("-D __SPF")
add_definitions("-D _CRT_SECURE_NO_WARNINGS")
add_definitions("-D SYS5")
add_definitions("-D YYDEBUG")

add_subdirectory(../SageOldSrc ${CMAKE_CURRENT_BINARY_DIR}/SageOldSrc)
target_link_libraries(Parser SageOldSrc)
