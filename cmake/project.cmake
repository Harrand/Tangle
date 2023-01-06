include(CMakeParseArguments)

function(tge_add_library)
	cmake_parse_arguments(
		TGE_ADD_LIBRARY
		""
		"TARGET"
		"SOURCES"
		${ARGN}
	)

	hdk_base_add_library(
		TARGET ${TGE_ADD_LIBRARY_TARGET}
		BASE tangle
		SOURCES ${TGE_ADD_LIBRARY_SOURCES}
	)
endfunction()

function(tge_add_executable)
	cmake_parse_arguments(
		TGE_ADD_EXECUTABLE
		""
		"TARGET"
		"SOURCES"
		${ARGN}
	)

	hdk_base_add_executable(
		TARGET ${TGE_ADD_EXECUTABLE_TARGET}
		BASE tangle
		SOURCES ${TGE_ADD_EXECUTABLE_SOURCES}
	)
endfunction()
