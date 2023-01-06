#ifndef TANGLE_TGE_HPP
#define TANGLE_TGE_HPP

namespace tge
{
	void initialise();
	void terminate();

	enum class platform
	{
		unknown,
		windows,
		linux,
		macos
	};

	constexpr platform get_platform()
	{
		#ifdef _WIN32
			return platform::windows;
		#else
			#ifdef __linux__
				return platform::linux;
			#else
				#ifdef __APPLE__
					return platform::macos;
				#else
					return platform::unknown;
				#endif
			#endif
		#endif
	}
}

#endif // TANGLE_TGE_HPP
