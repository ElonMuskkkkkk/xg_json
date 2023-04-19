cmake_minimum_required(VERSION 3.2)

project(XG_JSON)

set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -fPIC -g -std=c++11")

set(SRC ./src/json_item.cpp
        ./src/json_parse.cpp
        ./src/json.cpp)

add_library(xg-json SHARED ${SRC})

add_executable(test_item ./test/test_item.cpp)
target_link_libraries(test_item xg-json)

add_executable(test ./test/test.cpp)
target_link_libraries(test xg-json)


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
