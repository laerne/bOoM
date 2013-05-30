# Set environment
include_directories(${CMAKE_SOURCE_DIR})

# Old test that printed expressions to stdout~:
add_executable(old_stdout_test old_stdout_test.cpp)
target_link_libraries (old_stdout_test m boom)

# New cppunit test
add_executable(boomtest test__math2d.cpp)
target_link_libraries (boomtest m boom cppunit dl)

# Use C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -O0")

