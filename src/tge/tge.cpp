#include "tge/tge.hpp"
#include "hdk/hdk.hpp"

#include "tge/impl/windows/tge_windows.hpp"
#include "tge/impl/linux/tge_linux.hpp"

namespace tge
{
	void initialise()
	{
		hdk::initialise();
		#ifdef _WIN32
			tge::impl::initialise_windows();
		#elif defined(__linux__)
			tge::impl::initialise_linux();	
		#endif
	}
	
	void terminate()
	{
		#ifdef _WIN32
			tge::impl::terminate_windows();
		#elif defined(__linux__)
			tge::impl::terminate_linux();	
		#endif
		hdk::terminate();
	}
}
