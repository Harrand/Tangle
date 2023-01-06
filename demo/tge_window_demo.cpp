#include "tge/tge.hpp"
#include "tge/window.hpp"

int main()
{
	tge::initialise();
	{
		tge::window wnd
		{{
			.title = "Tangle Window Demo"
		}};
		while(!wnd.is_close_requested())
		{
			wnd.update();
		}
	}
	tge::terminate();
}
