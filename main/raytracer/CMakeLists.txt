add_library(raytracer OBJECT
	Ray.h
	Ray.cpp
	Tuple.h)

target_link_libraries(raytracer PRIVATE common)