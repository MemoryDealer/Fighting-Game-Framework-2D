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
// File: Log.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Log singleton class.
// ================================================ //

#include "Log.hpp"
#include "LogImpl.hpp"

// ================================================ //

template<> Log* Singleton<Log>::msSingleton = nullptr;

// ================================================ //

Log::Log(void) :
m_pImpl(new LogImpl())
{

}

// ================================================ //

Log::~Log(void)
{

}

// ================================================ //

void Log::logMessage(const std::string& str)
{
	m_pImpl->logMessage(str);
}

// ================================================ //

void Log::logTime(const bool time, const bool date)
{
	m_pImpl->logTime(time, date);
}

// ================================================ //