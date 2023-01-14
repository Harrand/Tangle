#ifdef __linux__
#include "tge/impl/linux/monitor.hpp"
#include "tge/impl/linux/tge_linux.hpp"
#include <X11/extensions/Xrandr.h>

namespace tge::impl
{
	std::vector<tge::monitor> get_monitors_linux()
	{
		auto x11d = impl::x11_display().display;
		std::vector<tge::monitor> ret;
		XRRScreenResources* resources = XRRGetScreenResourcesCurrent(x11d, DefaultRootWindow(x11d));
		for(int i = 0; i < resources->noutput; i++)
		{
			XRROutputInfo* out_info = XRRGetOutputInfo(x11d, resources, resources->outputs[i]);
			XRRCrtcInfo* crtc = XRRGetCrtcInfo(x11d, resources, out_info->crtc);
			ret.push_back
			({
				.name = std::string("Monitor ") + std::to_string(i),
				.dimensions = {crtc->width, crtc->height}
			});
		}
		return ret;
	}
}

#endif // __linux__
