// ================================================ //

#ifndef __LOGIMPL_HPP__
#define __LOGIMPL_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class LogImpl
{
public:
	explicit LogImpl(void);
	~LogImpl(void);

	void logMessage(const std::string& str);
	void logTime(const bool time = true, const bool date = false);

private:
	std::ofstream m_file;
};

// ================================================ //

#endif

// ================================================ //