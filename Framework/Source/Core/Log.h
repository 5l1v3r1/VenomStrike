#pragma once

#include <memory>
#include <string>

#include <spdlog/spdlog.h>

namespace VS
{
	class Log
	{
	public:
		static void Init(const std::string& LoggerName);

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return Logger; }
		inline static const std::string& GetPattern() { return Pattern; }

	private:
		static std::shared_ptr<spdlog::logger> Logger;
		static std::string Pattern;
	};
}

//! In both macros, LEVEL should be either trace/info/warning/error/critical/ (notice the lowercase)
#define VS_LOG(LEVEL, ...)	::VS::Log::GetLogger()->LEVEL((__VA_ARGS__))

//! Should be used for logs that originated from a source other than the current application (the server, a tool, etc.)
#define VS_LOG_EXTERNAL(SOURCE, LEVEL, ...)	\
											VS::Log::GetLogger()->set_pattern("%^[%T][" #SOURCE "][%l] %v %$"); \
											VS::Log::GetLogger()->LEVEL((__VA_ARGS__)); \
											VS::Log::GetLogger()->set_pattern(VS::Log::GetPattern());