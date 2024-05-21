find_package(GTest REQUIRED)
target_link_libraries(GTest::gtest INTERFACE gtest_main)

SET(MyTests 
  files_test
  strings_test
  grid_test
  print_test
  search_test
  neighbours_test
  path_test
)

foreach(test IN LISTS MyTests)
  add_executable(${test} ${test}.cpp ../src/aocutils.h)
  target_link_libraries(${test} GTest::gtest)
  string(REPLACE "_test" "" name ${test})
  add_test(${name} ${test})
endforeach()


file(GLOB files ./resource/*)
foreach(item ${files})
  message(STATUS ${item})
  FILE(COPY ${item} DESTINATION "${CMAKE_BINARY_DIR}/test/resource")
endforeach()