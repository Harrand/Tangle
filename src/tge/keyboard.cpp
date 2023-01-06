#include "tge/keyboard.hpp"
#include "tge/impl/windows/keyboard.hpp"

namespace tge
{
	std::string get_key_name(tge::key key)
	{
		#ifdef _WIN32
			return tge::impl::get_key_name_windows(key);
		#else
			static_assert(false, "tge::get_key_name not implemented for target platform.");
			return "";
		#endif
	}
}
