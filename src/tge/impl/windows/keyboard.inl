#include "tge/impl/windows/detail/winapi.hpp"

namespace tge::impl
{
	constexpr tge::key win_to_tge_key(int virtual_key_code)
	{
		tge::key k = tge::key::unknown;
		switch(virtual_key_code)
		{
			case VK_ESCAPE:
				k = tge::key::esc;
			break;
			case VK_F1:
				k = tge::key::f1;
			break;
			case VK_F2:
				k = tge::key::f2;
			break;
			case VK_F3:
				k = tge::key::f3;
			break;
			case VK_F4:
				k = tge::key::f4;
			break;
			case VK_F5:
				k = tge::key::f5;
			break;
			case VK_F6:
				k = tge::key::f6;
			break;
			case VK_F7:
				k = tge::key::f7;
			break;
			case VK_F8:
				k = tge::key::f8;
			break;
			case VK_F9:
				k = tge::key::f9;
			break;
			case VK_F10:
				k = tge::key::f10;
			break;
			case VK_F11:
				k = tge::key::f11;
			break;
			case VK_F12:
				k = tge::key::f12;
			break;
			case VK_DELETE:
				k = tge::key::del;
			break;
			case VK_PRIOR:
				k = tge::key::page_up;
			break;
			case VK_NEXT:
				k = tge::key::page_down;
			break;
			case VK_SNAPSHOT:
				k = tge::key::print_screen;
			break;
			case VK_SCROLL:
				k = tge::key::scroll_lock;
			break;
			case VK_PAUSE:
				k = tge::key::pause;
			break;
			case VK_INSERT:
				k = tge::key::insert;
			break;
			case 0x31:
				k = tge::key::one;
			break;
			case 0x32:
				k = tge::key::two;
			break;
			case 0x33:
				k = tge::key::three;
			break;
			case 0x34:
				k = tge::key::four;
			break;
			case 0x35:
				k = tge::key::five;
			break;
			case 0x36:
				k = tge::key::six;
			break;
			case 0x37:
				k = tge::key::seven;
			break;
			case 0x38:
				k = tge::key::eight;
			break;
			case 0x39:
				k = tge::key::nine;
			break;
			case 0x30:
				k = tge::key::zero;
			break;
			case VK_OEM_MINUS:
				k = tge::key::minus;
			break;
			case VK_OEM_PLUS:
				k = tge::key::equals; // not a typo...
			break;
			case VK_BACK:
				k = tge::key::backspace;
			break;
			case VK_TAB:
				k = tge::key::tab;
			break;
			case 0x51:
				k = tge::key::q;
			break;
			case 0x57:
				k = tge::key::w;
			break;
			case 0x45:
				k = tge::key::e;
			break;
			case 0x52:
				k = tge::key::r;
			break;
			case 0x54:
				k = tge::key::t;
			break;
			case 0x59:
				k = tge::key::y;
			break;
			case 0x55:
				k = tge::key::u;
			break;
			case 0x49:
				k = tge::key::i;
			break;
			case 0x4F:
				k = tge::key::o;
			break;
			case 0x50:
				k = tge::key::p;
			break;
			case VK_OEM_4:
				k = tge::key::left_bracket;
			break;
			case VK_OEM_6:
				k = tge::key::right_bracket;
			break;
			case VK_RETURN:
				k = tge::key::enter;
			break;
			case VK_CAPITAL:
				k = tge::key::caps_lock;
			break;
			case 0x41:
				k = tge::key::a;
			break;
			case 0x53:
				k = tge::key::s;
			break;
			case 0x44:
				k = tge::key::d;
			break;
			case 0x46:
				k = tge::key::f;
			break;
			case 0x47:
				k = tge::key::g;
			break;
			case 0x48:
				k = tge::key::h;
			break;
			case 0x4A:
				k = tge::key::j;
			break;
			case 0x4B:
				k = tge::key::k;
			break;
			case 0x4C:
				k = tge::key::l;
			break;
			case VK_OEM_1:
				k = tge::key::semi_colon;
			break;
			case VK_OEM_3:
				k = tge::key::apostrophe;
			break;
			case VK_OEM_7:
				k = tge::key::hash;
			break;
			case VK_SHIFT:
				k = tge::key::left_shift;
			break;
			case VK_OEM_5:
				k = tge::key::backslash;
			break;
			case 0x5A:
				k = tge::key::z;
			break;
			case 0x58:
				k = tge::key::x;
			break;
			case 0x43:
				k = tge::key::c;
			break;
			case 0x56:
				k = tge::key::v;
			break;
			case 0x42:
				k = tge::key::b;
			break;
			case 0x4E:
				k = tge::key::n;
			break;
			case 0x4D:
				k = tge::key::m;
			break;
			case VK_OEM_COMMA:
				k = tge::key::comma;
			break;
			case VK_OEM_PERIOD:
				k = tge::key::period;
			break;
			case VK_OEM_2:
				k = tge::key::forward_slash;
			break;
			case VK_RSHIFT:
				k = tge::key::right_shift;
			break;
			case VK_CONTROL:
				k = tge::key::left_ctrl;
			break;
			case VK_LWIN:
				k = tge::key::win_key;
			break;
			case VK_MENU:
				k = tge::key::alt;
			break;
			case VK_SPACE:
				k = tge::key::space;
			break;
			case VK_RMENU:
				k = tge::key::alt_gr;
			break;
			case VK_RCONTROL:
				k = tge::key::right_ctrl;
			break;
		}
		return k;
	}

	constexpr int tge_to_win_key(tge::key key)
	{
		// We have a conversion the other way around, so let's cheat. We're constexpr so we're allowed to be mega slow.
		for(int i = 0x01; i < 0xFF; i++)
		{
			if(win_to_tge_key(i) == key)
			{
				return i;
			}
		}
		return 0x07; // there are a couple of virtual keycodes which are undefined. 0x07 is one of them.
	}
}
