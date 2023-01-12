#include "tge/keyboard.hpp"
#include "tge/impl/linux/keyboard.hpp"
#include "tge/impl/windows/keyboard.hpp"

namespace tge
{
	std::string get_key_name(tge::key key)
	{
		#ifdef _WIN32
			return tge::impl::get_key_name_windows(key);
		#elif defined(__linux__)
			return tge::impl::get_key_name_linux(key);
		#else
			static_assert(false, "tge::get_key_name not implemented for target platform.");
			return "";
		#endif
	}

	std::string get_chars_typed(tge::key key, const keyboard_state& state)
	{
		#ifdef _WIN32
			return tge::impl::get_chars_typed_windows(key, state);
		#elif defined(__linux__)
			return tge::impl::get_chars_typed_linux(key, state);
		#else
			static_assert(false, "tge::get_chars_typed not implemented for target platform.");
			return "";
		#endif
	}
}
