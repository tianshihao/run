PROJECT(cpp-primer)
CONFIGURE_PROJECT(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR} TARGET_LIST)

# A list of target.
# cpp-primer-chapter16
# cpp-primer-chapter15-query
# cpp-primer-chapter15-quote
message(STATUS ${PROJECT_NAME} " contains:")

foreach(target ${TARGET_LIST})
  message(STATUS ${target})
endforeach(target ${TARGET_LIST})
