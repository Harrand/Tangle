#include "tge/tge.hpp"
#include "tge/window.hpp"
#include "tge/keyboard.hpp"
#include "tge/monitor.hpp"

int main()
{
	tge::initialise();
	{
		tge::window_handle wnd = tge::create_window();
		auto mons = tge::get_monitors();
		volatile int x = 5;
		while(!tge::get_window(wnd).is_close_requested())
		{
				tge::update();
				tge::get_window(wnd).update();
		}
		tge::destroy_window(wnd);
	}
	tge::terminate();
}
