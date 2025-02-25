add_executable(gtests
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
  CameraTest.cpp
  RenderTest.cpp)

target_link_libraries(
  gtests
  common
  raytracer
  gtest_main)

include(GoogleTest)
gtest_discover_tests(gtests)
