cmake_minimum_required(VERSION 2.8.8)
project(gtest_builder C CXX)

set(GTEST_FORCE_SHARED_CRT ON)
set(GTEST_DISABLE_PTHREADS ON)

if(MINGW OR CYGWIN)
    set(GTEST_DISABLE_PTHREADS ON)
endif()

add_subdirectory(../CommonLib ${CMAKE_CURRENT_BINARY_DIR}/CommonLib)
add_subdirectory(../SageUtils ${CMAKE_CURRENT_BINARY_DIR}/SageUtils)
add_subdirectory(../SageTransformLib ${CMAKE_CURRENT_BINARY_DIR}/SageTransformLib)
set(OWN_INCLUDES SageUtils CommonLib SageTransformLib)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(COMMON_LIB_PATH ../CommonLib/test)
set(SAGE_UTILS_PATH ../SageUtils/test)
set(SAGE_TRANSFORM_LIB_PATH ../SageTransformLib/test)

add_executable(StringUtilsTest.exe ${COMMON_LIB_PATH}/StringUtilsTest.cpp)
target_link_libraries(StringUtilsTest.exe GTest::GTest GTest::Main ${OWN_INCLUDES})
add_test(StringUtilsTest StringUtilsTest.exe)

add_executable(StubTest.exe ${SAGE_UTILS_PATH}/StubTest.cpp)
target_link_libraries(StubTest.exe GTest::GTest GTest::Main ${OWN_INCLUDES})
add_test(StubTest StubTest.exe)

add_executable(LoopTransformTighten.exe ${SAGE_TRANSFORM_LIB_PATH}/LoopTransformTightenTest.cpp)
target_link_libraries(LoopTransformTighten.exe GTest::GTest GTest::Main ${OWN_INCLUDES})
add_test(LoopTransformTighten LoopTransformTighten.exe)