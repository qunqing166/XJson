cmake_minimum_required(VERSION 2.8)

project(XJson)

set(CMAKE_CXX_STANDARD 20)

add_executable(main src/main.cpp src/JsonValue.cpp src/JsonSerialize.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)



# add_library(XJson STATIC
#     src/XJson.cpp
#     src/XJsonObject.cpp
#     src/XJsonArray.cpp
#     src/XJsonParser.cpp
#     src/XJsonWriter.cpp
# )

# target_link_libraries(XJson)    