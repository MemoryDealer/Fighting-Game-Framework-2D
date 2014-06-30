// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Log.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines Log singleton class.
// ================================================ //

#ifndef __LOG_HPP__
#define __LOG_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class LogImpl;

// ================================================ //

// Writes data to log file.
class Log : public Singleton<Log>
{
public:
	// Allocates LogImpl.
	explicit Log(void);

	// Empty destructor.
	~Log(void);

	// Writes str to open log file with a newline at the end.
	void logMessage(const std::string& str);

	// Writes the current time in format hh:mm:ss and date in m/d/y if date is true.
	void logTime(const bool time = true, const bool date = false);

private:
	std::shared_ptr<LogImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //