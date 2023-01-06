#include "tge/tge.hpp"
#include "hdk/hdk.hpp"

#include "tge/impl/windows/tge_windows.hpp"

namespace tge
{
	void initialise()
	{
		hdk::initialise();
		if constexpr(tge::get_platform() == tge::platform::windows)
		{
			tge::impl::initialise_windows();
		}
	}
	
	void terminate()
	{
		if constexpr(tge::get_platform() == tge::platform::windows)
		{
			tge::impl::terminate_windows();
		}
		hdk::terminate();
	}
}
