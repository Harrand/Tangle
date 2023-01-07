#ifndef TANGLE_KEYBOARD_HPP
#define TANGLE_KEYBOARD_HPP
#include "tge/api/keyboard.hpp"
#include <string>

namespace tge
{
	std::string get_key_name(tge::key key);
	std::string get_chars_typed(tge::key key, const keyboard_state& state);
}

#endif // TANGLE_KEYBOARD_HPP
