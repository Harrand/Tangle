#include "tge/monitor.hpp"
#include "tge/impl/windows/monitor.hpp"
#include "tge/impl/linux/monitor.hpp"

namespace tge
{
	std::vector<tge::monitor> get_monitors()
	{
		#ifdef _WIN32
			return impl::get_monitors_windows();
		#elif defined(__linux__)
			return impl::get_monitors_linux();
		#else
			static_assert(false);
			return {};
		#endif
	}
}
