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
// File: LogImpl.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements LogImpl Pimpl idiom class.
// ================================================ //

#include "LogImpl.hpp"
#include "Engine.hpp"

// ================================================ //

LogImpl::LogImpl(void) :
m_file()
{
	m_file.open("ExtMF.log", std::ios::out);
	if (!m_file.is_open()){
		throw std::exception("Failed to open log file");
	}

	this->logTime(false, true);
	this->logMessage(" Log created for Fighting Game Framework 2D - Version " + Engine::toString(Engine::VERSION_MAJOR) +
		"." + Engine::toString(Engine::VERSION_MINOR1) + Engine::toString(Engine::VERSION_MINOR2));
}

// ================================================ //

LogImpl::~LogImpl(void)
{
	m_file.close();
}

// ================================================ //

void LogImpl::logMessage(const std::string& str)
{
	this->logTime();
	m_file << str << std::endl;

	printf("LOG: %s\n", str.c_str()); // TODO: Remove in release build.
}

// ================================================ //

void LogImpl::logTime(const bool time, const bool date)
{
#ifdef __WIN32__
	SYSTEMTIME st;
	GetLocalTime(&st);
	if (date){
		m_file << "[" << st.wMonth << "/" << st.wDay << "/" << st.wYear << "] ";
	}
	if (time){
		if (st.wHour < 10) m_file << "0";
		m_file << st.wHour << ":";
		if (st.wMinute < 10) m_file << "0";
		m_file << st.wMinute << ":";
		if (st.wSecond < 10) m_file << "0";
		m_file << st.wSecond << ": ";
	}
#elif __linux__
	;
#elif __APPLE__
	;
#endif
}

// ================================================ //