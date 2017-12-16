cmake_minimum_required(VERSION 2.8)

set(project CommonLib)
if (TARGET ${project})
    return()
endif ()
project(${project})
message("processing ${project}")

set(SOURCE_LIB
        ./src/Log.cpp
        ./src/StringUtils.cpp
        ./src/Stacktrace.cpp
        ./src/SageTransformException.cpp
        ./src/SignalHandling.cpp
        )

include_directories(./include)

add_library(CommonLib STATIC ${SOURCE_LIB})
