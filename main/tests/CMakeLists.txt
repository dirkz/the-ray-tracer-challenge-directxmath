add_executable(rt_tests
  TestConstants.h
  TestUtil.h
  RayTest.cpp
  SphereTest.cpp
  CubeTest.cpp
  IntersectionTest.cpp
  TransformationTest.cpp
  VectorTest.cpp
  LightTest.cpp
  MaterialTest.cpp
  WorldTest.cpp
  CameraTest.cpp
  RenderTest.cpp
  CylinderTest.cpp
  ConeTest.cpp
  GroupTest.cpp
  ShapeTest.cpp
  TriangleTest.cpp)

target_link_libraries(
  rt_tests
  common
  raytracer
  gtest_main)

include(GoogleTest)
gtest_discover_tests(rt_tests)
