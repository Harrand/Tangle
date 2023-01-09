add_subdirectory(glad)

tge_add_executable(TARGET tge_typing_demo SOURCES tge_typing_demo.cpp)
tge_add_executable(TARGET tge_window_demo SOURCES tge_window_demo.cpp)

tge_add_executable(TARGET tge_opengl_demo SOURCES tge_opengl_demo.cpp)
target_link_libraries(tge_opengl_demo PRIVATE glad)
