#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace VS
{
	std::shared_ptr<spdlog::logger> Log::Logger;
	std::string Log::Pattern = "%^[%T][%n][%l] %v %$";

	void Log::Init(const std::string& LoggerName)
	{
		spdlog::set_pattern(Pattern);
		Logger = spdlog::stdout_color_mt(LoggerName);
		Logger->set_level(spdlog::level::trace);
	}
}
