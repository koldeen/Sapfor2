cmake_minimum_required(VERSION 2.8)

set(project Sapfor_2017)
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

set(FDVM_INCLUDES ../../../dvm/fdvm/trunk/include)
set(FDVM_SAGE_LIB_INCLUDES ../../../dvm/fdvm/trunk/Sage/lib/include)
set(FDVM_SAGE_H_INCLUDES ../../../dvm/fdvm/trunk/Sage/h/)
set(FTRANSFORM_BASE ../../transformers/ftransform/trunk/)
set(libdb_sources ../../../dvm/fdvm/trunk/Sage/lib/oldsrc)
set(sage_sources ../../../dvm/fdvm/trunk/Sage/lib/newsrc)
set(sagepp_sources ../../../dvm/fdvm/trunk/Sage/Sage++)
set(parser_sources ../../../dvm/fdvm/trunk/parser)

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
        ${fdvm_sources}/acc_analyzer.cpp
        ${fdvm_sources}/acc_data.cpp
        ${fdvm_sources}/acc_utilities.cpp
        ${fdvm_sources}/calls.cpp
        _src/DirectiveAnalyzer/DirectiveAnalyzer.cpp
        _src/Distribution/Array.h
        _src/Distribution/Arrays.h
        _src/Distribution/CreateDistributionDirs.cpp
        _src/Distribution/Cycle.cpp
        _src/Distribution/Distribution.cpp
        _src/Distribution/DvmhDirective.cpp
        _src/Distribution/DvmhDirectiveBase.cpp
        _src/Distribution/GraphCSR.cpp
        _src/ExpressionTransform/expr_transform.cpp
        _src/GraphCall/graph_calls.cpp
        _src/GraphLoop/graph_loops_base.cpp
        _src/GraphLoop/graph_loops.cpp
        _src/LoopAnalyzer/allocations_prepoc.cpp
        _src/LoopAnalyzer/dep_analyzer.cpp
        _src/LoopAnalyzer/directive_creator.cpp
        _src/LoopAnalyzer/insert_directive.cpp
        _src/LoopAnalyzer/loop_analyzer.cpp
        _src/LoopAnalyzer/remote_access.cpp
        _src/LoopAnalyzer/spf_directive_preproc.cpp
        _src/LoopConverter/enddo_loop_converter.cpp
        _src/LoopConverter/loop_transform.cpp
        _src/ParallelizationRegions/ParRegions.cpp
        _src/PrivateAnalyzer/private_analyzer.cpp
        _src/SageAnalysisTool/OmegaForSage/add-assert.c
        _src/SageAnalysisTool/OmegaForSage/affine.c
        _src/SageAnalysisTool/OmegaForSage/cover.c
        _src/SageAnalysisTool/OmegaForSage/ddomega-build.c
        _src/SageAnalysisTool/OmegaForSage/ddomega-use.c
        _src/SageAnalysisTool/OmegaForSage/ddomega.c
        _src/SageAnalysisTool/OmegaForSage/debug.c
        _src/SageAnalysisTool/OmegaForSage/ip.c
        _src/SageAnalysisTool/OmegaForSage/kill.c
        _src/SageAnalysisTool/OmegaForSage/refine.c
        _src/SageAnalysisTool/OmegaForSage/sagedriver.c
        _src/SageAnalysisTool/annotationDriver.cpp
        _src/SageAnalysisTool/arrayRef.cpp
        _src/SageAnalysisTool/computeInducVar.cpp
        _src/SageAnalysisTool/constanteProp.cpp
        _src/SageAnalysisTool/constanteSet.h
        _src/SageAnalysisTool/controlFlow.cpp
        _src/SageAnalysisTool/defUse.cpp
        _src/SageAnalysisTool/dependence.cpp
        _src/SageAnalysisTool/depGraph.cpp
        _src/SageAnalysisTool/depInterface.cpp
        _src/SageAnalysisTool/depInterfaceExt.h
        _src/SageAnalysisTool/flowAnalysis.cpp
        _src/SageAnalysisTool/inducVar.h
        _src/SageAnalysisTool/intrinsic.cpp
        _src/SageAnalysisTool/invariant.cpp
        _src/SageAnalysisTool/loopTransform.cpp
        _src/SageAnalysisTool/set.cpp
        _src/VerificationCode/CorrectVarDecl.cpp
        _src/VerificationCode/IncludeChecker.cpp
        _src/VerificationCode/LoopChecker.cpp
        _src/VerificationCode/VerifySageStructures.cpp
        _src/VisualizerCalls/get_information.cpp
        _src/directive_parser.cpp
        _src/SgUtils.cpp
        _src/transforms.cpp
        _src/utils.cpp)

add_executable(Sapfor_2017 ${SOURCE_EXE})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#commented for debugging
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
add_definitions("-D __SPF")
add_subdirectory(SageOldSrc)
add_subdirectory(SageNewSrc)
add_subdirectory(SageLib)
add_subdirectory(TransformCommonLib)
add_subdirectory(TransformUtils)
add_subdirectory(TransformLib)

add_definitions("-D _ARBU")
target_link_libraries(Sapfor_2017 TransformLib TransformUtils TransformCommonLib SageNewSrc SageLib gomp)