#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace Mad {
	class MAD_API Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

//core log macros
#define MAD_CORE_ERROR(...)	::Mad::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MAD_CORE_WARN(...)	::Mad::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MAD_CORE_INFO(...)	::Mad::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MAD_CORE_TRACE(...) ::Mad::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MAD_CORE_FATAL(...) ::Mad::Log::GetCoreLogger()->critical(__VA_ARGS__)

//client log macros
#define MAD_ERROR(...)	::Mad::Log::GetClientLogger()->error(__VA_ARGS__)
#define MAD_WARN(...)	::Mad::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MAD_INFO(...)	::Mad::Log::GetClientLogger()->info(__VA_ARGS__)
#define MAD_TRACE(...) ::Mad::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MAD_FATAL(...) ::Mad::Log::GetClientLogger()->critical(__VA_ARGS__)