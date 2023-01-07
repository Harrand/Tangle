#include "tge/tge.hpp"
#include "tge/window.hpp"
#include "tge/keyboard.hpp"
#include <cstdio>

int main()
{
	tge::initialise();
	{
		tge::window wnd
		{{
			.title = "Tangle Typing Demo"
		}};
		std::string msg = "";
		while(!wnd.is_close_requested())
		{
			wnd.update();
			const auto& keystate = wnd.get_keyboard_state();
			tge::key k = keystate.get_last_key();
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
				std::printf("%s               \r", msg.c_str());
			}
		}
	}
	tge::terminate();
}
