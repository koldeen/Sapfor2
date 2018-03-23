cmake_minimum_required(VERSION 2.8)

set(project parser)
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
    set(${Name} "${CMAKE_CURRENT_SOURCE_DIR}/../${Value}")
endforeach ()

# if not default parser_sources must be set in parser_sources.txt
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

add_subdirectory(../libDB ${CMAKE_CURRENT_BINARY_DIR}/libDB_build)

# if not default these must be set in ../sage_includes.txt
include_directories(${fdvm_include} ${sage_include_1} ${sage_include_2})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
add_definitions("-D __SPF")
add_definitions("-D SYS5")
add_definitions("-D YYDEBUG")

add_executable(${project} ${SOURCE_EXE})
target_link_libraries(${project} libDB)