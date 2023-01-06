#include "tge/impl/windows/tge_windows.hpp"
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
		.lpszClassName = "Tangle Windowing Library",
		.hIconSm = nullptr
	};

	void initialise_windows()
	{
		auto window_class = wndclass_gpuacc;
		window_class.hInstance = GetModuleHandle(nullptr);
		RegisterClassExA(&window_class);
	}

	void terminate_windows()
	{
		UnregisterClassA(wndclass_gpuacc.lpszClassName, GetModuleHandle(nullptr));
	}

	LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}

#endif // _WIN32
