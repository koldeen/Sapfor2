cmake_minimum_required(VERSION 2.8.8)
project(gtest_builder C CXX)

set(GTEST_FORCE_SHARED_CRT ON)
set(GTEST_DISABLE_PTHREADS ON)

if(MINGW OR CYGWIN)
    set(GTEST_DISABLE_PTHREADS ON)
endif()

add_subdirectory(../SageTransformLib ${CMAKE_CURRENT_BINARY_DIR}/SageTransformLib)
add_subdirectory(../SageUtils ${CMAKE_CURRENT_BINARY_DIR}/SageUtils)
add_subdirectory(../CommonLib ${CMAKE_CURRENT_BINARY_DIR}/CommonLib)
add_subdirectory(../libSage ${CMAKE_CURRENT_BINARY_DIR}/libSage)
add_subdirectory(../libSage++ ${CMAKE_CURRENT_BINARY_DIR}/libSage++)
add_subdirectory(../libDB ${CMAKE_CURRENT_BINARY_DIR}/libDB)
set(OWN_INCLUDES SageTransformLib SageUtils CommonLib libSage libSage++ libDB)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(COMMON_LIB_PATH ../CommonLib/test)
set(SAGE_UTILS_PATH ../SageUtils/test)
set(SAGE_TRANSFORM_LIB_PATH ../SageTransformLib/test)

include_directories(./include)
set(TEST_COMMON_SRC ./src/TestUtils.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
#commented out for debugging
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

#COMMON_LIB_TESTS
add_executable(StringUtilsTest.exe ${COMMON_LIB_PATH}/StringUtilsTest.cpp ${TEST_COMMON_SRC})
target_link_libraries(StringUtilsTest.exe GTest::GTest GTest::Main ${OWN_INCLUDES})
add_test(StringUtilsTest StringUtilsTest.exe)

#SAGE_UTILS_LIB_TESTS
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

#SAGE_TRANSFORM_LIB_TESTS
add_executable(LoopTransformTightenTest.exe ${SAGE_TRANSFORM_LIB_PATH}/LoopTransformTightenTest.cpp ${TEST_COMMON_SRC})
target_link_libraries(LoopTransformTightenTest.exe GTest::GTest GTest::Main ${OWN_INCLUDES})
add_test(LoopTransformTightenTest LoopTransformTightenTest.exe)

set(TEST_NAME LoopWrapTransformTest)
add_executable(${TEST_NAME}.exe ${SAGE_TRANSFORM_LIB_PATH}/${TEST_NAME}.cpp ${TEST_COMMON_SRC})
target_link_libraries(${TEST_NAME}.exe GTest::GTest GTest::Main ${OWN_INCLUDES})
add_test(${TEST_NAME} ${TEST_NAME}.exe)