add_executable(
  raytracer_tests
  TestConstants.h
  RayTest.cpp
  SphereTest.cpp
  IntersectionTest.cpp
  TransformationTest.cpp
  VectorTest.cpp)

target_link_libraries(
  raytracer_tests
  common
  raytracer
  gtest_main)

include(GoogleTest)
gtest_discover_tests(raytracer_tests)
