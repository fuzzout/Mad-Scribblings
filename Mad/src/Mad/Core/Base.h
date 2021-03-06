#pragma once
#include <memory>

#ifdef MAD_ENABLE_ASSERTS
#define MAD_ASSERT(x, ...) { if(!(x)) { MAD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define MAD_CORE_ASSERT(x, ...) { if(!(x)) { MAD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define MAD_ASSERT(x, ...)
#define MAD_CORE_ASSERT(x, ...)
#endif

#ifdef MAD_DEBUG
#define MAD_ENABLE_ASSERTS
#endif

#define BIT(x) (1 << x)

#define MAD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1) 

namespace Mad {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}