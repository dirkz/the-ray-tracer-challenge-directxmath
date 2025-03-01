add_library(raytracer OBJECT
	Constants.h
	Ray.h
	Ray.cpp
	Vector.h
	Shape.h
	Shape.cpp
	Sphere.h
	Sphere.cpp
	Intersection.h
	Intersection.cpp
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
	Computations.cpp
	Camera.h
	Camera.cpp
	Canvas.h
	Canvas.cpp
	Render.h
	CoordinateProvider.h
	CoordinateProvider.cpp
	Plane.h
	Plane.cpp
	Pattern.h
	PerlinNoise.cpp
	PerlinNoise.h
	Cube.h
	Cube.cpp
	Cylinder.h
	Cylinder.cpp
	Cone.h
	Cone.cpp)

target_include_directories(raytracer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(raytracer PRIVATE common)