// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
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