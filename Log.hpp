// ========================================================================= //
// Fighting game framework (2D) with online multiplayer.
// Copyright(C) 2014 Jordan Sparks <unixunited@live.com>
//
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ========================================================================= //
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