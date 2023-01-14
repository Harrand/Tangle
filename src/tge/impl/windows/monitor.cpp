#ifdef _WIN32
#include "tge/impl/windows/monitor.hpp"
#include "tge/impl/windows/detail/winapi.hpp"

namespace tge::impl
{
	BOOL CALLBACK mon_enum_proc(HMONITOR hmon, HDC hdcmon, LPRECT lprcmon, LPARAM dwdata)
	{
		auto mons = reinterpret_cast<std::vector<tge::monitor>*>(dwdata);
		MONITORINFOEXA minfo;
		minfo.cbSize = sizeof(MONITORINFOEXA);
		GetMonitorInfo(hmon, &minfo);
		hdk::vec2i dims{minfo.rcMonitor.right - minfo.rcMonitor.left, minfo.rcMonitor.bottom - minfo.rcMonitor.top};
		mons->push_back
		({
			.name = minfo.szDevice,
			.dimensions = static_cast<hdk::vec2ui>(dims)
		});
		return TRUE;
	}
	std::vector<tge::monitor> get_monitors_windows()
	{
		std::vector<tge::monitor> mons;
		EnumDisplayMonitors(nullptr, nullptr, mon_enum_proc, reinterpret_cast<LPARAM>(&mons));
		return mons;
	}
}

#endif // _WIN32
