# Find subdirectories of BASEDIR_ABSPATH norecursively.
# BASEDIR_ABSPATH: /root/source/repos/run/replica/cpp-primer/chapter15
macro(GET_SUBDIR_LIST BASEDIR_ABSPATH SUBDIR_LIST)
  file(GLOB ENTRIES RELATIVE ${BASEDIR_ABSPATH} ${BASEDIR_ABSPATH}/*)
  set(RESULT "")

  foreach(ENTRY ${ENTRIES})
    if(IS_DIRECTORY ${BASEDIR_ABSPATH}/${ENTRY})
      list(APPEND RESULT ${ENTRY})

      # TODO, why can not using this?
      # list(APPEND SUBDIR_LIST ${ENTRY})
    endif()
  endforeach()

  set(${SUBDIR_LIST} ${RESULT})
endmacro(GET_SUBDIR_LIST BASEDIR_ABSPATH SUBDIR_LIST)

# Find all subdirectories in BASEDIR_ABSPATH that contains include and src recursively.
# BASEDIR_ABSPATH: /root/source/repos/run/replica/cpp-primer
macro(GET_SUBDIR_ABSPATH_LIST_RECURSIVELY BASEDIR_ABSPATH SUBDIR_ABSPATH_LIST)
  # SUBDIR_RELPATH_LIST: chapter15; chapter16
  file(GLOB SUBDIR_RELPATH_LIST RELATIVE ${BASEDIR_ABSPATH} ${BASEDIR_ABSPATH}/*)

  set(SUBDIR_ABSPATH_NEED_TO_CHECK_LIST "")

  # Combine BASEDIR_ABSPATH and SUBDIR_RELPATH into SUBDIR_ABSPATH.
  # ${SUBDIR_RELPATH}: chapter15
  foreach(SUBDIR_RELPATH ${SUBDIR_RELPATH_LIST})
    # SUBDIR_ABSPATH: /root/source/repos/run/replica/cpp-primer/chapter15;
    # /root/source/repos/run/replica/cpp-primer/chapter16
    set(SUBDIR_ABSPATH ${BASEDIR_ABSPATH}/${SUBDIR_RELPATH})

    if(IS_DIRECTORY ${SUBDIR_ABSPATH})
      list(APPEND SUBDIR_ABSPATH_NEED_TO_CHECK_LIST ${SUBDIR_ABSPATH})
    endif()
  endforeach()

  # While check list is not empty.
  # SUBDIR_ABSPATH_NEED_TO_CHECK_LIST: /root/source/repos/run/replica/cpp-primer/chapter15;
  # /root/source/repos/run/replica/cpp-primer/chapter16
  while(SUBDIR_ABSPATH_NEED_TO_CHECK_LIST)
    # Check every absolute subdir.
    foreach(SUBDIR_ABSPATH ${SUBDIR_ABSPATH_NEED_TO_CHECK_LIST})
      # SUBDIR_ABSPATH: /root/source/repos/run/replica/cpp-primer/chapter15
      # DIRNAME_IN_SUBDIR_ABSPATH: query; qoute
      # SUBDIR_ABSPATH: /root/source/repos/run/replica/cpp-primer/chapter16
      # DIRNAME_IN_SUBDIR_ABSPATH:
      GET_SUBDIR_LIST(${SUBDIR_ABSPATH} DIRNAME_IN_SUBDIR_ABSPATH)

      # If DIRNAME_IN_SUBDIR_ABSPATH is empty then find main.cpp in it or touch main.cpp.
      if(NOT DIRNAME_IN_SUBDIR_ABSPATH)
        # TODO: Check main.cpp
        list(APPEND SUBDIR_ABSPATH_LIST ${SUBDIR_ABSPATH})

      # Else find subdir in the DIRNAME_IN_SUBDIR_ABSPATH and append them into check list.
      else()
        # Join every subdir into check list.
        foreach(DIRNAME ${DIRNAME_IN_SUBDIR_ABSPATH})
          set(DIR_PATH ${SUBDIR_ABSPATH}/${DIRNAME})

          # e.g. /root/source/repos/run/replica/cpp-primer/chapter15/query
          list(APPEND SUBDIR_ABSPATH_NEED_TO_CHECK_LIST ${DIR_PATH})
        endforeach()
      endif()

      # Remove item we checked.
      list(REMOVE_ITEM SUBDIR_ABSPATH_NEED_TO_CHECK_LIST ${SUBDIR_ABSPATH})
    endforeach()
  endwhile(SUBDIR_ABSPATH_NEED_TO_CHECK_LIST)

  FORMAT_MESSAGE_LIST(SUBDIR_ABSPATH_LIST)
endmacro()

macro(GENERATE_TARGET_NAME MODULE_CMAKE_LIST_DIR SUBDIR_ABSPATH_LIST TARGET_NAME_LIST)
  set(RESULT "")

  # MODULE_CMAKE_LIST_DIR: /root/source/repos/run/replica/cpp-primer

  # TARGET_NAME_BASE: cpp-primer
  GET_FILENAME_COMPONENT(TARGET_NAME_BASE ${MODULE_CMAKE_LIST_DIR} NAME)

  # SUBDIR_ABSPATH
  # /root/source/repos/run/replica/cpp-primer/chapter15/quote
  # SUBDIR_ABSPATH - MODULE_CMAKE_LIST_DIR
  # chapter15/quote
  # Then transfer it into chapter15-quote
  # Final get TARGET_NAME_BASE-chapter15-quote = cpp-primer-chapter15-quote
  # This is the target name we want.
  foreach(SUBDIR_ABSPATH ${SUBDIR_ABSPATH_LIST})
    # DROP THE PART OF MODULE_CMAKE_LIST_DIR OF SUBDIR_ABSPATH
    string(REPLACE ${MODULE_CMAKE_LIST_DIR} "" SUB_DIR_NO_PREFIX ${SUBDIR_ABSPATH})

    set(TARGET_NAME ${TARGET_NAME_BASE}${SUB_DIR_NO_PREFIX})

    # TARGET_NAME: cpp-primer-chapter15-quote
    string(REPLACE "/" "_" TARGET_NAME ${TARGET_NAME})

    list(APPEND TARGET_NAME_LIST ${TARGET_NAME})
  endforeach(SUBDIR_ABSPATH ${SUBDIR_ABSPATH_LIST})

  FORMAT_MESSAGE_LIST(TARGET_NAME_LIST)
endmacro(GENERATE_TARGET_NAME MODULE_CMAKE_LIST_DIR SUBDIR_ABSPATH_LIST TARGET_NAME_LIST)

# Output list in a pretty way. MESSAGE_LIST is a list.
macro(FORMAT_MESSAGE_LIST list_name)
  list(LENGTH ${list_name} list_length)

  if(${list_length} GREATER 0)
    list(GET ${list_name} 0 first_item)

    # message(STATUS "${list_name}: ${first_item}")
    math(EXPR list_length "${list_length} - 1")

    foreach(index RANGE ${list_length})
      list(GET ${list_name} ${index} item)
      message(STATUS "           ${item}")
    endforeach()
  endif()
endmacro()

# MODULE_NAME: cpp-primer
# MODULE_CMAKE_LIST_DIR: /root/source/repos/run/replica/cpp-primer
macro(CONFIGURE_MODULE MODULE_NAME MODULE_CMAKE_LIST_DIR TARGET_LIST)
  message(STATUS "Configuring ${MODULE_NAME}...")

  GET_SUBDIR_ABSPATH_LIST_RECURSIVELY(${MODULE_CMAKE_LIST_DIR} SUBDIR_ABSPATH_LIST)

  GENERATE_TARGET_NAME(${MODULE_CMAKE_LIST_DIR} "${SUBDIR_ABSPATH_LIST}" TARGET_NAME_LIST)

  list(LENGTH SUBDIR_ABSPATH_LIST LENGTH1)
  math(EXPR LENGTH2 "${LENGTH1} - 1")

  message(STATUS "Target localtion:Target")

  foreach(VAL RANGE ${LENGTH2})
    list(GET SUBDIR_ABSPATH_LIST ${VAL} SUBDIR_ABSPATH)
    list(GET TARGET_NAME_LIST ${VAL} TARGET_NAME)
    message(STATUS ${SUBDIR_ABSPATH}:${TARGET_NAME})

    # set(SOURCE_FILES "")
    # aux_source_directory(${SUBDIR_ABSPATH} SOURCE_FILES)
    # find all .cpp, .hpp, .h files except for main.cpp in ${SUBDIR_ABSPATH} and add them into SOURCE_FILES.
    file(GLOB_RECURSE SOURCE_FILES ${SUBDIR_ABSPATH}/*.cpp ${SUBDIR_ABSPATH}/*.hpp ${SUBDIR_ABSPATH}/*.h)
    list(REMOVE_ITEM SOURCE_FILES ${SUBDIR_ABSPATH}/main.cpp)

    FORMAT_MESSAGE_LIST(SOURCE_FILES)

    # Set library name as lib + TARGET_NAME.
    set(LIBRARY_NAME lib${TARGET_NAME})

    # if SOURCE_FILES is not empty then add it into library
    if(SOURCE_FILES)
      add_library(${LIBRARY_NAME} STATIC ${SOURCE_FILES})
      set_target_properties(${LIBRARY_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
      set_target_properties(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)

      if(MSVC)
        # Warning level 4 and all warnings as errors.
        add_compile_options(/W4 /WX)
      else()
        # Lots of warnings and all warnings as errors.
        add_compile_options(-Wall -Wextra -pedantic -Werror)
      endif()

      target_compile_features(${LIBRARY_NAME} PRIVATE cxx_std_17)

      # SETTING INCLUDE DIRECTORY AND LINKING.
      target_include_directories(${LIBRARY_NAME} PUBLIC ${SUBDIR_ABSPATH}/include
        PUBLIC ${CMAKE_SOURCE_DIR}/utils)

      list(APPEND TARGET_LIST ${LIBRARY_NAME})
    endif()

    # Set executable name as TARGET_NAME.
    set(EXECUTABLE_NAME ${TARGET_NAME})

    # if there is a main.cpp then add it into executable.
    file(GLOB_RECURSE MAIN_CPP ${SUBDIR_ABSPATH}/main.cpp)

    # if MAIN_CPP is empty then touch one.
    if(NOT MAIN_CPP)
      message(STATUS "No main.cpp in ${SUBDIR_ABSPATH}, touch one...")
      set(MAIN_CPP ${SUBDIR_ABSPATH}/main.cpp)
      file(WRITE ${MAIN_CPP} "")
    endif()

    add_executable(${EXECUTABLE_NAME} ${MAIN_CPP})

    if(MSVC)
      # Warning level 4 and all warnings as errors.
      add_compile_options(/W4 /WX)
    else()
      # Lots of warnings and all warnings as errors.
      add_compile_options(-Wall -Wextra -pedantic -Werror)
    endif()

    target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)

    set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

    # SETTING INCLUDE DIRECTORY AND LINKING.
    target_include_directories(${EXECUTABLE_NAME} PUBLIC ${SUBDIR_ABSPATH}/include
      PUBLIC ${CMAKE_SOURCE_DIR}/utils)

    list(APPEND TARGET_LIST ${EXECUTABLE_NAME})
  endforeach(VAL RANGE ${LENGTH2})

  FORMAT_MESSAGE_LIST(TARGET_LIST)
endmacro(CONFIGURE_MODULE MODULE_NAME MODULE_CMAKE_LIST_DIR TARGET_LIST)
