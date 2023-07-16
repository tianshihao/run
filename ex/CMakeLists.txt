# Get names of all subdirectories. In CMake language.
file(GLOB subdirs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

# For each subdirectory...
foreach(subdir ${subdirs})
    # If it is a directory...
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${subdir})
        # ...add it to the list of subdirectories to process.
        list(APPEND subdirs_to_process ${subdir})
    endif()
endforeach()

# For each subdirectory to process...
foreach(subdir ${subdirs_to_process})
    # Check if it has not a main.cpp file in it.
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/main.cpp)
        # Create a main.cpp file in it. The main.cpp contains a simple
        # "Hello World" program.
        file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/main.cpp
            "#include <iostream>\n"
            "\n"
            "int main() {\n"
            "  std::cout << \"Hello World!\" << std::endl;\n"
            "  return 0;\n"
            "}\n"
        )
    endif()

    # Check if it has not a header file named ${subdir}.h in it.
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/${subdir}.h)
        # Create a header file named ${subdir}.h in it. The header file contains
        # a simple function declaration.
        file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/${subdir}.h
            "#pragma once\n"
        )
    endif()

    # Get all files in the subdirectory.
    file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${subdir} ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/*)

    # Remove main.cpp from the list of files.
    list(REMOVE_ITEM files main.cpp)

    # Get all files' absolute paths.
    foreach(file ${files})
        list(APPEND files_absolute_paths ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/${file})
    endforeach()

    # Create a shared library target for the subdirectory using files. The name
    # of the library is "ex_" plus the name of the subdirectory.
    add_library(ex_${subdir} SHARED ${files_absolute_paths})

    # Set library's language to C++.
    set_target_properties(ex_${subdir} PROPERTIES LINKER_LANGUAGE CXX)

    # Set files_absolute_paths to empty.
    set(files_absolute_paths "")

    # Then create an executable target for the subdirectory using main.cpp. The
    # name of the executable is "ex_" plus the name of the subdirectory.
    add_executable(ex_${subdir}_sample ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/main.cpp)

    # Set executable's language to C++.
    set_target_properties(ex_${subdir}_sample PROPERTIES LINKER_LANGUAGE CXX)

    # Link the executable target to the shared library target.
    target_link_libraries(ex_${subdir}_sample ex_${subdir})

endforeach()



