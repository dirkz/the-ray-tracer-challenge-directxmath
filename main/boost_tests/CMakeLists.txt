add_executable(rt_boost_tests
  TestTest.cpp)

target_link_libraries(
  rt_boost_tests
  common
  raytracer
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

