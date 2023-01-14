#ifndef TANGLE_IMPL_LINUX_MONITOR_HPP
#define TANGLE_IMPL_LINUX_MONITOR_HPP 
#ifdef __linux__
#include "tge/api/monitor.hpp"
#include <vector>

namespace tge::impl
{
	std::vector<tge::monitor> get_monitors_linux();
}

#endif // __linux__
#endif // TANGLE_IMPL_LINUX_MONITOR_HPP
