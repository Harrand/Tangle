#ifdef __linux__
#include "tge/impl/linux/tge_linux.hpp"
#include "hdk/debug.hpp"

namespace tge::impl
{
	static x11_display_data x11d = {};

	void initialise_linux()
	{
		x11d.display = XOpenDisplay(nullptr);
		hdk::assert(x11d.display != nullptr, "XOpenDisplay(nullptr) failed. Is an X-server not available?");
		x11d.screen = DefaultScreen(x11d.display);
		hdk::report("Initialised for Linux!");
	}

	void terminate_linux()
	{
		XCloseDisplay(x11d.display);
		x11d.display = nullptr;
		hdk::report("Terminated on Linux!");
	}

	x11_display_data& x11_display()
	{
		return x11d;
	}
}

#endif // __linux__
