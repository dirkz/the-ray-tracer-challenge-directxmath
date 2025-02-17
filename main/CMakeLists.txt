add_executable(${CMAKE_PROJECT_NAME} WIN32
	main.cpp)

add_subdirectory(common)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE common)

enable_testing()

add_subdirectory(tests)

