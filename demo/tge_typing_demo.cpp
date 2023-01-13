#include "tge/tge.hpp"
#include "tge/window.hpp"
#include "tge/keyboard.hpp"
#include <cstdio>

int main()
{
	tge::initialise();
	{
		tge::window_handle wnd = tge::create_window({.title = "Tangle Typing Demo"});
		std::string msg = "";
		while(!tge::get_window(wnd).is_close_requested())
		{
			tge::update();
			tge::get_window(wnd).update();

			const auto& keystate = tge::get_window(wnd).get_keyboard_state();
			tge::key k = keystate.pop_last_key();
			if(k != tge::key::unknown)
			{
				std::string cur = tge::get_chars_typed(k, keystate);
				if(k == tge::key::enter)
				{
					msg = "";
				}
				else if(k == tge::key::backspace)
				{
					msg.pop_back();
				}
				else
				{
					msg += cur;
				}
				tge::get_window(wnd).set_title(msg);
			}
		}
	}
	tge::terminate();
}
