# cppunit test
#link_directories(${CMAKE_BINARY_DIR}/src/bOoM) #TODO a better way to fetch libboom output dir
add_executable(boom_view main.cpp SimpleDisplayActor.cpp SimpleInputActor.cpp)
target_link_libraries (boom_view m boom SDL2 cppa)

