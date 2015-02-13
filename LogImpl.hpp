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