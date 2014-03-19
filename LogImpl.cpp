// ================================================ //

#include "LogImpl.hpp"

// ================================================ //

LogImpl::LogImpl(void)
	: m_file()
{
	m_file.open("ExtMF.log", std::ios::out);
	if(!m_file.is_open()){
		throw std::exception("Failed to open log file");
	}

	this->logTime(false);
	this->logMessage(" Log created for Extreme Metal Fighter\n");
}

// ================================================ //

LogImpl::~LogImpl(void)
{
	m_file.close();
}

// ================================================ //

void LogImpl::logMessage(const std::string& str)
{
	m_file << str << std::endl;
}

// ================================================ //

void LogImpl::logTime(const bool newLine)
{
#ifdef __WIN32__
	SYSTEMTIME st;
	GetLocalTime(&st);
	m_file << "[" << st.wMonth << "/" << st.wDay <<
		"/" << st.wYear << " - " << st.wHour << ":" <<
		st.wMinute << ":" << st.wSecond << "]";
#elif __linux__
	;
#elif __APPLE__
	;
#endif

	if(newLine)
		m_file << std::endl;
}

// ================================================ //