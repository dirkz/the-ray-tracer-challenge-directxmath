add_library(raytracer OBJECT
	Ray.h
	Ray.cpp
	Tuple.h
	Intersectable.h
	Sphere.h
	Sphere.cpp)

target_include_directories(raytracer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(raytracer PRIVATE common)