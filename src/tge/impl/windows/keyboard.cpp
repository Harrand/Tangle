#ifdef _WIN32
#include "tge/impl/windows/keyboard.hpp"
#include "hdk/debug.hpp"
#include <cstring>

namespace tge::impl
{
	std::string get_key_name_windows(tge::key key)
	{
		int vkc = tge_to_win_key(key);
		auto scancode = MapVirtualKeyA(vkc, MAPVK_VK_TO_VSC);
		LONG param = scancode << 16;
		
		std::string ret;
		ret.resize(256, '\0');
		int res = GetKeyNameTextA(param, ret.data(), ret.size());
		if(res == 0)
		{
			return "unknown key";
		}
		return ret;
	}
}

#endif // _WIN32
