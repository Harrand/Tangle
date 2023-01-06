#ifndef TANGLE_WINDOW_HPP
#define TANGLE_WINDOW_HPP
#include "tge/impl/windows/window.hpp"

namespace tge
{
	#ifdef _WIN32
		using window = impl::window_winapi;
	#else
		static_assert(false, "Window Implementation does not seem to exist for this platform.");
	#endif
}

#endif // TANGLE_WINDOW_HPP
