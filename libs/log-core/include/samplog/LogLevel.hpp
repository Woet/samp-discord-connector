#pragma once

#ifdef ERROR //because Microsoft
#undef ERROR
#endif


namespace samplog
{
	enum samplog_LogLevel
	{
		NONE = 0,
		DEBUG = 1,
		INFO = 2,
		WARNING = 4,
		ERROR = 8,
		FATAL = 16,
		VERBOSE = 32
	};

	inline samplog_LogLevel operator|(samplog_LogLevel a, samplog_LogLevel b)
	{
		return static_cast<samplog_LogLevel>(static_cast<int>(a) | static_cast<int>(b));
	}
	inline samplog_LogLevel &operator|=(samplog_LogLevel &in, samplog_LogLevel val)
	{
		return in = in | val;
	}
}
