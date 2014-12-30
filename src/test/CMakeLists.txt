# cppunit test
add_executable(bOoMtest bOoM_test.cpp
		test__math2d.cpp
		test__shapes.cpp
		test__TiledArray.cpp
		test__color.cpp
		test__BitsetAllocator.cpp
	)
add_executable(bOoMenginetest bOoMengine_test.cpp
		test__Simulator.cpp
	)
target_link_libraries (bOoMtest m bOoM boost_unit_test_framework boost_prg_exec_monitor)
target_link_libraries (bOoMenginetest m bOoM bOoMengine boost_unit_test_framework boost_prg_exec_monitor)
add_test(bOoM ${EXECUTABLE_OUTPUT_PATH}/bOoMtest)
add_test(bOoMengine ${EXECUTABLE_OUTPUT_PATH}/bOoMenginetest)

add_executable(bOoMsandbox sandbox.cpp)
target_link_libraries (bOoMsandbox m bOoM bOoMengine)

