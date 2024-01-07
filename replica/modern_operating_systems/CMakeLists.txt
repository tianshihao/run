# Get the directory name of the current CMakeLists.txt file and set it to the
# component name.
get_filename_component(COMPONENT_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

CONFIGURE_MODULE(${COMPONENT_NAME} ${CMAKE_CURRENT_LIST_DIR} TARGET_LIST)

# Enable pthread.
FIND_PACKAGE(Threads REQUIRED)

if(CMAKE_THREAD_LIBS_INIT)
  foreach(TARGET ${TARGET_LIST})
    target_link_libraries(${TARGET} PUBLIC "${CMAKE_THREAD_LIBS_INIT}")
  endforeach(TARGET ${TARGET_LIST})
endif(CMAKE_THREAD_LIBS_INIT)
