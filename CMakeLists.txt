CMAKE_MINIMUM_REQUIRED(VERSION 3.15.0)
PROJECT(run VERSION 0.1.0)

# include(CTest)
# enable_testing()
INCLUDE(cmake/utils.cmake)

ADD_SUBDIRECTORY(replica)
ADD_SUBDIRECTORY(utils)
