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

	std::string get_chars_typed_windows(tge::key key, const keyboard_state& state)
	{
		std::wstring ret;
		ret.resize(256);
		// Firstly fill up the keyboard state (all of the 256 virtual keys).
		std::array<BYTE, 256> win_kb_state;
		std::fill(win_kb_state.begin(), win_kb_state.end(), 0);
		for(std::size_t i = 0; i < 256; i++)
		{
			tge::key k = tge::impl::win_to_tge_key(i);
			if(std::find(state.keys_down.begin(), state.keys_down.end(), k) != state.keys_down.end())
			{
				win_kb_state[i] = 0xFF;
			}
		}
		
		// Secondly, write into the key state.
		int vkc = tge::impl::tge_to_win_key(key);
		auto scancode = MapVirtualKeyA(vkc, MAPVK_VK_TO_VSC);
		int res = ToUnicode(vkc, scancode, win_kb_state.data(), ret.data(), ret.size(), 0);
		std::string reta;
		reta.resize(ret.size());
		std::transform(ret.begin(), ret.end(), reta.begin(), [](wchar_t wc)
		{
			return static_cast<char>(wc);
		});
		return reta;
	}
}

#endif // _WIN32
