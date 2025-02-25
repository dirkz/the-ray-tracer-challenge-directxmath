add_executable(rt_boost_tests
  TestTest.cpp)

target_link_libraries(
  rt_boost_tests
  common
  raytracer
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

enable_testing()
add_test(NAME boost_tests COMMAND rt_boost_tests)
