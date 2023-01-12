#ifndef TANGLE_WINDOW_HPP
#define TANGLE_WINDOW_HPP
#include "tge/impl/windows/window.hpp"
#include "tge/impl/linux/window.hpp"

namespace tge
{
	#ifdef _WIN32
		using window = impl::window_winapi;
		inline void* get_opengl_proc_address(const char* name)
		{
			return impl::get_opengl_proc_address_windows(name);
		}
	#elif defined(__linux__)
		using window = impl::window_x11;
		inline void* get_opengl_proc_address(const char* name)
		{
			return nullptr;
		}
	#else
		static_assert(false, "Window Implementation does not seem to exist for this platform.");
	#endif
}

#endif // TANGLE_WINDOW_HPP
