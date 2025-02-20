add_executable(raytracer_tests
  TestConstants.h
  TestUtil.h
  RayTest.cpp
  SphereTest.cpp
  IntersectionTest.cpp
  TransformationTest.cpp
  VectorTest.cpp
  LightTest.cpp
  MaterialTest.cpp
  WorldTest.cpp
  CameraTest.cpp)

target_link_libraries(
  raytracer_tests
  common
  raytracer
  gtest_main)

include(GoogleTest)
gtest_discover_tests(raytracer_tests)
