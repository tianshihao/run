# Prepare for gtest.
include(GoogleTest)

set(TESTS_NAME_LIST
  blob_ptr_test
  blob_test
  find_test
  screen_test
  shared_ptr_test
  unique_ptr_test
  vec_test
)

foreach(TEST_NAME ${TESTS_NAME_LIST})
  message(STATUS "Configure test ${TEST_NAME} ...")

  add_executable(${TEST_NAME} ./${TEST_NAME}.cpp)

  target_compile_features(${TEST_NAME} PRIVATE cxx_std_17)
  target_compile_options(${TEST_NAME} PRIVATE -fPIC -Wall -Wno-deprecated-declarations)

  target_include_directories(${TEST_NAME}
    PRIVATE
    ${CMAKE_SOURCE_DIR}
  )

  target_link_libraries(${TEST_NAME}
    PRIVATE
    GTest::gtest
    GTest::gtest_main
  )

  gtest_discover_tests(${TEST_NAME})

  # install(TARGETS ${TEST_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/test)
endforeach()

# install(DIRECTORY test_data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})