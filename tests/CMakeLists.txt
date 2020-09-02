#-------- Build tests ---------
message("Inside tests")

link_libraries(${PROJECT_NAME})
include_directories(${PROJECT_SOURCE_DIR})

add_executable(test_bufferQueue test_bufferQueue.cpp)
add_test(tbufferQueue test_bufferQueue)

add_executable(test_feeder test_feeder.cpp)
add_test(tfeeder test_feeder)
