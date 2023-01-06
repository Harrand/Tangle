#ifndef TANGLE_API_WINDOW_HPP
#define TANGLE_API_WINDOW_HPP
#include "hdk/data/vector.hpp"

namespace tge
{
	namespace window_flag
	{
		using flag_bit = int;
		static constexpr flag_bit
		// Normal window, no special flags.
		none = 0x00,
		// Window will create and maintain its own OpenGL context. During the lifetime of a created window, it is valid to call OpenGL functions (OpenGL desktop 4.5).
		opengl = 0x01 << 0,
		// Window will have a transparent background.
		transparent = 0x01 << 1,
		// Window will have a smaller title bar, without a maximise/minimise/close button.
		undecorated = 0x01 << 2,
		// Window will have no title bar at all.
		bare = 0x01 << 3;
	}
	struct window_info
	{
		const char* title = "Untitled";
		hdk::vec2ui dimensions = {800u, 600u};
		window_flag::flag_bit window_flags = window_flag::none;
	};

	template<typename T>
	concept window_api = requires(T t, hdk::vec2ui dims)
	{
		{t.is_close_requested()} -> std::same_as<bool>;
		{t.get_dimensions()} -> std::same_as<hdk::vec2ui>;
		{t.set_dimensions(dims)} -> std::same_as<void>;
		{t.update()} -> std::same_as<void>;
		{t.make_opengl_context_current()} -> std::same_as<bool>;
	};
}

#endif // TANGLE_API_WINDOW_HPP
