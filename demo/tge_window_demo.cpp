#include "tge/tge.hpp"
#include "tge/window.hpp"
#include "tge/keyboard.hpp"

int main()
{
	tge::initialise();
	{
		tge::window wnd
		{{
			.title = "Tangle Window Demo",
			.window_flags = tge::window_flag::opengl
		}};
		while(!wnd.is_close_requested())
		{
			wnd.update();
			const auto& keystate = wnd.get_keyboard_state();
			for(tge::key k : keystate.keys_down)
			{
				if(k != tge::key::unknown)
				{
					hdk::report("key \"%s\" pressed", tge::get_key_name(k).c_str());
				}
			}
		}
	}
	tge::terminate();
}
