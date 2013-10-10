# cppunit test
add_executable(boom_view main.cpp display.cpp)
target_link_libraries (boom_view m boom SDL2)

# Use C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -O0 -Wall -W")

