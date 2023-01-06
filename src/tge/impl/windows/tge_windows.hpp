#ifndef TANGLE_IMPL_WINDOWS_TGE_HPP
#define TANGLE_IMPL_WINDOWS_TGE_HPP
#ifdef _WIN32
#include "tge/impl/windows/detail/winapi.hpp"

namespace tge::impl
{
	constexpr char wndclass_name[] = "Tangle Windowing Library";

	LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	void initialise_windows();
	void terminate_windows();
}

#endif // _WIN32
#endif // TANGLE_IMPL_WINDOWS_TGE_HPP
