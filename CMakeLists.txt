CMAKE_MINIMUM_REQUIRED(VERSION 3.15.0)
PROJECT(run VERSION 0.1.0)

INCLUDE(cmake/utils.cmake)
INCLUDE(cmake/gtest.cmake)

ADD_SUBDIRECTORY(replica)
ADD_SUBDIRECTORY(utils)
add_subdirectory(test)

set(CMAKE_CXX_STANDARD 17)