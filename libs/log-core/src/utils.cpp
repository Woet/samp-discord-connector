#include <algorithm>

#ifdef WIN32
#  include <Windows.h>
#else
#  include <sys/stat.h>
#endif

#include "utils.hpp"

using samplog::samplog_LogLevel;


const char *utils::Getsamplog_LogLevelAsString(samplog::samplog_LogLevel level)
{
	switch (level)
	{
	case samplog_LogLevel::DEBUG:
		return "DEBUG";
	case samplog_LogLevel::INFO:
		return "INFO";
	case samplog_LogLevel::WARNING:
		return "WARNING";
	case samplog_LogLevel::ERROR:
		return "ERROR";
	case samplog_LogLevel::FATAL:
		return "FATAL";
	case samplog_LogLevel::VERBOSE:
		return "VERBOSE";
	case samplog_LogLevel::NONE:
	default:
		// do nothing
		break;
	}
	return "<unknown>";
}

fmt::rgb utils::Getsamplog_LogLevelColor(samplog::samplog_LogLevel level)
{
	switch (level)
	{
	case samplog_LogLevel::DEBUG:
		return fmt::color::green;
	case samplog_LogLevel::INFO:
		return fmt::color::royal_blue;
	case samplog_LogLevel::WARNING:
		return fmt::color::orange;
	case samplog_LogLevel::ERROR:
		return fmt::color::red;
	case samplog_LogLevel::FATAL:
		return fmt::color::red;
	case samplog_LogLevel::VERBOSE:
		return fmt::color::white_smoke;
	case samplog_LogLevel::NONE:
	default:
		// do nothing
		break;
	}
	return fmt::color::white;
}

void utils::CreateFolder(std::string foldername)
{
#ifdef WIN32
	std::replace(foldername.begin(), foldername.end(), '/', '\\');
	CreateDirectoryA(foldername.c_str(), NULL);
#else
	std::replace(foldername.begin(), foldername.end(), '\\', '/');
	mkdir(foldername.c_str(), ACCESSPERMS);
#endif
}

void utils::EnsureFolders(std::string const &path)
{
	size_t pos = 0;
	while ((pos = path.find('/', pos)) != std::string::npos)
		utils::CreateFolder(path.substr(0, pos++));
}

void utils::EnsureTerminalColorSupport()
{
	static bool enabled = false;
	if (enabled)
		return;

#ifdef WIN32
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (console == INVALID_HANDLE_VALUE)
		return;

	DWORD console_opts;
	if (!GetConsoleMode(console, &console_opts))
		return;

	if (!SetConsoleMode(console, console_opts | ENABLE_VIRTUAL_TERMINAL_PROCESSING))
		return;
#endif
	enabled = true;
}
