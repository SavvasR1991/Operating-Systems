cmake_minimum_required(VERSION 2.8.9)
project(FileManagment)

include_directories(Include)

file(GLOB SOURCES "src/*.cpp")
 
add_executable(FileManagment ${SOURCES})  
