#include "tge/tge.hpp"
#include "tge/window.hpp"
#include <array>

int main()
{
	tge::initialise();
	{
		constexpr std::size_t window_count = 8;
		std::array<tge::window_handle, window_count> windows;
		std::fill(windows.begin(), windows.end(), hdk::nullhand);
		for(std::size_t i = 0; i < window_count; i++)
		{
			windows[i] = tge::create_window({.title = std::to_string(i).c_str()});
		}
		auto is_active = [](tge::window_handle wh){return tge::has_window(wh) && !tge::get_window(wh).is_close_requested();};
		while(std::any_of(windows.begin(), windows.end(), is_active))
		{
			tge::update();
			for(std::size_t i = 0; i < window_count; i++)
			{
				if(is_active(windows[i]))
				{
					tge::get_window(windows[i]).update();
				}
			}
		}

		for(std::size_t i = 0; i < window_count; i++)
		{
			tge::destroy_window(windows[i]);
		}

	}
	tge::terminate();
}
