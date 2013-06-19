# cppunit test
add_executable(boomtest main.cpp)
target_link_libraries (boomtest m boom cppunit dl)

# Use C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -O0")

