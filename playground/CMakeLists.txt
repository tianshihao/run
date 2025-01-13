# Get all .cpp files of current directory.
file(GLOB_RECURSE SRC_FILES *.cpp)

# Generate respective executable for each .cpp file.
foreach(SRC_FILE ${SRC_FILES})
    # Get the name of the file without the extension.
    get_filename_component(EXEC_NAME ${SRC_FILE} NAME_WE)

    # Generate the executable.
    add_executable(${EXEC_NAME} ${SRC_FILE})

    # Link the executable with the library.
    target_link_libraries(${EXEC_NAME} ${LIB_NAME} pthread)

    # Set target CXX Standard C++20 and wall flag.
    target_compile_features(${EXEC_NAME} PRIVATE cxx_std_20)

    target_compile_options(${EXEC_NAME} PRIVATE -O3 -Wall -Werror)
endforeach(SRC_FILE ${SRC_FILES})

# Traverse the subdirecotry, and generate the executables with the same name of
# the subdirectory.

# Get all subdirectories.
file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

# Generate the executables for each subdirectory.
foreach(SUBDIR ${SUBDIRS})
    # Check if the subdirectory is a directory.
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR})
        # If the subdirectory is empty, create a main.cpp file.
        file(GLOB SUBDIR_FILES ${SUBDIR}/*.cpp)
        if(NOT SUBDIR_FILES)
            file(WRITE ${SUBDIR}/main.cpp "")
        endif()

        # # Generate the executable.
        # add_executable(${SUBDIR} ${SUBDIR}/${SUBDIR}.cpp)
        # Add all .cpp files in the subdirectory to the executable.
        file(GLOB_RECURSE SUBDIR_SRC_FILES ${SUBDIR}/*.cpp)

        add_executable(${SUBDIR} ${SUBDIR_SRC_FILES})

        # Link the executable with the library.
        target_link_libraries(${SUBDIR} ${LIB_NAME} pthread)

        # Set target CXX Standard C++20 and wall flag.
        target_compile_features(${SUBDIR} PRIVATE cxx_std_20)

        target_compile_options(${SUBDIR} PRIVATE -O3 -Wall -Werror)
    endif()
endforeach(SUBDIR ${SUBDIRS})

    