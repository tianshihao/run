cmake_minimum_required(VERSION 3.21.0)
project(run VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_HOME_DIRECTORY})

add_subdirectory(utils)
add_subdirectory(playground)
add_subdirectory(ex)
add_subdirectory(replica)
