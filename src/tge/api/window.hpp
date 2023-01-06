#ifndef TANGLE_API_WINDOW_HPP
#define TANGLE_API_WINDOW_HPP
#include "hdk/data/vector.hpp"

namespace tge
{
	namespace window_flag
	{
		enum flag_bit
		{
			none = 0x00,
			opengl = 0x01
		};
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
	};
}

#endif // TANGLE_API_WINDOW_HPP
