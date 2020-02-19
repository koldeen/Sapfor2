cmake_minimum_required(VERSION 2.8)

set(project Sapfor)
if (TARGET ${project})
    return()
endif ()
project(${project})
message("processing ${project}")
#include(CTest)

add_definitions("-D SYS5")
add_definitions("-D YYDEBUG")

set(JAVA_SDK_DIR "${JAVA_HOME}")
#set(CMAKE_CXX_STANDARD 11)

set(fdvm_include ../../../dvm/fdvm/trunk/include)
set(sage_include_1 ../../../dvm/fdvm/trunk/Sage/lib/include)
set(sage_include_2 ../../../dvm/fdvm/trunk/Sage/h/)
set(libdb_sources ../../../dvm/fdvm/trunk/Sage/lib/oldsrc)
set(sage_sources ../../../dvm/fdvm/trunk/Sage/lib/newsrc)
set(sagepp_sources ../../../dvm/fdvm/trunk/Sage/Sage++)
set(parser_sources ../../../dvm/fdvm/trunk/parser)
set(pppa_sources ../../../dvm/tools/pppa/trunk/src)
set(zlib_sources ../../../dvm/tools/Zlib)

# Read pathes to external sapfor directories
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/paths.txt")
    message("Found paths.txt, using custom paths.")
    FILE(STRINGS ./paths.txt SAPFOR_PATHS)
else ()
    message("Not found paths.txt, using default paths.")
    FILE(STRINGS ./paths.default.txt SAPFOR_PATHS)
endif ()

if(NOT EXISTS ${JAVA_SDK_DIR}/include)
	if (WIN32)
		message("path '${JAVA_SDK_DIR}/include' does not exist, set JAVA_HOME correctly")
	else ()
		message("path '${JAVA_SDK_DIR}/include' does not exist, set JAVA_HOME correctly")
	endif()		
endif()

if (WIN32)
	if(NOT EXISTS ${JAVA_SDK_DIR}/include/win32)
		message("path '${JAVA_SDK_DIR}/include/win32' does not exist, set JAVA_HOME correctly")
	endif()
elseif (UNIX)
	if(NOT EXISTS ${JAVA_SDK_DIR}/include/linux)
		message("path '${JAVA_SDK_DIR}/include/linux' does not exist, set JAVA_HOME correctly")
	endif()
endif()

  
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
include_directories(${fdvm_include})
include_directories(${sage_include_1})
include_directories(${zlib_sources}/include)
#Zlib includes
include_directories(${sage_include_2})

#JAVA includes 
if (EXISTS ${JAVA_SDK_DIR}/include)
	include_directories(${JAVA_SDK_DIR}/include)
	if (WIN32)
		include_directories(${JAVA_SDK_DIR}/include/win32)
	else ()
		include_directories(${JAVA_SDK_DIR}/include/linux)
	endif()
endif()

set(VS_CALLS _src/VisualizerCalls/get_information.cpp
		_src/VisualizerCalls/get_information.h
		_src/VisualizerCalls/SendMessage.cpp
		_src/VisualizerCalls/SendMessage.h)
	
set(VERIF _src/VerificationCode/CorrectVarDecl.cpp
        _src/VerificationCode/IncludeChecker.cpp
        _src/VerificationCode/LoopChecker.cpp
        _src/VerificationCode/VerifySageStructures.cpp
		_src/VerificationCode/verifications.h)

set(UTILS _src/Utils/AstWrapper.h
		_src/Utils/BoostStackTrace.cpp
		_src/Utils/CommonBlock.h
		_src/Utils/DefUseList.h
		_src/Utils/errors.h
		_src/Utils/leak_detector.h
		_src/Utils/PassManager.h
		_src/Utils/RationalNum.cpp
		_src/Utils/RationalNum.h
        _src/Utils/SgUtils.cpp
		_src/Utils/SgUtils.h
        _src/Utils/types.h
        _src/Utils/utils.cpp
		_src/Utils/utils.h
		_src/Utils/version.h)
		
set(OMEGA _src/SageAnalysisTool/OmegaForSage/add-assert.cpp
        _src/SageAnalysisTool/OmegaForSage/affine.cpp
        _src/SageAnalysisTool/OmegaForSage/cover.cpp
        _src/SageAnalysisTool/OmegaForSage/ddomega-build.cpp
        _src/SageAnalysisTool/OmegaForSage/ddomega-use.cpp
        _src/SageAnalysisTool/OmegaForSage/ddomega.cpp
        _src/SageAnalysisTool/OmegaForSage/debug.cpp
        _src/SageAnalysisTool/OmegaForSage/ip.cpp
        _src/SageAnalysisTool/OmegaForSage/kill.cpp
        _src/SageAnalysisTool/OmegaForSage/refine.cpp
        _src/SageAnalysisTool/OmegaForSage/sagedriver.cpp
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
        _src/SageAnalysisTool/set.cpp)

set(PRIV _src/PrivateAnalyzer/private_analyzer.cpp
		_src/PrivateAnalyzer/private_analyzer.h
		${fdvm_sources}/acc_analyzer.cpp
        ${fdvm_sources}/acc_data.cpp
        ${fdvm_sources}/acc_utilities.cpp
        ${fdvm_sources}/calls.cpp
		)
		
set(PARALLEL_REG _src/ParallelizationRegions/ParRegions.cpp
		_src/ParallelizationRegions/ParRegions.h
		_src/ParallelizationRegions/ParRegions_func.h
		_src/ParallelizationRegions/expand_extract_reg.cpp
		_src/ParallelizationRegions/expand_extract_reg.h
		_src/ParallelizationRegions/resolve_par_reg_conflicts.cpp
		_src/ParallelizationRegions/resolve_par_reg_conflicts.h)
		
set(LOOP_CONV _src/LoopConverter/array_assign_to_loop.cpp
		_src/LoopConverter/array_assign_to_loop.h
        _src/LoopConverter/enddo_loop_converter.cpp
		_src/LoopConverter/enddo_loop_converter.h
        _src/LoopConverter/loop_transform.cpp
		_src/LoopConverter/loop_transform.h
		_src/LoopConverter/loops_combiner.cpp
		_src/LoopConverter/loops_combiner.h
		_src/LoopConverter/loops_splitter.cpp
		_src/LoopConverter/loops_splitter.h
        _src/LoopConverter/private_arrays_breeder.cpp
        _src/LoopConverter/private_arrays_breeder.h		
        _src/LoopConverter/swap_array_dims.cpp
		_src/LoopConverter/swap_array_dims.h
		_src/LoopConverter/uniq_call_chain_dup.cpp
		_src/LoopConverter/uniq_call_chain_dup.h)
		
set(CFG _src/CFGraph/CFG_BasicBlock.cpp
		_src/CFGraph/CFG_BasicBlock.h
		_src/CFGraph/CFG_Common.cpp
		_src/CFGraph/CFG_Common.h		
		_src/CFGraph/CFG_Variables.cpp
		_src/CFGraph/CFG_Variables.h
		_src/CFGraph/CFGraph.cpp
		_src/CFGraph/CFGraph.h)
		
set(CREATE_INTER_T	_src/CreateInterTree/CreateInterTree.cpp
		_src/CreateInterTree/CreateInterTree.h)

set(DIRA  _src/DirectiveAnalyzer/DirectiveAnalyzer.cpp
		_src/DirectiveAnalyzer/DirectiveAnalyzer.h)
		
set(DISTR _src/Distribution/Array.cpp
        _src/Distribution/Array.h
        _src/Distribution/Arrays.h
        _src/Distribution/CreateDistributionDirs.cpp
		_src/Distribution/CreateDistributionDirs.h
        _src/Distribution/Cycle.cpp
		_src/Distribution/Cycle.h
        _src/Distribution/Distribution.cpp
		_src/Distribution/Distribution.h
        _src/Distribution/DvmhDirective.cpp
		_src/Distribution/DvmhDirective.h
		_src/Distribution/DvmhDirective_func.h
        _src/Distribution/DvmhDirectiveBase.cpp
		_src/Distribution/DvmhDirectiveBase.h
        _src/Distribution/GraphCSR.cpp
		_src/Distribution/GraphCSR.h)
		
set(DVMH_REG _src/DvmhRegions/DvmhRegionInserter.cpp
		_src/DvmhRegions/DvmhRegionInserter.h
		_src/DvmhRegions/RegionsMerger.cpp
		_src/DvmhRegions/RegionsMerger.h
		_src/DvmhRegions/ReadWriteAnalyzer.cpp
		_src/DvmhRegions/ReadWriteAnalyzer.h
		_src/DvmhRegions/LoopChecker.cpp
		_src/DvmhRegions/LoopChecker.h
		_src/DvmhRegions/DvmhRegion.cpp
		_src/DvmhRegions/DvmhRegion.h
		_src/DvmhRegions/VarUsages.cpp
		_src/DvmhRegions/VarUsages.h
		_src/DvmhRegions/TypedSymbol.cpp
		_src/DvmhRegions/TypedSymbol.h)
		
set(DYNA _src/DynamicAnalysis/createParallelRegions.cpp
		_src/DynamicAnalysis/createParallelRegions.h
		_src/DynamicAnalysis/gcov_info.cpp
		_src/DynamicAnalysis/gcov_info.h
		_src/DynamicAnalysis/gCov_parser.cpp
		_src/DynamicAnalysis/gCov_parser_func.h)

set(EXPR_TRANSFORM _src/ExpressionTransform/control_flow_graph_part.cpp
		_src/ExpressionTransform/expr_transform.cpp
		_src/ExpressionTransform/expr_transform.h)
		
set(GR_CALL _src/GraphCall/graph_calls.cpp
		_src/GraphCall/graph_calls.h
		_src/GraphCall/graph_calls_base.cpp
		_src/GraphCall/graph_calls_func.h)
		
set(GR_LOOP _src/GraphLoop/graph_loops_base.cpp
        _src/GraphLoop/graph_loops.cpp
		_src/GraphLoop/graph_loops.h
		_src/GraphLoop/graph_loops_func.h)
		
set(INLINER _src/Inliner/CopySubprogramBetweenFiles.cpp
		_src/Inliner/inliner.h)
		
set(LOOP_ANALYZER  _src/LoopAnalyzer/allocations_prepoc.cpp
        _src/LoopAnalyzer/dep_analyzer.cpp
        _src/LoopAnalyzer/directive_creator.cpp
		_src/LoopAnalyzer/directive_creator_base.cpp
		_src/LoopAnalyzer/directive_creator.h
		_src/LoopAnalyzer/directive_parser.cpp
		_src/LoopAnalyzer/directive_parser.h
        _src/LoopAnalyzer/insert_directive.cpp
        _src/LoopAnalyzer/loop_analyzer.cpp
		_src/LoopAnalyzer/loop_analyzer.h
        _src/LoopAnalyzer/remote_access.cpp
		_src/LoopAnalyzer/shadow.cpp
		_src/LoopAnalyzer/shadow.h
        _src/LoopAnalyzer/spf_directive_preproc.cpp)
		
set(MAIN _src/Sapfor.cpp
		_src/Sapfor.h
		_src/SapforData.h)

set(PREDICTOR _src/Predictor/PredictScheme.cpp
              _src/Predictor/PredictScheme.h)

set(PARSER  ${parser_sources}/cftn.c
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
			${parser_sources}/unparse_hpf.c)

set(PPPA    ${pppa_sources}/inter.cpp
			${pppa_sources}/potensyn.cpp
			${pppa_sources}/statfile.cpp
			${pppa_sources}/statprintf.cpp
			${pppa_sources}/statread.cpp
			${pppa_sources}/treeinter.cpp  
			${pppa_sources}/bool.h
			${pppa_sources}/dvmh_stat.h
			${pppa_sources}/inter.h
			${pppa_sources}/potensyn.h
			${pppa_sources}/statist.h
			${pppa_sources}/statprintf.h
			${pppa_sources}/statread.h
			${pppa_sources}/strall.h
			${pppa_sources}/sysstat.h
			${pppa_sources}/treeinter.h
			${pppa_sources}/ver.h)
			
set(ZLIB    ${zlib_sources}/src/adler32.c
			${zlib_sources}/src/compress.c
			${zlib_sources}/src/crc32.c
			${zlib_sources}/src/deflate.c
			${zlib_sources}/src/gzio.c
			${zlib_sources}/src/infblock.c
			${zlib_sources}/src/infcodes.c
			${zlib_sources}/src/inffast.c
			${zlib_sources}/src/inflate.c
			${zlib_sources}/src/inftrees.c
			${zlib_sources}/src/infutil.c
			${zlib_sources}/src/trees.c
			${zlib_sources}/src/uncompr.c
			${zlib_sources}/src/zutil.c)

set(SOURCE_EXE		
	${CFG}
	${CREATE_INTER_T}
	${DIRA}
	${DISTR}
	${DVMH_REG}
	${DYNA}
	${EXPR_TRANSFORM}
	${GR_CALL}
	${GR_LOOP}
	${INLINER}
	${LOOP_ANALYZER}
	${LOOP_CONV}
	${PARALLEL_REG}
	${PRIV}
	${OMEGA}
	${UTILS}
	${VERIF}
	${VS_CALLS}
	${MAIN}
	${PREDICTOR}
	${PARSER}
	${PPPA}
	${ZLIB})

add_executable(Sapfor_F ${SOURCE_EXE})

source_group (CFGraph FILES ${CFG})
source_group (CodeConverter FILES ${LOOP_CONV})
source_group (CreateIntervals FILES ${CREATE_INTER_T})
source_group (DirectiveAnalyzer FILES ${DIRA})
source_group (Distribution FILES ${DISTR})
source_group (DvmhRegions FILES ${DVMH_REG})
source_group (DynamicAnalysis FILES ${DYNA})
source_group (ExpressionTransform FILES ${EXPR_TRANSFORM})
source_group (CallGraph FILES ${GR_CALL})
source_group (LoopGraph FILES ${GR_LOOP})
source_group (Inliner FILES ${INLINER})
source_group (LoopAnalyzer FILES ${LOOP_ANALYZER})
source_group (ParallelizationRegions FILES ${PARALLEL_REG})
source_group (PrivateAnalyzer FILES ${PRIV})	  
source_group (SageExtension FILES ${OMEGA})
source_group (Utils FILES ${UTILS})
source_group (VerificationCode FILES ${VERIF})	     
source_group (VisualizerCalls FILES ${VS_CALLS})
source_group (_SapforMain FILES ${MAIN})
source_group (Predictor FILES ${PREDICTOR})
source_group (Parser FILES ${PARSER})
source_group (PPPA\\PPPA FILES ${PPPA})
source_group (PPPA\\ZLib FILES ${ZLIB})
   
if (MSVC_IDE)   
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
else()
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

add_definitions("-D __SPF")
add_definitions("-D _CRT_SECURE_NO_WARNINGS")
add_definitions("-D _CRT_NON_CONFORMING_SWPRINTFS")

add_subdirectory(SageOldSrc)
add_subdirectory(SageNewSrc)
add_subdirectory(SageLib)
add_subdirectory(Parser)
add_subdirectory(Inliner)

add_definitions("-D __SPF_BUILT_IN_PARSER")
add_definitions("-D __SPF_BUILT_IN_PPPA")

if (WIN32)
	if(EXISTS ${JAVA_SDK_DIR}/include/win32)
		add_definitions("-D JAVA")
	endif()
elseif (UNIX)
	if(EXISTS ${JAVA_SDK_DIR}/include/linux)
		add_definitions("-D JAVA")
	endif()
endif()

if (WIN32)
	target_link_libraries(Sapfor_F SageNewSrc SageLib SageOldSrc)
elseif(UNIX)
	target_link_libraries(Sapfor_F SageNewSrc SageLib SageOldSrc pthread)
endif()

#install(TARGETS <name.exe/dll>
#    LIBRARY DESTINATION <name_f>
#	RUNTIME DESTINATION <name_f>)
