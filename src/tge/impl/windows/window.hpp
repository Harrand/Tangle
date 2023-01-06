#ifndef TANGLE_IMPL_WINDOWS_WINDOW_HPP
#define TANGLE_IMPL_WINDOWS_WINDOW_HPP
#ifdef _WIN32
#include "tge/api/window.hpp"
#include "tge/impl/windows/detail/winapi.hpp"

namespace tge::impl
{
	class window_winapi
	{
	public:
		window_winapi(window_info info);
		window_winapi(const window_winapi& copy) = delete;
		window_winapi(window_winapi&& move) = delete;
		~window_winapi();
		window_winapi& operator=(const window_winapi& rhs) = delete;
		window_winapi& operator=(window_winapi&& rhs) = delete;

		// tge::window_api<> begin
		bool is_close_requested() const;
		hdk::vec2ui get_dimensions() const;
		void set_dimensions(hdk::vec2ui dimensions);
		void update();
		// tge::window_api<> end
		friend LRESULT wndproc(HWND, UINT, WPARAM, LPARAM);
	private:
		void impl_init_opengl();
		void impl_request_close();

		HWND hwnd = nullptr;
		HDC hdc = nullptr;
		bool close_requested = false;
	};
	static_assert(tge::window_api<window_winapi>);
}

#endif // _WIN32
#endif // TANGLE_IMPL_WINDOWS_WINDOW_HPP
