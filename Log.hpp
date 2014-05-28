// ================================================ //

#ifndef __LOG_HPP__
#define __LOG_HPP__

// ================================================ //

#include <memory>
#include "Singleton.hpp"

// ================================================ //

class LogImpl;

// ================================================ //

class Log : public Singleton<Log>
{
public:
	explicit Log(void);
	~Log(void);

	void logMessage(const std::string& str);
	void logTime(const bool time = true, const bool date = false);

private:
	std::shared_ptr<LogImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //