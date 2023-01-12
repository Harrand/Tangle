#ifndef TANGLE_IMPL_LINUX_TGE_LINUX_HPP
#define TANGLE_IMPL_LINUX_TGE_LINUX_HPP
#ifdef __linux__
#include <X11/Xlib.h>

namespace tge::impl
{
	void initialise_linux();
	void terminate_linux();
}

#endif // __linux__
#endif // TANGLE_IMPL_LINUX_TGE_LINUX_HPP
