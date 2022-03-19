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

#ifdef HZ_ENABLE_ASSERTS
#define MAD_ASSERT(x, ...) { if(!(x)) { MAD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define MAD_CORE_ASSERT(x, ...) { if(!(x)) { MAD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define MAD_ASSERT(x, ...)
#define MAD_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)