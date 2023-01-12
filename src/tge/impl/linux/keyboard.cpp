#ifdef __linux__
#include "tge/impl/linux/keyboard.hpp"

namespace tge::impl
{
	std::string get_key_name_linux(tge::key key)
	{
		return "NYI";
	}

	std::string get_chars_typed_linux(tge::key key, const keyboard_state& state)
	{
		return "NYI";
	}
}

#endif // __linux__
