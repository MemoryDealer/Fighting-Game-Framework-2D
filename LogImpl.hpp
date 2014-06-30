// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: LogImpl.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines LogImpl Pimpl idiom class.
// ================================================ //

#ifndef __LOGIMPL_HPP__
#define __LOGIMPL_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

// Pimpl idiom class for Log.
class LogImpl
{
public:
	// Opens a file handle for ExtMF.log and logs the date, time, and
	// engine version.
	explicit LogImpl(void);

	// Closes the file handle.
	~LogImpl(void);

	void logMessage(const std::string& str);
	void logTime(const bool time = true, const bool date = false);

private:
	std::ofstream m_file;
};

// ================================================ //

#endif

// ================================================ //