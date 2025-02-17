add_executable(
  raytracer_tests
  RayTest.cpp)

target_link_libraries(
  raytracer_tests
  common
  raytracer
  gtest_main)

include(GoogleTest)
gtest_discover_tests(raytracer_tests)
