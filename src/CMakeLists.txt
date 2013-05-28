#Search each main namespace
add_subdirectory(bOoM)
MESSAGE(STATUS ${CMAKE_INCLUDE_PATH})


#These source directories are roots for header files.
include_directories(bOoM)
#define executable
add_executable(boom_test main.cpp)

target_link_libraries (boom_test m boom)

#use C++11
list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -O0")
