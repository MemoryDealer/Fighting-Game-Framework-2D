// ================================================ //

#ifndef __LOG_HPP__
#define __LOG_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class LogImpl;

// ================================================ //

class Log : public Singleton<Log>
{
public:
	explicit Log(void);
	~Log(void);

	void logMessage(const std::string& str);
	void logTime(const bool newLine = true);

private:
	std::tr1::shared_ptr<LogImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //