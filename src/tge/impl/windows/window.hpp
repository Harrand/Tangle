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
		bool make_opengl_context_current();
		const keyboard_state& get_keyboard_state() const;
		const mouse_state& get_mouse_state() const;
		// tge::window_api<> end
		friend LRESULT wndproc(HWND, UINT, WPARAM, LPARAM);
	private:
		void impl_init_opengl();
		bool impl_is_opengl() const;
		void impl_request_close();
		keyboard_state& impl_mutable_keyboard_state();
		mouse_state& impl_mutable_mouse_state();

		HWND hwnd = nullptr;
		HDC hdc = nullptr;
		HGLRC opengl_rc = nullptr;
		bool close_requested = false;
		keyboard_state key_state = {};
		mouse_state mouse_state = {};
	};
	static_assert(tge::window_api<window_winapi>);
}

#endif // _WIN32
#endif // TANGLE_IMPL_WINDOWS_WINDOW_HPP
