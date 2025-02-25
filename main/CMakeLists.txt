add_executable(${CMAKE_PROJECT_NAME} WIN32
	main.cpp
	RenderWindow.h
	RenderWindow.cpp "boost_tests/TestTest.cpp")

add_subdirectory(common)
add_subdirectory(raytracer)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE common raytracer)

enable_testing()

add_subdirectory(google_tests)
add_subdirectory(boost_tests)

