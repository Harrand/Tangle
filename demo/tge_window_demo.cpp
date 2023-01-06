#include "tge/tge.hpp"
#include "tge/window.hpp"
#include <gl/GL.h>

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
		}
	}
	tge::terminate();
}
