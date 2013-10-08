# cppunit test
add_executable(boomtest test.cpp)
target_link_libraries (boomtest m boom cppunit dl)
add_test(boomtest ${EXECUTABLE_OUTPUT_PATH}/boomtest)

# Use C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -O0")

