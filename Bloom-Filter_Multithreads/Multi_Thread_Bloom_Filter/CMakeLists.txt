cmake_minimum_required(VERSION 2.8.9)
project(BloomFilter)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "-m32 -pthread")
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-m32 -pthread")


include_directories(Include)
 
file(GLOB SOURCES "src/*.cpp")
 
add_executable(invoke-oracle-multithreaded ${SOURCES})  

target_link_libraries(invoke-oracle-multithreaded ${CMAKE_SOURCE_DIR}/Include/libhash.a)
target_link_libraries(invoke-oracle-multithreaded ${CMAKE_SOURCE_DIR}/Include/liboracle_v3.a)

