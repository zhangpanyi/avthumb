cmake_minimum_required(VERSION 2.8)

project(avthumb C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(CXX_FLAGS
  -g
  -Wall
  -Wextra
  -Wno-unused-parameter
  -Wold-style-cast
  -Woverloaded-virtual
  -Wpointer-arith
  -Wwrite-strings
  -march=native
  -std=c++14
)
if(CMAKE_BUILD_BITS EQUAL 32)
  list(APPEND CXX_FLAGS "-m32")
endif()
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG")

set(BINARY_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

find_package(OpenCV REQUIRED)
find_package(Protobuf REQUIRED)

set(GRPC_PROTOCOL_LIBRARY protocol)
set(GRPC_PROTOCOL_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/protocol)
add_subdirectory(protocol)

set(SPDLOG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/third_party/spdlog/include)

add_subdirectory(app)
