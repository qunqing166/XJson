cmake_minimum_required(VERSION 3.15)

project(XJson)

set(CMAKE_CXX_STANDARD 20)

set(SRC_LIST src/JsonValue.cpp src/JsonSerialize.cpp)
set(MAIN test/test.cpp)

add_executable(main ${MAIN} ${SRC_LIST})

add_library(XJson_static STATIC ${SRC_LIST})
add_library(XJson_shared SHARED ${SRC_LIST})

set_target_properties(XJson_static PROPERTIES OUTPUT_NAME "XJson")
set_target_properties(XJson_shared PROPERTIES OUTPUT_NAME "XJson")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

