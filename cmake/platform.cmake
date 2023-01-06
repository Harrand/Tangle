function(configure_windows target)
	message(WARNING "Support for Windows is not yet fully implemented")
	target_link_libraries(${target} PUBLIC OpenGL32 dwmapi)
endfunction()
