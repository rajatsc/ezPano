cmake_minimum_required(VERSION 3.10)

#set the project name
project(ezPano
		DESCRIPTION "multi-threaded endoscopic stitching library"
		LANGUAGES CXX
		)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

#----- Set Build type -----
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")




#----- Set Compiler Flags ----
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")



#----- Find Dependencies -----
#OpenCV
find_package(OpenCV REQUIRED)
if (NOT OpenCV_FOUND)
	message(FATAL_ERROR "OpenCV not found")
endif()
message(STATUS "Use OpenCV ${OpenCV_VERSION}")

#yaml-cpp
find_package(yaml-cpp REQUIRED)
message("${YAML_CPP_INCLUDE_DIR}")
message("${YAML_CPP_LIBRARIES}")

if(false)
if (NOT yaml-cpp__FOUND)
	message(FATAL_ERROR "yaml-cpp not found")
endif()
message(STATUS "Use yaml-cpp ${YAML_CPP_VERSION}")
endif()


#opengl
find_package(OpenGL REQUIRED)

#glfw3
find_package(glfw3 3.2 REQUIRED)

#glew
find_package(GLEW REQUIRED)



########################################################
# include directories
########################################################
include_directories(${PROJECT_SOURCE_DIR}/include)


add_subdirectory(src)

#########################################################
# Examples
########################################################
option(BUILD_EXAMPLES "Build with examples" OFF)
if (${BUILD_EXAMPLES})
	add_subdirectory(examples)
endif()


###########################################################
# Tests
##########################################################

option(ENABLE_TESTS "Enable tests" OFF)
if (${ENABLE_TESTS})
	enable_testing()
	add_subdirectory(tests)
endif()


