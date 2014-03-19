// ================================================ //

#include "Log.hpp"
#include "LogImpl.hpp"

// ================================================ //

template<> Log* Singleton<Log>::msSingleton = 0;

// ================================================ //

Log::Log(void)
	: m_pImpl(new LogImpl())
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

void Log::logTime(const bool newLine)
{
	m_pImpl->logTime(newLine);
}

// ================================================ //