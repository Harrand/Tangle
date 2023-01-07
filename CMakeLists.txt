cmake_minimum_required(VERSION 3.23)

configure_file(version.txt version_txt_dummy.xml)
file(READ version.txt TGE_VERSION_TXT)
string(REGEX MATCH "[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+" TGE_VERSION ${TGE_VERSION_TXT})

project(tangle VERSION ${TGE_VERSION}
	DESCRIPTION "C++20 Windowing Library")
include(cmake/platform.cmake)
include(cmake/project.cmake)

add_subdirectory(lib/HDK)

hdk_add_library(TARGET tangle
	SOURCES
	src/tge/keyboard.cpp
	src/tge/keyboard.hpp
	src/tge/tge.hpp
	src/tge/tge.cpp
	src/tge/window.hpp
	# tge api
	src/tge/api/keyboard.hpp
	src/tge/api/mouse.hpp
	src/tge/api/window.hpp
	# tge impl (windows)
	src/tge/impl/windows/detail/winapi.hpp
	src/tge/impl/windows/keyboard.cpp
	src/tge/impl/windows/keyboard.hpp
	src/tge/impl/windows/keyboard.inl
	src/tge/impl/windows/tge_windows.cpp
	src/tge/impl/windows/tge_windows.hpp
	src/tge/impl/windows/window.cpp
	src/tge/impl/windows/window.hpp
	)
target_include_directories(tangle PUBLIC "${PROJECT_SOURCE_DIR}/src")
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
	configure_windows(tangle)
endif()

message(STATUS "Tangle v${TGE_VERSION}")
add_subdirectory(lib)

add_subdirectory(demo)
enable_testing()
add_subdirectory(test)
