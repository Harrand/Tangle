function(add_tge_test)
	cmake_parse_arguments(
		ADD_TGE_TEST
		""
		"NAME"
		"SOURCE_FILES"
		${ARGN}
		)

	hdk_base_add_test(
		TARGET ${ADD_TGE_TEST_NAME}
		BASE_NAME tge
		SOURCES ${ADD_TGE_TEST_SOURCE_FILES}
	)
endfunction()

hdk_base_add_test_harness(BASE_NAME tge)
add_dependencies(tgetest_build hdktest_build)

add_tge_test(NAME tge_initialise_test SOURCE_FILES tge_initialise_test.cpp)
