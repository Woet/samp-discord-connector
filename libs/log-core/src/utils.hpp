#pragma once

#include <string>
#include <fmt/color.h>

#include "samplog/LogLevel.hpp"


namespace utils
{
	const char *Getsamplog_LogLevelAsString(samplog::samplog_LogLevel level);
	fmt::rgb Getsamplog_LogLevelColor(samplog::samplog_LogLevel level);

	void CreateFolder(std::string foldername);
	void EnsureFolders(std::string const &path);
	void EnsureTerminalColorSupport();
}
