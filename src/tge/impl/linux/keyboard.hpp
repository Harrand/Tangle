#ifndef TANGLE_IMPL_LINUX_KEYBOARD_HPP
#ifdef __linux__
#include "tge/api/keyboard.hpp"
#include <string>

namespace tge::impl
{
	std::string get_key_name_linux(tge::key key);
	std::string get_chars_typed_linux(tge::key key, const keyboard_state& state);
}

#endif // __linux__
#endif // TANGLE_IMPL_LINUX_KEYBOARD_HPP
