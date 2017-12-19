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

include_directories(./include)
set(TEST_COMMON_SRC ./src/TestUtils.cpp)

add_executable(StringUtilsTest.exe ${COMMON_LIB_PATH}/StringUtilsTest.cpp ${TEST_COMMON_SRC})
target_link_libraries(StringUtilsTest.exe GTest::GTest GTest::Main ${OWN_INCLUDES})
add_test(StringUtilsTest StringUtilsTest.exe)

add_executable(StubTest.exe ${SAGE_UTILS_PATH}/StubTest.cpp ${TEST_COMMON_SRC})
target_link_libraries(StubTest.exe GTest::GTest GTest::Main ${OWN_INCLUDES})
add_test(StubTest StubTest.exe)

add_executable(LineReorderRecordTest.exe ${SAGE_UTILS_PATH}/LineReorderRecordTest.cpp ${TEST_COMMON_SRC})
target_link_libraries(LineReorderRecordTest.exe GTest::GTest GTest::Main ${OWN_INCLUDES})
add_test(LineReorderRecordTest LineReorderRecordTest.exe)

add_executable(LineReordererTest.exe ${SAGE_UTILS_PATH}/LineReordererTest.cpp ${TEST_COMMON_SRC})
target_link_libraries(LineReordererTest.exe GTest::GTest GTest::Main ${OWN_INCLUDES})
add_test(LineReordererTest LineReordererTest.exe)

add_executable(SageTransformUtilsTest.exe ${SAGE_UTILS_PATH}/SageTransformUtilsTest.cpp ${TEST_COMMON_SRC})
target_link_libraries(SageTransformUtilsTest.exe GTest::GTest GTest::Main ${OWN_INCLUDES})
add_test(SageTransformUtilsTest SageTransformUtilsTest.exe)

add_executable(SageUtilsTest.exe ${SAGE_UTILS_PATH}/SageUtilsTest.cpp ${TEST_COMMON_SRC})
target_link_libraries(SageUtilsTest.exe GTest::GTest GTest::Main ${OWN_INCLUDES})
add_test(SageUtilsTest SageUtilsTest.exe)

add_executable(LoopTransformTighten.exe ${SAGE_TRANSFORM_LIB_PATH}/LoopTransformTightenTest.cpp ${TEST_COMMON_SRC})
target_link_libraries(LoopTransformTighten.exe GTest::GTest GTest::Main ${OWN_INCLUDES})
add_test(LoopTransformTighten LoopTransformTighten.exe)