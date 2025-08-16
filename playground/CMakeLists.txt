# Scan all .cpp files in the current directory (non-recursive)
file(GLOB SRC_FILES *.cpp)

# Include the auto_main function
include(auto_main)

# Generate an executable for each .cpp file
foreach(SRC_FILE ${SRC_FILES})
    # Get the name of the file without the extension
    get_filename_component(EXEC_NAME ${SRC_FILE} NAME_WE)

    # Ensure each .cpp file has a unique main function with nested namespace if empty
    auto_main(${SRC_FILE})

    # Generate the executable
    add_executable(${EXEC_NAME} ${SRC_FILE})

    # Link the executable with the library
    # For multithreading support: link pthread on Unix-like systems (GCC/MinGW), not needed on MSVC/Windows
    target_link_threads(${EXEC_NAME})

    # Example: set target C++ standard or features, e.g. target_compile_features(${EXEC_NAME} PRIVATE cxx_std_17 cxx_lambdas)
    # target_compile_features(${EXEC_NAME} PRIVATE ...)

    # Example: add compile options, e.g. target_compile_options(${EXEC_NAME} PRIVATE -Wall -Wextra -O2)
    # target_compile_options(${EXEC_NAME} PRIVATE ...)
endforeach()