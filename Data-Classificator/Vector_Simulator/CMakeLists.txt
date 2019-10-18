cmake_minimum_required(VERSION 2.8.9)
project(Vector_Simulator)

include_directories(Include)
 
file(GLOB SOURCES "src/*.cpp")
 
add_executable(Vector_Simulator ${SOURCES})  
