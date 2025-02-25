add_executable(rt_google_tests
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
  rt_google_tests
  common
  raytracer
  gtest_main)

include(GoogleTest)
gtest_discover_tests(rt_google_tests)
