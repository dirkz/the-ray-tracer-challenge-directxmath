add_library(raytracer OBJECT
	Ray.h
	Ray.cpp)

target_link_libraries(raytracer PRIVATE common)