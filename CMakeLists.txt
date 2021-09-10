cmake_minimum_required(VERSION 3.15)

project(bandClock)
add_library(${CMAKE_PROJECT_NAME} bandClock.ino)
set_target_properties(bandClock PROPERTIES LINKER_LANGUAGE CXX)
