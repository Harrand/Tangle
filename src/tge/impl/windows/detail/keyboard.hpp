#ifndef TANGLE_IMPL_WINDOWS_KEYBOARD_HPP
#define TANGLE_IMPL_WINDOWS_KEYBOARD_HPP
#ifdef _WIN32
#include "tge/api/keyboard.hpp"
#include <string>

namespace tge::impl
{
	constexpr tge::key win_to_tge_key(int virtual_key_code);
	constexpr int tge_to_win_key(tge::key key);
	std::string get_key_name(tge::key key);
}

#include "tge/impl/windows/detail/keyboard.inl"

#endif // _WIN32
#endif // TANGLE_IMPL_WINDOWS_KEYBOARD_HPP
