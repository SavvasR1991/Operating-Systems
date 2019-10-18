cmake_minimum_required(VERSION 2.8.9)
project(Sorting_Algorithms)

include_directories(Include)
 
file(GLOB SOURCES "src/*.cpp")
 
add_executable(Sorting_Algorithms ${SOURCES})  
