add_library(raytracer OBJECT
	Ray.h
	Ray.cpp
	Vector.h
	Intersectable.h
	Sphere.h
	Sphere.cpp
	Intersection.h
	Intersection.cpp
	Intersectable.cpp
	Vector.cpp
	Matrix.h
	Matrix.cpp
	PointLight.h
	PointLight.cpp
	Material.h
	Material.cpp
	World.h
	World.cpp
	Computations.h
	Computations.cpp)

target_include_directories(raytracer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(raytracer PRIVATE common)