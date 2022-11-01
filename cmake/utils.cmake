# Find subdirectories of BASE_DIR norecursively.
MACRO(GET_SUBDIR_LIST BASE_DIR SUBDIR_LIST)
  FILE(GLOB ITEMS RELATIVE ${BASE_DIR} ${BASE_DIR}/*)
  SET(RESULT "")

  FOREACH(ITEM ${ITEMS})
    IF(IS_DIRECTORY ${BASE_DIR}/${ITEM})
      LIST(APPEND RESULT ${ITEM})

      # TODO, why can not using this?
      # LIST(APPEND SUBDIR_LIST ${ITEM})
    ENDIF()
  ENDFOREACH()

  SET(${SUBDIR_LIST} ${RESULT})
ENDMACRO(GET_SUBDIR_LIST BASE_DIR SUBDIR_LIST)

# Find all subdirectories in BASE_DIR that contains include and src recursively.
MACRO(GET_SUB_DIR_ABS_LIST_RECURSIVELY BASE_DIR SUB_DIR_ABS_LIST)
  # TODO, what if RELATIVE is changed into ABSOLUTE?
  FILE(GLOB SUB_DIRS RELATIVE ${BASE_DIR} ${BASE_DIR}/*)

  SET(SUB_DIR_ABS_NEED_TO_CHECK_LIST "")

  # Combine BASE_DIR and SUB_DIR_REL into SUB_DIR_ABS.
  FOREACH(SUB_DIR_REL ${SUB_DIRS})
    SET(SUB_DIR_ABS ${BASE_DIR}/${SUB_DIR_REL})

    IF(IS_DIRECTORY ${SUB_DIR_ABS})
      LIST(APPEND SUB_DIR_ABS_NEED_TO_CHECK_LIST ${SUB_DIR_ABS})
    ENDIF()
  ENDFOREACH()

  # While check list is not empty.
  WHILE(SUB_DIR_ABS_NEED_TO_CHECK_LIST)
    # Check every absolute subdir.
    FOREACH(SUB_DIR_ABS ${SUB_DIR_ABS_NEED_TO_CHECK_LIST})
      GET_SUBDIR_LIST(${SUB_DIR_ABS} DIRS_IN_SUB_DIR)

      # If it contains include and src, which is we want.
      # e.g. /root/source/repos/run/replica/cpp-primer/chapter15/query
      # or /root/source/repos/run/replica/cpp-primer/chapter16 both contain
      # include and src.
      IF("include" IN_LIST DIRS_IN_SUB_DIR AND "src" IN_LIST DIRS_IN_SUB_DIR)
        # MESSAGE(STATUS "FIND EXECUTABLE IN: " ${SUB_DIR_ABS})
        LIST(APPEND SUB_DIR_ABS_LIST ${SUB_DIR_ABS})

      # Else check its subdirs.
      # e.g. /root/source/repos/run/replica/cpp-primer/chapter15, then find
      # its subdirectory.
      ELSE()
        # Join every subdir into check list.
        FOREACH(DIR ${DIRS_IN_SUB_DIR})
          SET(DIR_PATH ${SUB_DIR_ABS}/${DIR})

          # e.g. /root/source/repos/run/replica/cpp-primer/chapter15/query
          LIST(APPEND SUB_DIR_ABS_NEED_TO_CHECK_LIST ${DIR_PATH})
        ENDFOREACH()
      ENDIF()

      # Remove item we checked.
      LIST(REMOVE_ITEM SUB_DIR_ABS_NEED_TO_CHECK_LIST ${SUB_DIR_ABS})
    ENDFOREACH()
  ENDWHILE(SUB_DIR_ABS_NEED_TO_CHECK_LIST)
ENDMACRO(GET_SUB_DIR_ABS_LIST_RECURSIVELY BASE_DIR SUB_DIR_ABS_LIST)

MACRO(GENERATE_TARGET_NAME BASE_DIRECTORY SUB_DIR_ABS_NEED_TO_CHECK_LIST TARGET_NAME_LIST)
  SET(RESULT "")

  # BASE_DIRECTORY: /root/source/repos/run/replica/cpp-primer

  # TARGET_NAME_BASE: cpp-primer
  GET_FILENAME_COMPONENT(TARGET_NAME_BASE ${BASE_DIRECTORY} NAME)

  # SUB_DIR_ABS
  # /root/source/repos/run/replica/cpp-primer/chapter15/quote
  # SUB_DIR_ABS - BASE_DIRECTORY
  # chapter15/quote
  # Then transfer it into chapter15-quote
  # Final get TARGET_NAME_BASE-chapter15-quote = cpp-primer-chapter15-quote
  # This is the target name we want.
  FOREACH(SUB_DIR_ABS ${SUB_DIR_ABS_NEED_TO_CHECK_LIST})
    # DROP THE PART OF BASE_DIRECTORY OF SUB_DIR_ABS
    STRING(REPLACE ${BASE_DIRECTORY} "" SUB_DIR_NO_PREFIX ${SUB_DIR_ABS})

    SET(TARGET_NAME ${TARGET_NAME_BASE}${SUB_DIR_NO_PREFIX})

    # TARGET_NAME: cpp-primer-chapter15-quote
    STRING(REPLACE "/" "-" TARGET_NAME ${TARGET_NAME})

    LIST(APPEND TARGET_NAME_LIST ${TARGET_NAME})
  ENDFOREACH(SUB_DIR_ABS ${SUB_DIR_ABS_NEED_TO_CHECK_LIST})
ENDMACRO(GENERATE_TARGET_NAME BASE_DIRECTORY SUB_DIR_ABS_NEED_TO_CHECK_LIST TARGET_NAME_LIST)

# MACRO(CONFIGURE_PROJECT PROJECT_NAME PROJECT_CMAKE_LIST_DIR TARGET_LIST INCLUDE_DIRS)
MACRO(CONFIGURE_PROJECT PROJECT_NAME PROJECT_CMAKE_LIST_DIR TARGET_LIST)
  MESSAGE(STATUS "CONFIGURING ${PROJECT_NAME}...")
  GET_SUB_DIR_ABS_LIST_RECURSIVELY(${PROJECT_CMAKE_LIST_DIR} SUB_DIR_ABS_LIST)

  FOREACH(SUB_DIR_ABS ${SUB_DIR_ABS_LIST})
    MESSAGE(STATUS "SUB_DIR_ABS: ${SUB_DIR_ABS}")
  ENDFOREACH(SUB_DIR_ABS ${SUB_DIR_ABS_LIST})

  GENERATE_TARGET_NAME(${PROJECT_CMAKE_LIST_DIR} "${SUB_DIR_ABS_LIST}" TARGET_NAME_LIST)

  FOREACH(IT ${TARGET_NAME_LIST})
    MESSAGE(STATUS "TARGET: ${IT}")
  ENDFOREACH(IT ${TARGET_NAME_LIST})

  LIST(LENGTH SUB_DIR_ABS_LIST LENGTH1)
  MATH(EXPR LENGTH2 "${LENGTH1} - 1")

  FOREACH(VAL RANGE ${LENGTH2})
    LIST(GET SUB_DIR_ABS_LIST ${VAL} SUB_DIR_ABS)
    LIST(GET TARGET_NAME_LIST ${VAL} TARGET_NAME)
    MESSAGE(STATUS "Pair\n${SUB_DIR_ABS}:${TARGET_NAME}")

    SET(SOURCE_FILES "")
    AUX_SOURCE_DIRECTORY(${SUB_DIR_ABS}/src SOURCE_FILES)

    ADD_EXECUTABLE(${TARGET_NAME} ${SOURCE_FILES})

    IF(MSVC)
      # warning level 4 and all warnings as errors
      ADD_COMPILE_OPTIONS(/W4 /WX)
    ELSE()
      # lots of warnings and all warnings as errors
      ADD_COMPILE_OPTIONS(-Wall -Wextra -pedantic -Werror)
      MESSAGE(STATUS "WARNING OPTIONS: -Wall -Wextra -pedantic -Werror")
    ENDIF()

    TARGET_COMPILE_FEATURES(${TARGET_NAME} PRIVATE cxx_std_17)

    # SETTING INCLUDE DIRECTORY AND LINKING.
    TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} PUBLIC ${SUB_DIR_ABS}/include
      PUBLIC ${CMAKE_SOURCE_DIR}/utils)
    message(STATUS "aaaaaaaaaaaaaaaaaaaaa" ${SUB_DIR_ABS}/include)
    INCLUDE_DIRECTORIES(${SUB_DIR_ABS}/include)
    TARGET_LINK_LIBRARIES(${TARGET_NAME} PUBLIC run-utils)

    LIST(APPEND TARGET_LIST ${TARGET_NAME})
  ENDFOREACH(VAL RANGE ${LENGTH2})
ENDMACRO(CONFIGURE_PROJECT PROJECT_NAME PROJECT_CMAKE_LIST_DIR TARGET_LIST)
