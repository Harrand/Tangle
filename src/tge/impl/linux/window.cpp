#ifdef __linux__
#include "tge/impl/linux/window.hpp"
#include <X11/Xatom.h>

namespace tge::impl
{
	window_x11::window_x11(window_info info)
	{
		const x11_display_data x11d = impl::x11_display();
		this->wnd = XCreateSimpleWindow(x11d.display, RootWindow(x11d.display, x11d.screen), 0, 0, info.dimensions[0], info.dimensions[1], 1, BlackPixel(x11d.display, x11d.screen), WhitePixel(x11d.display, x11d.screen));
		this->set_title(info.title);
		XSelectInput(x11d.display, this->wnd, ExposureMask | KeyPressMask);
		XMapWindow(x11d.display, this->wnd);

		Atom protocols[] = {XInternAtom(x11d.display, "WM_DELETE_WINDOW", False)};
		XSetWMProtocols(x11d.display, this->wnd, protocols, sizeof(protocols) / sizeof(Atom));
	}

	window_x11::~window_x11()
	{
		if(this->wnd != -1)
		{
			this->request_close();
			this->wnd = -1;
		}
	}

	window_x11::native window_x11::get_native() const
	{
		return this->wnd;
	}

	bool window_x11::is_close_requested() const
	{
		return this->close_requested;
	}

	hdk::vec2ui window_x11::get_dimensions() const
	{
		XWindowAttributes attr{};
		XGetWindowAttributes(impl::x11_display().display, this->wnd, &attr);
		return static_cast<hdk::vec2ui>(hdk::vec2i{attr.width, attr.height});
	}

	void window_x11::set_dimensions(hdk::vec2ui dimensions)
	{
		hdk::report("warning: NYI set_dimensions linux");
	}

	std::string window_x11::get_title() const
	{
		char* name = nullptr;
		[[maybe_unused]] Status res = XFetchName(impl::x11_display().display, this->wnd, &name);
		std::string ret = name;
		XFree(name);
		return ret;
	}

	void window_x11::set_title(std::string title)
	{
		XStoreName(impl::x11_display().display, this->wnd, title.c_str());
	}

	void window_x11::update()
	{
		const auto& x11d = impl::x11_display();
		XEvent e;
		XNextEvent(x11d.display, &e);
		if(e.type == Expose)
		{
			/*
			auto dims = this->get_dimensions();
			XFillRectangle(x11d.display, this->wnd, DefaultGC(x11d.display, x11d.screen), 0, 0, dims[0], dims[1]);
			*/
		}
		if(e.type == KeyPress)
		{
			this->request_close();
		}
		if(e.type == ClientMessage)
		{
			const Atom protocol = e.xclient.data.l[0];
			if(protocol != None)
			{
				if(protocol == XInternAtom(impl::x11_display().display, "WM_DELETE_WINDOW", False))
				{
					this->request_close();
				}
			}
		}
	}

	bool window_x11::make_opengl_context_current()
	{
		return false;
	}

	const keyboard_state& window_x11::get_keyboard_state() const
	{
		return this->kb_state;
	}

	const mouse_state& window_x11::get_mouse_state() const
	{
		return this->m_state;
	}

	void* window_x11::get_user_data() const
	{
		return this->userdata;
	}

	void window_x11::set_user_data(void* udata)
	{
		this->userdata = udata;
	}

	void window_x11::request_close()
	{
		XUnmapWindow(impl::x11_display().display, this->wnd);
		XDestroyWindow(impl::x11_display().display, this->wnd);
		XFlush(impl::x11_display().display);
		this->close_requested = true;
		this->wnd = -1;
		//XClientMessageEvent msg;
		//msg.type = ClientMessage;
		//msg.window = this->wnd;
		//msg.message_type = XInternAtom(impl::x11_display().display, "WM_DELETE_WINDOW", False);
		//msg.format = 32;
		//msg.data.l[0] = this->wnd;
		//msg.data.l[1] = CurrentTime;
		//XSendEvent(impl::x11_display().display, this->wnd, False, NoEventMask, reinterpret_cast<XEvent*>(&msg));
		//hdk::report("die please");
	}
}

#endif // __linux__
