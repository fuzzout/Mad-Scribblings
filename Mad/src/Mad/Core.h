#pragma once

#ifdef MAD_PLATFORM_WINDOWS
	#ifdef MAD_BUILD_DLL
		#define MAD_API __declspec(dllexport)
			#else
			#define MAD_API __declspec(dllimport)
		#endif
#else
#error Mad only supports windows!
#endif
