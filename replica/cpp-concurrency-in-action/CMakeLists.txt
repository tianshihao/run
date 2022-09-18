# Exercises for book C++ Concurrency in action.
project(cpp-concurrency-in-action)

message(STATUS "Configuring cpp-concurrency-in-action...")

# Enable pthread.
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Find all directory under the currecnt directory.
SUBDIRLIST(subdirs ${CMAKE_CURRENT_LIST_DIR})

# Process subdirectory.
foreach(subdir ${subdirs})
  message(${subdir})

  # Set an empty list.
  set(source_files)
  # Source file
  aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/${subdir}/src source_files)

  foreach(source_file ${source_files})
    message(${source_file})
  endforeach()

  set(separator "-")

  set(target_name ${PROJECT_NAME}${separator}${subdir})

  # Add executable for every chapter.
  add_executable(${target_name} ${source_files})

  target_compile_features(${target_name} PRIVATE cxx_std_17)

  # Setting include directory and linking.
  target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/${subdir}/include)
  target_link_libraries(${target_name} PRIVATE Threads::Threads)
endforeach()
