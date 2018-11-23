cmake_minimum_required(VERSION 2.8)

set(project libDB)
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

# if not default ${libdb_sources} must be set in ../paths.txt
set(SOURCE_LIB
        ${libdb_sources}/anal_ind.c
        ${libdb_sources}/db.c
        ${libdb_sources}/db_unp.c
        ${libdb_sources}/db_unp_comm.c
        ${libdb_sources}/db_unp_vpc.c
        ${libdb_sources}/dbutils.c
        ${libdb_sources}/garb_coll.c
        ${libdb_sources}/glob_anal.c
        ${libdb_sources}/ker_fun.c
        ${libdb_sources}/list.c
        ${libdb_sources}/make_nodes.c
        ${libdb_sources}/mod_ref.c
        ${libdb_sources}/ndeps.c
        ${libdb_sources}/readnodes.c
        ${libdb_sources}/sets.c
        ${libdb_sources}/setutils.c
        ${libdb_sources}/symb_alg.c
        ${libdb_sources}/writenodes.c
        )

# if not default ${fdvm_include}, ${sage_include_1}, ${sage_include_2} must be set in ../paths.txt
include_directories(${fdvm_include} ${sage_include_1} ${sage_include_2})

add_library(libDB STATIC ${SOURCE_LIB})
