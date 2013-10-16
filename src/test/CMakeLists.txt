# cppunit test
add_executable(boomtest test.cpp)
target_link_libraries (boomtest m boom cppunit dl)
add_test(boomtest ${EXECUTABLE_OUTPUT_PATH}/boomtest)

