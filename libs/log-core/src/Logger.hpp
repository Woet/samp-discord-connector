#pragma once

#include <string>
#include <chrono>
#include <atomic>

#include <samplog/export.h>
#include <samplog/ILogger.hpp>
#include "LogRotationManager.hpp"

using samplog::samplog_LogLevel;


class Logger : public samplog::ILogger
{
public:
	using Clock = std::chrono::system_clock;

	struct Config
	{
		samplog_LogLevel Level = samplog_LogLevel::ERROR | samplog_LogLevel::WARNING | samplog_LogLevel::FATAL;
		bool PrintToConsole = false;
		bool Append = true;
		LogRotationConfig Rotation;
	};

public:
	Logger(std::string modulename);
	~Logger();

public: // interface implementation
	bool IsLogLevel(samplog_LogLevel log_level) const override
	{
		return (_config.Level & log_level) == log_level;
	}

	bool Log(samplog_LogLevel level, std::string msg,
		std::vector<samplog::AmxFuncCallInfo> const &call_info) override;
	bool Log(samplog_LogLevel level, std::string msg) override;
	bool LogNativeCall(AMX * const amx, cell * const params,
		std::string name, std::string params_format) override;

	void Destroy() override
	{
		delete this;
	}

public:
	inline std::string const &GetModuleName() const
	{
		return _moduleName;
	}

private:
	void OnConfigUpdate(Logger::Config const &config);

	std::string FormatTimestamp(Clock::time_point time);
	std::string FormatLogMessage(std::string message,
		std::vector<samplog::AmxFuncCallInfo> call_info);

	void WriteLogString(std::string const &time, samplog_LogLevel level,
		std::string const &message);
	void PrintLogString(std::string const &time, samplog_LogLevel level,
		std::string const &message);

private:
	std::string const _moduleName;
	std::string const _logFilePath;
	std::atomic<unsigned int> _logCounter;

	Config _config;
};
