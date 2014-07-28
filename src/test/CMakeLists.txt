# cppunit test
add_executable(bOoMtest test.cpp
		test__math2d.cpp
		test__shapes.cpp
		test__TiledArray.cpp
		test__color.cpp
		test__BitsetAllocator.cpp
		test__Simulator.cpp
	)
target_link_libraries (bOoMtest m bOoM bOoMengine boost_unit_test_framework boost_prg_exec_monitor)
add_test(bOoMtest ${EXECUTABLE_OUTPUT_PATH}/bOoMtest)

add_executable(bOoMsandbox sandbox.cpp)
target_link_libraries (bOoMsandbox m bOoM bOoMengine)

