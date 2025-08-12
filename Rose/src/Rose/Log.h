#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/fmt/ostr.h>
namespace Rose
{
	class ROSE_API Log
	{
	public:
		static void Init();
		//inline可以被多个源文件包含，shared_ptr 将生命周期延长至调用者释放
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	
	
	};
} // namespace Rose
//CORE LOGGING MACROS
#define RS_CORE_ERROR(...)		::Rose::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RS_CORE_WARN(...)		::Rose::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RS_CORE_INFO(...)		::Rose::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RS_CORE_TRACE(...)		::Rose::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RS_CORE_FATAL(...)		::Rose::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//client logging macros
#define RS_ERROR(...)			::Rose::Log::GetClientLogger()->error(__VA_ARGS__)
#define RS_WARN(...)			::Rose::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RS_INFO(...)			::Rose::Log::GetClientLogger()->info(__VA_ARGS__)
#define RS_TRACE(...)			::Rose::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RS_FATAL(...)			::Rose::Log::GetClientLogger()->fatal(__VA_ARGS__)


