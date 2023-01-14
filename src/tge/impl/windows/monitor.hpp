#ifndef TANGLE_IMPL_WINDOWS_MONITOR_HPP
#define TANGLE_IMPL_WINDOWS_MONITOR_HPP
#ifdef _WIN32
#include "tge/api/monitor.hpp"

namespace tge::impl
{
	std::vector<tge::monitor> get_monitors_windows();
}

#endif // _WIN32
#endif // TANGLE_IMPL_WINDOWS_MONITOR_HPP
