add_executable(
  hello_test
  HelloTest.cpp)

target_link_libraries(
  hello_test
  raytracer
  gtest_main)

include(GoogleTest)
gtest_discover_tests(hello_test)
