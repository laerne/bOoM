# cppunit test
#link_directories(${CMAKE_BINARY_DIR}/src/bOoM) #TODO a better way to fetch libboom output dir
add_library(bOoMengine SDLDisplayer.cpp)
target_link_libraries (bOoMengine m bOoM SDL2)

