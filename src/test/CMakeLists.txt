# cppunit test
add_executable(bOoMtest test.cpp)
target_link_libraries (bOoMtest m bOoM cppunit dl)
add_executable(bOoMsandbox sandbox.cpp)
target_link_libraries (bOoMsandbox m bOoM bOoMengine)
add_test(bOoMtest ${EXECUTABLE_OUTPUT_PATH}/bOoMtest)

