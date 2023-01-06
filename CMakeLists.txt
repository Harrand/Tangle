cmake_minimum_required(VERSION 3.23)

configure_file(version.txt version_txt_dummy.xml)
file(READ version.txt TGE_VERSION_TXT)
string(REGEX MATCH "[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+" TGE_VERSION ${TGE_VERSION_TXT})

project(tangle VERSION ${TGE_VERSION}
	DESCRIPTION "C++20 Windowing Library")

add_subdirectory(lib/HDK)

hdk_add_library(TARGET tangle
	SOURCES
	src/tge/tge.hpp
	src/tge/tge.cpp
	# tge api
	src/tge/api/window.hpp
	)
target_include_directories(tangle PUBLIC "${PROJECT_SOURCE_DIR}/src")

message(STATUS "Tangle v${TGE_VERSION}")
add_subdirectory(lib)
