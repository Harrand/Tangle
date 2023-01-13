#ifdef __linux__
#define GLX_GLXEXT_PROTOTYPES
#include "tge/impl/linux/window.hpp"
#include <GL/glxext.h>
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
			this->impl_request_close();
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
		}
		if(e.type == ClientMessage)
		{
			const Atom protocol = e.xclient.data.l[0];
			if(protocol != None)
			{
				if(protocol == XInternAtom(impl::x11_display().display, "WM_DELETE_WINDOW", False))
				{
					this->impl_request_close();
				}
			}
		}
	}

	bool window_x11::make_opengl_context_current()
	{
		if(ctx == nullptr)
		{
			return false;
		}
		return glXMakeCurrent(impl::x11_display().display, this->wnd, this->ctx);
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

	void window_x11::impl_request_close()
	{
		XUnmapWindow(impl::x11_display().display, this->wnd);
		XDestroyWindow(impl::x11_display().display, this->wnd);
		XFlush(impl::x11_display().display);
		this->close_requested = true;
		this->wnd = -1;
	}

	void window_x11::impl_init_opengl()
	{
		const auto& x11d = impl::x11_display();
		constexpr int maj = 4, min = 5;
		int nelements;
		GLXFBConfig* fb_configs = glXChooseFBConfig(x11d.display, x11d.screen, nullptr, &nelements);
		hdk::assert(fb_configs != nullptr, "Failed to choose framebuffer config for OpenGL context.");
		int attribs[] =
		{
			GLX_CONTEXT_MAJOR_VERSION_ARB, maj,
			GLX_CONTEXT_MINOR_VERSION_ARB, min,
			GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
			None
		};
		this->ctx = glXCreateContextAttribsARB(x11d.display, fb_configs[0], nullptr, True, attribs);
		hdk::assert(this->ctx != nullptr, "Could create OpenGL context :(");
		XFree(fb_configs);
		this->make_opengl_context_current();	
	}
}

#endif // __linux__
