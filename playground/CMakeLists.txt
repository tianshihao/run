# Get all .cpp files of current directory.
file(GLOB_RECURSE SRC_FILES *.cpp)
# Generate respective executable for each .cpp file.
foreach(SRC_FILE ${SRC_FILES})
    # Get the name of the file without the extension.
    get_filename_component(EXEC_NAME ${SRC_FILE} NAME_WE)
    # Generate the executable.
    add_executable(${EXEC_NAME} ${SRC_FILE})
    # Link the executable with the library.
    target_link_libraries(${EXEC_NAME} ${LIB_NAME})
endforeach(SRC_FILE ${SRC_FILES})