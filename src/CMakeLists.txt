#create ezPano library

message("Inside src directory")
add_library(${PROJECT_NAME}
            SHARED
			${CMAKE_CURRENT_SOURCE_DIR}/feeder.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/tracking.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/stitching.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/global_optimization.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/system.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/gui/gui.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/data/featureDatabase.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/data/mosaicDatabase.cpp
			)



# Set output directory of the library
set_target_properties(${PROJECT_NAME} PROPERTIES
                      OUTPUT_NAME ${PROJECT_NAME}
                      LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

message(STATUS ${OPENGL_INCLUDE_DIR})
message(STATUS ${OPENGL_gl_LIBRARY})
message(STATUS ${GLEW_LIBRARIES})

target_include_directories(${PROJECT_NAME}
							PUBLIC
							"${PROJECT_SOURCE_DIR}/include"
							${OPENGL_INCLUDE_DIR}
							"${CMAKE_CURRENT_SOURCE_DIR}/data"
							"${CMAKE_CURRENT_SOURCE_DIR}"
							)


#link to required libraries
target_link_libraries(${PROJECT_NAME}
						PUBLIC
						opencv_core
						opencv_features2d
						opencv_videoio
						opencv_highgui
						glfw
						${OPENGL_gl_LIBRARY}
						${GLEW_LIBRRIES}
						)

