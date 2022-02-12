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

//! In both macros, LEVEL should be either Output/Info/Warning/Error/Critical/
#define VS_LOG(LEVEL, ...)	\
	do { \
		if (strcmp(#LEVEL, "Output") == 0) \
		{ \
			VS::Log::GetLogger()->set_pattern("%v"); \
			VS::Log::GetLogger()->trace(__VA_ARGS__); \
			VS::Log::GetLogger()->set_pattern(VS::Log::GetPattern()); \
			break; \
		} \
		else if (strcmp(#LEVEL, "Info") == 0) { VS::Log::GetLogger()->info(__VA_ARGS__); break; } \
		else if (strcmp(#LEVEL, "Warning") == 0) { VS::Log::GetLogger()->warn(__VA_ARGS__); break; } \
		else if (strcmp(#LEVEL, "Error") == 0) { VS::Log::GetLogger()->error(__VA_ARGS__); break; } \
		else if (strcmp(#LEVEL, "Critical") == 0) { VS::Log::GetLogger()->critical(__VA_ARGS__); break; } \
		else { VS::Log::GetLogger()->error("INVALID LOG LEVEL"); break; } \
	} while (0);
	

//! Should be used for logs that originated from a source other than the current application (the server, a tool, etc.)
#define VS_LOG_EXTERNAL(SOURCE, LEVEL, ...)	\
											VS::Log::GetLogger()->set_pattern("%^[%T][" #SOURCE "][%l] %v %$"); \
											VS_LOG(LEVEL, __VA_ARGS__) \
											VS::Log::GetLogger()->set_pattern(VS::Log::GetPattern());