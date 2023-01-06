#include "tge/impl/windows/tge_windows.hpp"
#include "tge/impl/windows/window.hpp"
#ifdef _WIN32

namespace tge::impl
{
	constexpr WNDCLASSEXA wndclass_gpuacc
	{
		.cbSize = sizeof(WNDCLASSEX),
		.style = CS_OWNDC,
		.lpfnWndProc = wndproc,
		.cbClsExtra = 0,
		.cbWndExtra = 0,
		.hInstance = nullptr,
		.hIcon = nullptr,
		.hCursor = nullptr,
		.hbrBackground = nullptr,
		.lpszMenuName = nullptr,
		.lpszClassName = wndclass_name,
		.hIconSm = nullptr
	};

	void initialise_windows()
	{
		auto window_class = wndclass_gpuacc;
		window_class.hInstance = GetModuleHandle(nullptr);
		RegisterClassExA(&window_class);
	}

//--------------------------------------------------------------------------------------------------

	void terminate_windows()
	{
		UnregisterClassA(wndclass_name, GetModuleHandle(nullptr));
	}

//--------------------------------------------------------------------------------------------------

	LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		auto get_window = [hwnd]()
		{
			auto wnd = reinterpret_cast<window_winapi*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
			hdk::assert(wnd != nullptr, "window_winapi userdata not setup properly. userdata was nullptr.");
			return wnd;
		};
		switch(msg)
		{
			case WM_CREATE:
			{
				// When created, the window passes a void* for create params, this is guaranteed to be a pointer to the window_winapi. We set it as userdata so we always have access to this pointer.
				auto create = reinterpret_cast<CREATESTRUCT*>(lparam);
				auto wnd = reinterpret_cast<window_winapi*>(create->lpCreateParams);
				SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(wnd));
			}
			break;
			case WM_CLOSE:
				get_window()->impl_request_close();	
				return FALSE;
			break;
			case WM_DESTROY:
				PostQuitMessage(0);
			break;
		}
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}

#endif // _WIN32
