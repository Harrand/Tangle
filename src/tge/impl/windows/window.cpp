#ifdef _WIN32
#include "tge/impl/windows/window.hpp"
#include "tge/impl/windows/tge_windows.hpp"
#include "hdk/debug.hpp"

namespace tge::impl
{
	window_winapi::window_winapi(window_info info)
	{
		this->hwnd = CreateWindowExA(
			0,
			impl::wndclass_name,
			info.title,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			info.dimensions[0], info.dimensions[1],
			nullptr, nullptr,
			GetModuleHandle(nullptr),
			this
		);
		hdk::assert(this->hwnd != nullptr, "Window creation failed. GetLastError() returns %lu", GetLastError());
		this->hdc = GetDC(this->hwnd);
		if(info.window_flags & window_flag::opengl)
		{
			hdk::report("Setting up window for modern opengl.");
			this->impl_init_opengl();
		}
		ShowWindow(this->hwnd, SW_SHOW);
	}

//--------------------------------------------------------------------------------------------------

	window_winapi::~window_winapi()
	{
		this->impl_request_close();
	}

//--------------------------------------------------------------------------------------------------
	bool window_winapi::is_close_requested() const
	{
		return this->close_requested;
	}

//--------------------------------------------------------------------------------------------------

	hdk::vec2ui window_winapi::get_dimensions() const
	{
		RECT rect;
		[[maybe_unused]] bool ret = GetWindowRect(this->hwnd, &rect);
		hdk::assert(ret, "Failed to retrieve window dimensions. GetLastError() returns %lu", GetLastError());
		return static_cast<hdk::vec2ui>(hdk::vec2i{rect.right - rect.left, rect.bottom - rect.top});
	}

//--------------------------------------------------------------------------------------------------

	void window_winapi::set_dimensions(hdk::vec2ui dims)
	{
		SetWindowPos(
			this->hwnd,
			HWND_NOTOPMOST,
			0, 0,
			dims[0], dims[1],
			SWP_NOMOVE
		);
	}

//--------------------------------------------------------------------------------------------------

	void window_winapi::update()
	{
		MSG msg{};
		this->close_requested = GetMessage(&msg, nullptr, 0, 0) == 0;
		if(this->close_requested)
		{
			return;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		SwapBuffers(this->hdc);
	}

//--------------------------------------------------------------------------------------------------

bool window_winapi::make_opengl_context_current()
{
	hdk::assert(this->hdc != nullptr, "Tried to make window opengl context current, but the window was malformed (HDC is invalid)");
	if(this->opengl_rc == nullptr)
	{
		return false;
	}
	return wglMakeCurrent(this->hdc, this->opengl_rc);
}

//--------------------------------------------------------------------------------------------------

	void window_winapi::impl_init_opengl()
	{
		tge::impl::wgl_function_data wgl = tge::impl::get_wgl_functions();
		hdk::assert(wgl != wgl_function_data{}, "Attempting to create modern OpenGL context for window, but WGL function data has not been loaded properly. Did you forget to `tge::initialise()`?");
		// First, set pixel format.
		{
			int attrib[] =
			{
				WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
				WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
				WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
				WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
				WGL_COLOR_BITS_ARB, 24,
				WGL_DEPTH_BITS_ARB, 24,
				WGL_STENCIL_BITS_ARB, 8,
				WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB, GL_TRUE,
				0
			};
			int format;
			UINT formats;
			if(!wgl.wgl_choose_pixel_format_arb(this->hdc, attrib, nullptr, 1, &format, &formats) || formats == 0)
			{
				hdk::error("Modern OpenGL does not support the default required pixel format. Your graphics card is probably too old to support modern OpenGL.");
			}
			PIXELFORMATDESCRIPTOR dsc =
			{
				.nSize = sizeof(PIXELFORMATDESCRIPTOR)
			};
			bool ok = DescribePixelFormat(this->hdc, format, sizeof(dsc), &dsc);
			hdk::assert(ok, "Failed to describe OpenGL pixel format. No idea why not, I'm afraid.");
			if(!SetPixelFormat(this->hdc, format, &dsc))
			{
				hdk::error("Failed to set modern OpenGL pixel format.");
			}
		}

		// Second, create modern opengl context.
		{
			int attrib[] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
				WGL_CONTEXT_MINOR_VERSION_ARB, 5,
				WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
				#if HDK_DEBUG
					WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
				#endif
				0
			};
			this->opengl_rc = wgl.wgl_create_context_attribs_arb(this->hdc, nullptr, attrib);
			hdk::assert(this->opengl_rc != nullptr, "Failed to create modern opengl context (OpenGL 4.5). Perhaps your graphics card does not support this version?");
			[[maybe_unused]] BOOL ok = wglMakeCurrent(this->hdc, this->opengl_rc);
			hdk::assert(ok, "Failed to make modern opengl context current.");
		}
	}

//--------------------------------------------------------------------------------------------------

	bool window_winapi::impl_is_opengl() const
	{
		return this->opengl_rc != nullptr;
	}

//--------------------------------------------------------------------------------------------------

	void window_winapi::impl_request_close()
	{
		if(this->hwnd != nullptr)
		{
			DestroyWindow(this->hwnd);
			this->hwnd = nullptr;
		}
	}
}

#endif // WIN32
