cmake_minimum_required(VERSION 3.8)
project(run VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include_directories(${CMAKE_HOME_DIRECTORY})

# export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add_subdirectory(utils)
add_subdirectory(playground)
# add_subdirectory(ex)
add_subdirectory(replica)
