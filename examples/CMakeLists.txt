# ----- Build example executables -----
message("Inside examples")

set(EXECUTABLE_TARGETS "")

add_executable(main main.cpp)
list(APPEND EXECUTABLE_TARGETS main)

add_executable(video video.cpp)
list(APPEND EXECUTABLE_TARGETS video)


foreach(EXECUTABLE_TARGET IN LISTS EXECUTABLE_TARGETS)
	#set output directory for executables


	target_link_libraries(${EXECUTABLE_TARGET}
							PRIVATE
							${PROJECT_NAME}
							opencv_core
							opencv_videoio
							opencv_highgui
							glfw
							${OPENGL_gl_LIBRARY}
							${GLEW_LIBRARIES})
endforeach()


