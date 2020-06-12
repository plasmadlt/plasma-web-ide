cmake_minimum_required(VERSION 3.5)

project(talk VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ion.cdt CONFIG REQUIRED)
message("Found CDT package at: ${ION_CDT_ROOT}")

### Generate the wasm and abi
add_contract(talk talk talk.hpp talk.cpp)

# Print include directories
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "Include directories='${dir}'")
endforeach()

message(STATUS "Source directory='${CMAKE_SOURCE_DIR}'")
message(STATUS "Build directory='${CMAKE_BINARY_DIR}'")
message(STATUS "Build documentation='${BUILD_DOXYGEN}'")
