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

	HWND window_winapi::impl_get_hwnd() const
	{
		return this->hwnd;
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
